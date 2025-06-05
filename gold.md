# Understanding Signal Handling and Exit Status Codes

## 1. Why We Set Exit Status to 130

The value 130 is a convention that follows this formula:
- 128 = base value for signal-terminated processes
- SIGINT = signal number 2 (Ctrl+C)
- So: 128 + 2 = 130

In bash, when a process is terminated by Ctrl+C (SIGINT), the exit status is set to 130. This follows the POSIX convention that processes terminated by signals should have an exit status of 128 + signal number.

## 2. The WIF Macros Explained
These macros from <sys/wait.h> help you interpret the status returned by waitpid().

### WIFEXITED(status)
- **Purpose**: Checks if the child process terminated normally (with exit() or by reaching the end of main())
- **Returns**: Non-zero (true) if the child exited normally
- **Usage**: `if (WIFEXITED(status)) { /* child exited normally */ }`

### WEXITSTATUS(status)
- **Purpose**: Extracts the exit code from a normally terminated process
- **Returns**: The exit code value (0-255) passed to exit()
- **Usage**: `g_exit_status = WEXITSTATUS(status);`
- **Note**: Only use this if WIFEXITED returned true

### WIFSIGNALED(status)
- **Purpose**: Checks if the child process was terminated by a signal (like Ctrl+C or segfault)
- **Returns**: Non-zero (true) if the child was killed by a signal
- **Usage**: `if (WIFSIGNALED(status)) { /* child was killed by signal */ }`

### WTERMSIG(status)
- **Purpose**: Extracts the signal number that caused the process to terminate
- **Returns**: The signal number (e.g., 2 for SIGINT, 11 for SIGSEGV)
- **Usage**: `signal_num = WTERMSIG(status);`
- **Note**: Only use this if WIFSIGNALED returned true

## 3. Your Signal Handling Flow

### In your update_exit_status function:
This function:
- Checks if the process exited normally; if so, uses its exit code
- If not, checks if it was terminated by a signal; if so, sets exit status to 128 + signal number

### In set_heredoc_status:
This function:
- Checks if the heredoc child was terminated by a signal (Ctrl+C)
- If so, closes the pipe, sets exit status to 130, and returns -1 to indicate failure
- Otherwise returns the pipe file descriptor for future use

## Why This Approach Is Correct
- **POSIX Compliance**: Following the exit status conventions of bash/POSIX
- **Proper Signal Handling**: Different code paths for normal exits vs. signal terminations
- **Resource Management**: Closing file descriptors when processes terminate unexpectedly
- **User Experience**: Matching bash's behavior so scripts behave correctly


## 3. Why Set h_fd = -1 When a Heredoc Is Interrupted

Setting `h_fd = -1` is a crucial error handling technique:

1. **Invalid FD Marker**: In Unix, valid file descriptors are always non-negative integers. Setting a file descriptor to -1 is a convention to mark it as invalid.

2. **Error Detection**: Code that uses this descriptor can check:
   ```c
   if (file->h_fd < 0) {
       // Handle error case - don't try to read from this FD
   }
   ```

3. **Preventing Undefined Behavior**: Using an invalid or closed file descriptor can cause:
   - Reading from uninitialized memory
   - Writing to the wrong place
   - Unpredictable program behavior

4. **Clear State Communication**: It clearly communicates that a process was interrupted and data collection failed.

5. **Safety in Resource Management**: Prevents accidentally using a closed or never-opened file descriptor later in the program.

## 4. How Complex Commands Are Executed

Let's analyze a complex command: `cat << EOF | grep "hello" | wc -l > output.txt`

### Step 1: Parsing and Tokenization
- Command is broken into tokens and organized into a command pipeline
- Redirections are identified: heredoc `<< EOF` and output file `> output.txt`
- Pipeline stages identified: `cat`, `grep "hello"`, and `wc -l`

### Step 2: Heredoc Collection (CRITICAL)
- Before any command is executed, ALL heredocs must be collected
- Shell forks a child process to collect the heredoc input
- Child reads lines until delimiter (`EOF`) is seen
- Data is stored in a pipe, with read end saved for later use
- Parent waits for this process to complete before proceeding

### Step 3: Pipeline Setup
- N-1 pipes created for N commands (2 pipes for 3 commands)
- Each pipe has a read end (0) and write end (1)

### Step 4: Command Execution
1. **Fork First Command (cat):**
   - Stdin redirected to heredoc pipe
   - Stdout redirected to pipe[0][1]
   - Close all other pipe ends
   - Execute cat

2. **Fork Second Command (grep):**
   - Stdin redirected to pipe[0][0]
   - Stdout redirected to pipe[1][1]
   - Close all other pipe ends
   - Execute grep with "hello" argument

3. **Fork Third Command (wc):**
   - Stdin redirected to pipe[1][0]
   - Stdout redirected to output.txt file
   - Close all other pipe ends
   - Execute wc with -l argument

### Step 5: Parent Process Behavior
- Closes all pipe ends (to prevent hanging)
- Waits for all child processes to complete
- Updates exit status based on last command's exit code

### Step 6: Cleanup
- Free memory allocated for command structures
- Free pipe arrays
- Return to main loop for next command

## 5. Common Pitfalls in Shell Implementation

1. **Collecting Heredocs Too Late**: Heredocs must be collected before any command in the pipeline executes. Otherwise, commands might start running before their input is ready.

2. **Not Closing Unused Pipe Ends**: Each process should close pipe ends it doesn't use. If you don't:
   - Commands won't receive EOF and will hang waiting for more input
   - You'll leak file descriptors, eventually hitting system limits

3. **Double-Collecting Heredocs**: Collecting heredocs in both the parent and child processes causes duplicate prompts and corrupted input.

4. **Signal Handling During Heredoc**: If a user presses Ctrl+C during heredoc input, you must:
   - Close the pipe
   - Mark the file descriptor as invalid (-1)
   - Set the exit status appropriately (130)
   - Ensure the parent process knows the collection failed

5. **Wrong Order of Dup2 and Close**: Always call dup2() before closing the original file descriptor.

## 6. Handling Standalone Heredocs

A standalone heredoc (`<< EOF` without a command) is a special case:
- Must still collect the heredoc input
- No command to attach the input to
- Should properly handle signals and update exit status
- Needs to close the heredoc pipe after collection

In bash, a standalone heredoc without a command is essentially a no-op after collecting the input.

## 7. The Importance of File Descriptor Management

File descriptors are a limited resource in Unix systems (typically limited to 1024 per process). Poor file descriptor management leads to:

1. **Resource Leaks**: Unclosed file descriptors accumulate until your program hits the system limit
2. **Hanging Processes**: Programs waiting on pipe data that will never arrive
3. **Data Corruption**: Writing to or reading from the wrong descriptors
4. **Security Vulnerabilities**: Leaking sensitive file handles to child processes


## 8. Key System Functions Used in Minishell

### fork()

**Function Signature:**
```c
pid_t fork(void);
```

**Purpose:**  
Creates a new process by duplicating the calling process (parent). The new process (child) is an exact copy of the parent process, including open file descriptors, register state, and memory.

**Return Values:**
- **Parent:** PID of the child process
- **Child:** 0
- **Error:** -1

**How Bash Uses It:**  
Bash uses `fork()` to create a new process for each command in a pipeline or for external commands. The parent shell waits for the child to complete while the child executes the command.

**Minishell Implementation:**
```c
pid = fork();
if (pid == 0) {
    // Child process code: redirect FDs, execute command
    execve(path, args, env);
    exit(EXIT_FAILURE); // Only reached if execve fails
} else {
    // Parent process code: wait for child to finish
    waitpid(pid, &status, 0);
    update_exit_status(status);
}
```

**Pitfalls:**
- Resources must be freed correctly in both parent and child
- Signal handlers are inherited and may need to be reset
- If a child never exits, the parent can hang waiting for it

### execve()

**Function Signature:**
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

**Purpose:**  
Replaces the current process image with a new process image specified by the given path. When successfully called, it never returns to the calling process.

**Parameters:**
- **pathname:** Path to the executable file
- **argv:** NULL-terminated array of strings representing arguments
- **envp:** NULL-terminated array of strings representing environment variables

**Return Value:**  
Only returns -1 on error. On success, it never returns.

**How Bash Uses It:**  
Bash uses `execve()` after `fork()` to replace the child process with the command to be executed. The parent shell continues running, while the child becomes the new command.

**Minishell Implementation:**
```c
char *path = get_cmd_path(cmd, env); // Find full path to executable
char **args = prepare_args(cmd); // Prepare arguments array
char **envp = env_to_array(env_list); // Convert env list to array

execve(path, args, envp);
// If we reach here, execve failed
ft_putstr_fd("minishell: command not found: ", 2);
exit(EXIT_FAILURE);
```

**Pitfalls:**
- Always check if the command exists before calling execve
- All memory allocated in the child will be discarded after execve
- File descriptors remain open unless explicitly closed
- Environment must be properly formatted as NULL-terminated array

### waitpid()

**Function Signature:**
```c
pid_t waitpid(pid_t pid, int *status, int options);
```

**Purpose:**  
Waits for a specific child process to change state (usually to terminate).

**Parameters:**
- **pid:** PID of the child to wait for (-1 for any child)
- **status:** Pointer to store exit status information
- **options:** Modifiers like WNOHANG (non-blocking wait)

**Return Value:**
- PID of the child that changed state
- 0 if WNOHANG was used and no child changed state
- -1 on error

**How Bash Uses It:**  
Bash uses `waitpid()` to wait for commands to finish and retrieve their exit status. For pipelines, it waits for each process in the pipeline.

**Minishell Implementation:**
```c
// Wait for a single command
waitpid(pid, &status, 0);
update_exit_status(status);

// Wait for all commands in a pipeline
while (i < cmd_count) {
    waitpid(pids[i], &status, 0);
    // For pipelines, only the last command's status matters
    if (i == cmd_count - 1)
        update_exit_status(status);
    i++;
}
```

**Pitfalls:**
- Forgetting to check WIFEXITED() before using WEXITSTATUS()
- Not properly handling signals in status
- Not updating the global exit status for $?

### pipe()

**Function Signature:**
```c
int pipe(int pipefd[2]);
```

**Purpose:**  
Creates a unidirectional data channel (pipe) for interprocess communication.

**Parameters:**
- **pipefd:** Array to store two file descriptors:
  - pipefd[0]: Read end of pipe
  - pipefd[1]: Write end of pipe

**Return Value:**
- 0 on success
- -1 on error

**How Bash Uses It:**  
Bash creates pipes to connect commands in a pipeline. The stdout of one process is connected to the stdin of the next process.

**Minishell Implementation:**
```c
// Create pipe for connecting commands
int pipe_fd[2];
if (pipe(pipe_fd) < 0) {
    ft_putstr_fd("minishell: pipe error\n", 2);
    return;
}

// After fork, in child1 (left command):
close(pipe_fd[0]); // Close read end
dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
close(pipe_fd[1]);

// After fork, in child2 (right command):
close(pipe_fd[1]); // Close write end
dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin from pipe
close(pipe_fd[0]);
```

**Pitfalls:**
- Not closing unused pipe ends causes resource leaks
- If a pipe's write end is closed but the read end remains open, read() will return 0 (EOF)
- If all write ends are closed, processes reading from the pipe receive EOF
- If all read ends are closed, processes writing to the pipe receive SIGPIPE

### dup() and dup2()

**Function Signatures:**
```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

**Purpose:**  
- **dup():** Creates a copy of a file descriptor
- **dup2():** Creates a copy of a file descriptor, but using a specific new descriptor number

**Parameters:**
- **oldfd:** Original file descriptor to duplicate
- **newfd:** (dup2 only) Desired file descriptor number for the duplicate

**Return Value:**
- New file descriptor on success
- -1 on error

**How Bash Uses Them:**  
Bash uses these functions to redirect input/output for commands. For example, redirecting stdout to a file or connecting commands in a pipeline.

**Minishell Implementation:**
```c
// Redirect stdin from file
int fd = open(file_path, O_RDONLY);
if (fd < 0) {
    ft_putstr_fd("minishell: No such file or directory\n", 2);
    exit(EXIT_FAILURE);
}
dup2(fd, STDIN_FILENO);
close(fd); // Important: close the original after dup2

// Redirect stdout to file (with truncate)
int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, STDOUT_FILENO);
close(fd);

// Redirect stdout to file (with append)
int fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
dup2(fd, STDOUT_FILENO);
close(fd);
```

**Pitfalls:**
- Failing to close the original file descriptor after dup2() leads to resource leaks
- Always check for errors when opening files
- The order matters: call dup2() before closing the original descriptor
- Remember to set appropriate permissions when creating files

### signal()

**Function Signature:**
```c
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

**Purpose:**  
Sets a function to handle a specific signal.

**Parameters:**
- **signum:** Signal number to handle (e.g., SIGINT for Ctrl+C)
- **handler:** Function to call when signal is received, or SIG_IGN/SIG_DFL

**Return Value:**
- Previous signal handler on success
- SIG_ERR on error

**How Bash Uses It:**  
Bash sets up signal handlers to manage user interrupts (Ctrl+C, Ctrl+Z, Ctrl+\) and other signals differently depending on context.

**Minishell Implementation:**
```c
// Interactive mode (at prompt)
void set_signals_interactive(void)
{
    signal(SIGINT, handle_sigint);  // Ctrl+C: clear line, show new prompt
    signal(SIGQUIT, SIG_IGN);       // Ctrl+\: ignore
}

// Child process execution
void set_signals_in_child(void)
{
    signal(SIGINT, SIG_DFL);   // Ctrl+C: default behavior (terminate)
    signal(SIGQUIT, SIG_DFL);  // Ctrl+\: default behavior (core dump)
}

// Handle Ctrl+C at prompt
void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);         // New line
    rl_on_new_line();          // Tell readline we moved to a new line
    rl_replace_line("", 0);    // Clear the input line
    rl_redisplay();            // Redisplay the prompt
    g_exit_status = 130;       // Set appropriate exit status
}
```

**Pitfalls:**
- Signal handlers should be kept simple and avoid complex logic
- Global variables modified in signal handlers should be declared volatile
- Some functions are not safe to call from signal handlers
- Signal dispositions are inherited across fork() but reset by execve()

## 9. Understanding Exit Codes in Bash

In bash, exit codes follow specific conventions:

- **0:** Success
- **1-125:** Program-defined error codes
- **126:** Command found but not executable
- **127:** Command not found
- **128+n:** Process terminated by signal n
- **130:** Process terminated by Ctrl+C (SIGINT, signal 2)
- **131:** Process terminated by Ctrl+\ (SIGQUIT, signal 3)
- **137:** Process terminated by SIGKILL (signal 9)


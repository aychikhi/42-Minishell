# 42 Minishell

`minishell` is our take on a small interactive shell inspired by bash.
We built it as a duo project at 42 School, with a strong focus on parsing, process control, and clean file descriptor management.

**Authors:** [@aychikhi](https://github.com/aychikhi) and [@ayaarab](https://github.com/ayaarab)

---

## What this project does

Our shell reads commands, parses them, expands environment variables, applies redirections, and executes either builtins or external programs.

It supports:

- Interactive prompt with command history (`readline`)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quotes
- Pipelines (`|`)
- Redirections (`>`, `>>`, `<`, `<<`)
- Heredoc handling with signal-safe behavior
- Wildcard expansion (`*`)
- Builtins:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

---

## Build and run

### Requirements

- `cc` (or `clang`)
- `make`
- `readline` library

### Compile

```bash
make
```

### Launch

```bash
./minishell
```

---

## Quick usage examples

```bash
echo "hello minishell"
export NAME=aya
echo "hi $NAME"
cat infile | grep 42 | wc -l
cat << EOF
line 1
line 2
EOF
```

---

## Project structure

- `src/parsing/` → tokenization, syntax checks, expansion, command building
- `src/execution/` → pipelines, redirections, heredoc, external execution, signals
- `src/execution/builtins/` → builtin command implementations
- `includes/` → shared structures and function prototypes

---

## Notes from our implementation

- Exit statuses follow bash conventions (including signal-based `128 + signal` behavior).
- Heredocs are collected before pipeline execution to avoid broken input flow.
- We paid close attention to closing unused pipe ends to prevent hangs and FD leaks.

---

## Known limitations

This project follows the pedagogical scope of 42 Minishell and is not a full bash replacement.
Some advanced shell features are intentionally out of scope.

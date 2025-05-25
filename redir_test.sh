#!/bin/bash

MINISHELL=./minishell
TEST_DIR=testdir
mkdir -p $TEST_DIR
cd $TEST_DIR || exit 1

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'
TOTAL=0
PASS=0
FAIL=0

describe() {
    echo -e "\n$1"
}

test_case() {
    ((TOTAL++))
    local testname="$1"
    local command="$2"
    local expected_status="${3:-0}"
    local verify="${4:-true}"
    local setup="${5:-}"

    # Setup
    eval "$setup" 2>/dev/null

    # Run in bash to get reference
    local bash_output=$(bash -c "$command" 2>&1)
    local bash_status=$?
    local bash_stdout=$(printf "%s" "$bash_output" | sed -n '/^STDOUT:/,$p' | sed '1d')
    local bash_stderr=$(printf "%s" "$bash_output" | sed '/^STDOUT:/Q' | sed '$d')

    # Run in minishell
    local shell_output=$($MINISHELL -c "$command" 2>&1)
    local shell_status=$?
    local shell_stdout=$(printf "%s" "$shell_output" | sed -n '/^STDOUT:/,$p' | sed '1d')
    local shell_stderr=$(printf "%s" "$shell_output" | sed '/^STDOUT:/Q' | sed '$d')

    # Verification
    local status_ok=0
    [ "$shell_status" -eq "$expected_status" ] && status_ok=1

    local verify_ok=0
    eval "$verify" >/dev/null 2>&1 && verify_ok=1

    # Compare with bash if no specific verification
    if [ -z "$verify" ]; then
        [ "$shell_stdout" = "$bash_stdout" ] && [ "$shell_stderr" = "$bash_stderr" ] && verify_ok=1
    fi

    if [ $status_ok -eq 1 ] && [ $verify_ok -eq 1 ]; then
        echo -e "${GREEN}PASS: $testname${NC}"
        ((PASS++))
    else
        echo -e "${RED}FAIL: $testname${NC}"
        echo "   Command: $command"
        [ $status_ok -eq 0 ] && echo "   Expected status: $expected_status, Got: $shell_status"
        [ $verify_ok -eq 0 ] && echo "   Verification failed"
        ((FAIL++))
    fi

    # Cleanup
    rm -f *.txt testfile* f1 f2 input.txt output.txt
}

# Basic redirections
describe "Basic redirection tests"
test_case "Simple truncate" "echo hello > testfile" 0 "grep hello testfile"
test_case "File append" "echo world >> testfile" 0 "grep world testfile"
test_case "Input redirection" "cat < testfile" 0 "[ ! -z '$shell_stdout' ]"

# Edge cases
describe "Edge cases"
test_case "Multiple outputs" "echo test > f1 > f2" 0 "[ -s f2 ] && [ ! -s f1 ]"
test_case "No space redirection" "echo test>nsfile" 0 "grep test nsfile"
test_case "Redirect empty" "> emptyfile" 0 "[ -f emptyfile ] && [ ! -s emptyfile ]"

# Error cases
describe "Error handling"
test_case "Bad input file" "cat < nonexistent" 1 "" ""
test_case "Write to directory" "echo test > ." 1 "" ""
test_case "Permission denied" "touch protected; chmod 000 protected; echo test > protected" 1 "" ""

# Complex cases
describe "Complex redirections"
test_case "Combined redirects" "cat < input.txt > output.txt" 0 "[ -f output.txt ]" "echo 'content' > input.txt"
test_case "Append and truncate" "echo a > f; echo b >> f; echo c > f" 0 "grep -q '^c$' f"

# Special characters
describe "Special filenames"
test_case "Space in filename" "echo test > 'spaced file'" 0 "grep test 'spaced file'"
test_case "Special chars" "echo \$PATH > \$file" 0 "grep '\$PATH' \$file" "file='special\$file'"

# Cleanup and results
cd .. && rm -rf $TEST_DIR
echo -e "\nResults:"
echo -e "Total: $TOTAL"
echo -e "${GREEN}Passed: $PASS${NC}"
echo -e "${RED}Failed: $FAIL${NC}"

exit $FAIL
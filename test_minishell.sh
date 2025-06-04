#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_minishell.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 10:00:00 by student           #+#    #+#              #
#    Updated: 2024/01/01 10:00:00 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Script de test pour minishell
# Usage: ./test_minishell.sh

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

MINISHELL="./minishell"
PASSED=0
FAILED=0

# Function to print test results
print_test_result() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}: $2"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAIL${NC}: $2"
        ((FAILED++))
    fi
}

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_exit_code="${3:-0}"
    
    echo -e "\n${BLUE}Testing${NC}: $test_name"
    echo -e "${YELLOW}Command${NC}: $command"
    
    # Run the command
    echo "$command" | timeout 5 $MINISHELL > /dev/null 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq $expected_exit_code ]; then
        print_test_result 0 "$test_name"
    else
        print_test_result 1 "$test_name (expected exit code $expected_exit_code, got $exit_code)"
    fi
}

# Function to test with file output
test_with_output() {
    local test_name="$1"
    local command="$2"
    local expected_output="$3"
    
    echo -e "\n${BLUE}Testing${NC}: $test_name"
    echo -e "${YELLOW}Command${NC}: $command"
    
    # Run the command and capture output
    local actual_output=$(echo "$command" | timeout 5 $MINISHELL 2>/dev/null | tail -n +3)
    
    if [ "$actual_output" = "$expected_output" ]; then
        print_test_result 0 "$test_name"
    else
        print_test_result 1 "$test_name (output mismatch)"
        echo -e "  Expected: '$expected_output'"
        echo -e "  Got: '$actual_output'"
    fi
}

echo -e "${BLUE}============================================${NC}"
echo -e "${BLUE}       MINISHELL TEST SUITE                ${NC}"
echo -e "${BLUE}============================================${NC}"

# Check if minishell exists
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: $MINISHELL not found. Please compile first with 'make'${NC}"
    exit 1
fi

# Make sure it's executable
chmod +x "$MINISHELL"

echo -e "\n${BLUE}Testing basic functionality...${NC}"

# Test 1: Basic echo
test_with_output "echo command" "echo hello" "hello"

# Test 2: pwd command
run_test "pwd command" "pwd"

# Test 3: env command
run_test "env command" "env"

# Test 4: exit command
run_test "exit command" "exit" 0

# Test 5: export command
run_test "export command" "export TEST=hello"

# Test 6: unset command
run_test "unset command" "unset TEST"

# Test 7: cd command
run_test "cd command" "cd /tmp"

# Test 8: echo with -n option
test_with_output "echo -n command" "echo -n hello" "hello"

echo -e "\n${BLUE}Testing pipes...${NC}"

# Test 9: Simple pipe
run_test "simple pipe" "echo hello | cat"

# Test 10: Multiple pipes
run_test "multiple pipes" "echo hello | cat | cat"

echo -e "\n${BLUE}Testing redirections...${NC}"

# Test 11: Output redirection
run_test "output redirection" "echo hello > test_output.txt"

# Test 12: Input redirection (if test_output.txt exists)
if [ -f "test_output.txt" ]; then
    run_test "input redirection" "cat < test_output.txt"
    rm -f test_output.txt
fi

# Test 13: Append redirection
run_test "append redirection" "echo hello >> test_append.txt"
rm -f test_append.txt

echo -e "\n${BLUE}Testing environment variables...${NC}"

# Test 14: Environment variable expansion
run_test "environment variable" "echo \$HOME"

# Test 15: Exit code variable
run_test "exit code variable" "echo \$?"

echo -e "\n${BLUE}Testing error handling...${NC}"

# Test 16: Non-existent command
run_test "non-existent command" "nonexistentcommand" 127

# Test 17: Syntax error
run_test "syntax error - pipe at end" "echo hello |" 1

echo -e "\n${BLUE}Testing quotes...${NC}"

# Test 18: Single quotes
test_with_output "single quotes" "echo 'hello world'" "hello world"

# Test 19: Double quotes
test_with_output "double quotes" "echo \"hello world\"" "hello world"

echo -e "\n${BLUE}============================================${NC}"
echo -e "${BLUE}           TEST RESULTS                     ${NC}"
echo -e "${BLUE}============================================${NC}"

echo -e "\n${GREEN}Tests passed: $PASSED${NC}"
echo -e "${RED}Tests failed: $FAILED${NC}"

TOTAL=$((PASSED + FAILED))
echo -e "Total tests: $TOTAL"

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed! Your minishell is working correctly.${NC}"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed. Please check your implementation.${NC}"
    exit 1
fi
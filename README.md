# Testing Documentation

This document describes the testing setup and procedures for the Factory Equipment Management System.

## Test Structure

The testing system consists of two main components:
1. Unit Tests (`tests/unit_tests.c`)
2. End-to-End Tests (`tests/e2e_tests.c`)

### Unit Tests

Unit tests verify individual components and functions of the system. Each core function has its own test suite:

- `test_readCSVToArray()`: Tests CSV file reading functionality
  - Tests normal case with valid data
  - Tests empty file case
  - Tests file with invalid format

- `test_addMachine()`: Tests machine addition functionality
  - Tests adding first entry
  - Tests adding to existing list
  - Tests with long input validation

- `test_searchMachine()`: Tests search functionality
  - Tests searching by name
  - Tests searching by code
  - Tests searching by status
  - Tests with non-existent data

- `test_updateMachine()`: Tests update functionality
  - Tests normal update case
  - Tests with invalid machine code
  - Tests with invalid date format

- `test_deleteRecordCSV()`: Tests deletion functionality
  - Tests normal deletion
  - Tests deleting non-existent record
  - Tests with empty list

### End-to-End Tests

The E2E tests verify the complete workflow of the application, testing multiple functions working together:

1. Initial Setup
   - Creates test environment
   - Prepares test files

2. Workflow Tests
   - Adding multiple machines
   - Searching for machines
   - Updating machine information
   - Deleting machines
   - Verifying final state

## Running the Tests

### Prerequisites
- GCC compiler
- Make utility (optional)

### Compiling and Running Unit Tests
```bash
gcc -o run_unit_tests tests/unit_tests.c src/function.c src/machine.c src/validation.c -I src
./run_unit_tests
```

### Compiling and Running E2E Tests
```bash
gcc -o run_e2e_tests tests/e2e_tests.c src/function.c src/machine.c src/validation.c -I src
./run_e2e_tests
```

### Expected Output

For unit tests, you should see output like:
```
Running unit tests...

Testing readCSVToArray...
readCSVToArray tests passed!

Testing addMachine...
addMachine tests passed!

[...]

All unit tests passed successfully!
```

For E2E tests:
```
Running end-to-end test scenario...

Test 1: Adding first machine...
Test 1 passed: First machine added successfully

[...]

All end-to-end tests completed successfully!
```

## Test Data

The tests use the following test data files:
- `test.csv`: Used for unit tests
- `e2e_test.csv`: Used for end-to-end tests
- `mock_input.txt`: Used to simulate user input

These files are created and cleaned up automatically during test execution.

## Adding New Tests

To add new test cases:

1. For unit tests:
   - Add new test function in `unit_tests.c`
   - Add function call in main()
   - Update this documentation

2. For E2E tests:
   - Add new test scenario in `e2e_tests.c`
   - Update mock input data if needed
   - Update this documentation

## Troubleshooting

Common issues and solutions:

1. Failed to open file
   - Check file permissions
   - Verify correct file paths

2. Memory leaks
   - Use valgrind for detection
   - Ensure proper cleanup in tests

3. Input/Output redirection issues
   - Check mock input file format
   - Verify stdin restoration
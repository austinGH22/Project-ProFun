###RUN PROGRAM
```bash
gcc main.c function.c -o output
./output 
```

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


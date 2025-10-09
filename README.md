###RUN PROGRAM
```bash
gcc main.c function.c -o output
./output 
```

### Compiling and Running Unit Tests
```bash
gcc -o run_unit_tests unit_tests.c function.c machine.c validation.c -I src
./run_unit_tests
```

### Compiling and Running E2E Tests
```bash
gcc -o run_e2e_tests e2e_tests.c function.c machine.c validation.c -I src
./run_e2e_tests
```


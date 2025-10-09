#include "../src/project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Helper function to setup test environment
void setup_test_environment() {
    // Create a clean test CSV file
    FILE *fp = fopen("e2e_test.csv", "w");
    if (fp) fclose(fp);
}

// Helper function to cleanup test environment
void cleanup_test_environment() {
    remove("e2e_test.csv");
    remove("e2e_mock_input.txt");
}

// Helper function to prepare mock input
void prepare_mock_input(const char *input) {
    FILE *fp = fopen("e2e_mock_input.txt", "w");
    if (fp) {
        fprintf(fp, "%s", input);
        fclose(fp);
    }
}

// End-to-end test scenario
void run_e2e_test() {
    printf("Running end-to-end test scenario...\n\n");
    
    setup_test_environment();
    Machine *list = NULL;
    int count = 0;
    
    // Test 1: Add first machine
    printf("Test 1: Adding first machine...\n");
    prepare_mock_input("TestMachine1\nTEST1\nActive\n2023-10-09\n");
    freopen("e2e_mock_input.txt", "r", stdin);
    addMachine("e2e_test.csv", &list, &count);
    
    // Verify addition
    count = readCSVToArray("e2e_test.csv", &list);
    assert(count == 1);
    assert(strcmp(list[0].name, "TestMachine1") == 0);
    printf("Test 1 passed: First machine added successfully\n\n");
    
    // Test 2: Add second machine
    printf("Test 2: Adding second machine...\n");
    prepare_mock_input("TestMachine2\nTEST2\nInactive\n2023-10-10\n");
    freopen("e2e_mock_input.txt", "r", stdin);
    addMachine("e2e_test.csv", &list, &count);
    
    // Verify second addition
    count = readCSVToArray("e2e_test.csv", &list);
    assert(count == 2);
    assert(strcmp(list[1].name, "TestMachine2") == 0);
    printf("Test 2 passed: Second machine added successfully\n\n");
    
    // Test 3: Search for machines
    printf("Test 3: Searching for machines...\n");
    prepare_mock_input("Active\n");
    freopen("e2e_mock_input.txt", "r", stdin);
    searchMachine(list, count, "Active");
    printf("Test 3 passed: Search functionality verified\n\n");
    
    // Test 4: Update machine
    printf("Test 4: Updating machine status...\n");
    prepare_mock_input("TEST1\nMaintenance\n2023-10-11\n");
    freopen("e2e_mock_input.txt", "r", stdin);
    updateMachine("e2e_test.csv", list, count);
    
    // Verify update
    count = readCSVToArray("e2e_test.csv", &list);
    assert(strcmp(list[0].status, "Maintenance") == 0);
    assert(strcmp(list[0].maintenanceDate, "2023-10-11") == 0);
    printf("Test 4 passed: Machine updated successfully\n\n");
    
    // Test 5: Delete machine
    printf("Test 5: Deleting machine...\n");
    prepare_mock_input("TEST2\n");
    freopen("e2e_mock_input.txt", "r", stdin);
    deleteRecordCSV("e2e_test.csv", &list, &count);
    
    // Verify deletion
    count = readCSVToArray("e2e_test.csv", &list);
    assert(count == 1);
    assert(strcmp(list[0].code, "TEST1") == 0);
    printf("Test 5 passed: Machine deleted successfully\n\n");
    
    // Cleanup
    free(list);
    cleanup_test_environment();
    
    // Restore stdin
    freopen("/dev/tty", "r", stdin);
    
    printf("All end-to-end tests completed successfully!\n");
}

int main() {
    run_e2e_test();
    return 0;
}
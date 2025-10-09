#include "../src/project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Helper functions for testing
void create_test_file(const char *filename, const char *content) {
    FILE *fp = fopen(filename, "w");
    if (fp) {
        fprintf(fp, "%s", content);
        fclose(fp);
    }
}

void delete_test_file(const char *filename) {
    remove(filename);
}

// Test cases for readCSVToArray
void test_readCSVToArray() {
    printf("Testing readCSVToArray...\n");
    
    const char *test_data = "Machine1,CODE1,Active,2023-10-09\n"
                           "Machine2,CODE2,Inactive,2023-10-10\n";
    create_test_file("test.csv", test_data);

    Machine *list = NULL;
    int count = readCSVToArray("test.csv", &list);
    
    assert(count == 2);
    assert(strcmp(list[0].name, "Machine1") == 0);
    assert(strcmp(list[0].code, "CODE1") == 0);
    assert(strcmp(list[0].status, "Active") == 0);
    assert(strcmp(list[0].maintenanceDate, "2023-10-09") == 0);
    
    assert(strcmp(list[1].name, "Machine2") == 0);
    assert(strcmp(list[1].code, "CODE2") == 0);
    assert(strcmp(list[1].status, "Inactive") == 0);
    assert(strcmp(list[1].maintenanceDate, "2023-10-10") == 0);

    free(list);
    delete_test_file("test.csv");
    printf("readCSVToArray tests passed!\n");
}

// Test cases for addMachine
void test_addMachine() {
    printf("Testing addMachine...\n");
    
    create_test_file("test_add.csv", "");
    
    Machine *list = NULL;
    int count = 0;
    
    // Test adding a new machine
    FILE *mock_input = fopen("mock_input.txt", "w");
    fprintf(mock_input, "TestMachine\nTEST1\nActive\n2023-10-09\n");
    fclose(mock_input);
    
    // Redirect stdin to mock input
    freopen("mock_input.txt", "r", stdin);
    
    addMachine("test_add.csv", &list, &count);
    
    assert(count == 1);
    assert(strcmp(list[0].name, "TestMachine") == 0);
    assert(strcmp(list[0].code, "TEST1") == 0);
    assert(strcmp(list[0].status, "Active") == 0);
    assert(strcmp(list[0].maintenanceDate, "2023-10-09") == 0);
    
    free(list);
    delete_test_file("test_add.csv");
    delete_test_file("mock_input.txt");
    
    // Restore stdin
    freopen("/dev/tty", "r", stdin);
    printf("addMachine tests passed!\n");
}

// Test cases for searchMachine
void test_searchMachine() {
    printf("Testing searchMachine...\n");
    
    Machine test_machines[] = {
        {"Machine1", "CODE1", "Active", "2023-10-09"},
        {"Machine2", "CODE2", "Inactive", "2023-10-10"}
    };
    
    // Test searching by name
    char keyword[] = "Machine1";
    searchMachine(test_machines, 2, keyword);
    
    // Test searching by status
    char keyword2[] = "Active";
    searchMachine(test_machines, 2, keyword2);
    
    printf("searchMachine tests passed!\n");
}

// Test cases for updateMachine
void test_updateMachine() {
    printf("Testing updateMachine...\n");
    
    const char *test_data = "Machine1,CODE1,Active,2023-10-09\n";
    create_test_file("test_update.csv", test_data);
    
    Machine *list = NULL;
    int count = readCSVToArray("test_update.csv", &list);
    
    // Set up mock input for update
    FILE *mock_input = fopen("mock_input.txt", "w");
    fprintf(mock_input, "CODE1\nInactive\n2023-10-10\n");
    fclose(mock_input);
    
    // Redirect stdin to mock input
    freopen("mock_input.txt", "r", stdin);
    
    updateMachine("test_update.csv", list, count);
    
    // Read the updated file to verify changes
    Machine *updated_list = NULL;
    count = readCSVToArray("test_update.csv", &updated_list);
    
    assert(strcmp(updated_list[0].status, "Inactive") == 0);
    assert(strcmp(updated_list[0].maintenanceDate, "2023-10-10") == 0);
    
    free(list);
    free(updated_list);
    delete_test_file("test_update.csv");
    delete_test_file("mock_input.txt");
    
    // Restore stdin
    freopen("/dev/tty", "r", stdin);
    printf("updateMachine tests passed!\n");
}

// Test cases for deleteRecordCSV
void test_deleteRecordCSV() {
    printf("Testing deleteRecordCSV...\n");
    
    const char *test_data = "Machine1,CODE1,Active,2023-10-09\n"
                           "Machine2,CODE2,Inactive,2023-10-10\n";
    create_test_file("test_delete.csv", test_data);
    
    Machine *list = NULL;
    int count = readCSVToArray("test_delete.csv", &list);
    
    // Set up mock input for delete
    FILE *mock_input = fopen("mock_input.txt", "w");
    fprintf(mock_input, "CODE1\n");
    fclose(mock_input);
    
    // Redirect stdin to mock input
    freopen("mock_input.txt", "r", stdin);
    
    deleteRecordCSV("test_delete.csv", &list, &count);
    
    assert(count == 1);
    assert(strcmp(list[0].name, "Machine2") == 0);
    
    free(list);
    delete_test_file("test_delete.csv");
    delete_test_file("mock_input.txt");
    
    // Restore stdin
    freopen("/dev/tty", "r", stdin);
    printf("deleteRecordCSV tests passed!\n");
}

// Main test runner
int main() {
    printf("Running unit tests...\n\n");
    
    test_readCSVToArray();
    test_addMachine();
    test_searchMachine();
    test_updateMachine();
    test_deleteRecordCSV();
    
    printf("\nAll unit tests passed successfully!\n");
    return 0;
}
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

void trimNewline(char *str) {
    size_t len = strlen(str);
    if(len > 0 && (str[len-1] == '\n' || str[len-1]=='\r'))
        str[len-1] = '\0';
}

void toLowerCase(char *str) {
    for(int i=0; str[i]; i++)
        str[i] = tolower((unsigned char)str[i]);
}

//Function read
int readCSVToArray(const char *filename, Machine **list) {
    FILE *fp = fopen(filename, "r");
    if(!fp) 
    return 0;

    Machine *temp = malloc(sizeof(Machine));
    int count = 0;
    char line[MAX_LINE];

    while(fgets(line, sizeof(line), fp)) {
        trimNewline(line);
        if(sscanf(line, " %[^,],%[^,],%[^,],%[^,\n]",
                  temp[count].name,
                  temp[count].code,
                  temp[count].status,
                  temp[count].maintenanceDate) == 4) {
            count++;
            temp = realloc(temp, (count+1)*sizeof(Machine));
        }
    }

    fclose(fp);
    *list = temp; 
    return count;
}

//Function Add
void addMachine(const char *filename, Machine **list, int *count) {
    Machine newMachine;

    printf("Enter Machine Name: ");
    scanf(" %[^\n]", newMachine.name);

    printf("Enter Machine ID: ");
    scanf("%s", newMachine.code);

    printf("Enter Status: ");
    scanf(" %[^\n]", newMachine.status);

    printf("Enter Maintenance Date (YYYY-MM-DD): ");
    scanf("%s", newMachine.maintenanceDate);

    *list = realloc(*list, (*count+1)*sizeof(Machine));
    (*list)[*count] = newMachine;
    (*count)++;

    FILE *fp = fopen(filename, "a");
    if(fp) {
        fprintf(fp, "%s,%s,%s,%s\n",
                newMachine.name,
                newMachine.code,
                newMachine.status,
                newMachine.maintenanceDate);
        fclose(fp);
        printf("Added successfully!\n");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
         printf("\nPress Enter to return to menu...");
        getchar();

    } else {
        printf("Failed to open CSV.\n");
    }
}

//Function Search
void searchMachine(Machine *list, int count, char *keyword) {
    int found=0;
    char kw[MAX_FIELD];       
    strcpy(kw, keyword);
    toLowerCase(kw);

    printf("\n--------------- SEARCH RESULT ---------------\n");
    for(int i=0;i<count;i++){
        char n[MAX_FIELD], c[MAX_FIELD], s[MAX_FIELD], d[MAX_FIELD];
        strcpy(n,list[i].name);
        strcpy(c,list[i].code);
        strcpy(s,list[i].status);
        strcpy(d,list[i].maintenanceDate);
        toLowerCase(n); toLowerCase(c); toLowerCase(s); toLowerCase(d);

        if(strstr(n,kw) || strstr(c,kw) || strstr(s,kw) || strstr(d,kw)){
            printf("%d) %s | %s | %s | %s\n", i+1,
                   list[i].name,list[i].code,list[i].status,list[i].maintenanceDate);
            found=1;
        }
    }
    if(!found) printf("No results found for '%s'\n", keyword);
}

//Function update
void updateMachine(const char *filename, Machine *list, int count) {
    char keyword[MAX_FIELD];
    int index=-1;

    while(1){
        printf("\nSearch \"Name\" or \"Code\" or \"Status\" or \"Maintenance data\"for update (0 to return to menu) : ");
        getchar(); // clear buffer
        fgets(keyword, sizeof(keyword), stdin);
        trimNewline(keyword);
        if(strcmp(keyword,"0")==0) return;

        // search matching
        int foundIndexes[MAX_LINE], fcount=0;
        char kw[MAX_FIELD]; strcpy(kw,keyword); toLowerCase(kw);
        for(int i=0;i<count;i++){
            char n[MAX_FIELD], c[MAX_FIELD], s[MAX_FIELD], d[MAX_FIELD];
            strcpy(n,list[i].name); strcpy(c,list[i].code);
            strcpy(s,list[i].status); strcpy(d,list[i].maintenanceDate);
            toLowerCase(n); toLowerCase(c); toLowerCase(s); toLowerCase(d);
            if(strstr(n,kw)||strstr(c,kw)||strstr(s,kw)||strstr(d,kw)){
                fcount++;
                foundIndexes[fcount-1]=i;
                printf("%d) %s | %s | %s | %s\n", fcount,
                       list[i].name,list[i].code,list[i].status,list[i].maintenanceDate);
            }
        }
        if(fcount==0){
            printf("No match found.\n");
            continue;
        }

        int choice;
        printf("Choose number to update ( 1 or 2 or ... (0 to return to menu): ");
        scanf("%d",&choice);
        if(choice<1 || choice>fcount){ printf("Invalid choice.\n"); continue;}
        index=foundIndexes[choice-1];

        printf("Choose field to update:\n1) Name\n2) Code\n3) Status\n4) Maintenance Date\nChoice: ");
        int f;
        scanf("%d",&f);
        getchar(); 
        switch(f){
            case 1: printf("Enter new Name: "); fgets(list[index].name,MAX_FIELD,stdin); trimNewline(list[index].name); break;
            case 2: printf("Enter new Code: "); fgets(list[index].code,MAX_FIELD,stdin); trimNewline(list[index].code); break;
            case 3: printf("Enter new Status: "); fgets(list[index].status,MAX_FIELD,stdin); trimNewline(list[index].status); break;
            case 4: printf("Enter new Maintenance Date: "); fgets(list[index].maintenanceDate,MAX_FIELD,stdin); trimNewline(list[index].maintenanceDate); break;
            default: printf("Invalid field.\n"); continue;
        }

        // write all back to CSV
        FILE *fp=fopen(filename,"w");
        for(int i=0;i<count;i++){
            fprintf(fp,"%s,%s,%s,%s\n",
                    list[i].name,list[i].code,list[i].status,list[i].maintenanceDate);
        }
        fclose(fp);
        printf("Update successful!\n");
    }
}

//Function Delete
void deleteRecordCSV(const char *filename, Machine **list, int *count){
    char keyword[MAX_FIELD];
    while(1){
        printf("\nEnter keyword to search for delete : ");
        getchar(); fgets(keyword,sizeof(keyword),stdin); trimNewline(keyword);
        if(strcmp(keyword,"0")==0) return;

        int foundIndexes[MAX_LINE], fcount=0;
        char kw[MAX_FIELD]; strcpy(kw,keyword); toLowerCase(kw);
        for(int i=0;i<*count;i++){
            char n[MAX_FIELD], c[MAX_FIELD], s[MAX_FIELD], d[MAX_FIELD];
            strcpy(n,(*list)[i].name); strcpy(c,(*list)[i].code);
            strcpy(s,(*list)[i].status); strcpy(d,(*list)[i].maintenanceDate);
            toLowerCase(n); toLowerCase(c); toLowerCase(s); toLowerCase(d);
            if(strstr(n,kw)||strstr(c,kw)||strstr(s,kw)||strstr(d,kw)){
                fcount++;
                foundIndexes[fcount-1]=i;
                printf("%d) %s | %s | %s | %s\n", fcount,
                       (*list)[i].name,(*list)[i].code,(*list)[i].status,(*list)[i].maintenanceDate);
            }
        }
        if(fcount==0){ printf("No match found.\n"); continue;}

        int choice; printf("Choose number to delete ( 1 or 2 or ... ): "); scanf("%d",&choice);
        if(choice<1 || choice>fcount){ printf("Invalid choice.\n"); continue;}
        int index=foundIndexes[choice-1];

        printf("Are you sure to delete (Y/N)? ");
        while (getchar() != '\n');
        char confirm; scanf(" %c",&confirm); 
        if(confirm!='Y' && confirm!='y')
        { printf("Cancelled.\n"); return;}

        for(int i=index;i<*count-1;i++)
            (*list)[i]=(*list)[i+1];
        (*count)--;

        FILE *fp=fopen(filename,"w");
        for(int i=0;i<*count;i++)
            fprintf(fp,"%s,%s,%s,%s\n",
                    (*list)[i].name,(*list)[i].code,(*list)[i].status,(*list)[i].maintenanceDate);
        fclose(fp);

        printf("Delete successful!\n");
        return;
    }




}

//unit test *********************************************************************************** 
void create_test_csv() {
    FILE *fp = fopen(TEST_FILE, "w");
    assert(fp != NULL);
    fprintf(fp,
        "Drill Press,E001,Operational,2025-07-24\n"
        "Lathe Machine,E002,Stopped,2024-06-25\n"
        "Milling Machine,E003,Operational,2024-03-27\n"
    );
    fclose(fp);
}

void clear_csv() {
    FILE *fp = fopen(TEST_FILE, "w");
    assert(fp != NULL);
    fclose(fp);
}

// normal tests
void test_readCSVToArray_normal() {
    printf("\nRunning test_readCSV]ToArray_normal...\n");
    create_test_csv();

    Machine *list = NULL;
    int count = readCSVToArray(TEST_FILE, &list);

    assert(count == 3);
    assert(strcmp(list[0].name, "Drill Press") == 0);
    assert(strcmp(list[1].code, "E002") == 0);
    assert(strcmp(list[2].status, "Operational") == 0);
    assert(strcmp(list[2].maintenanceDate, "2024-03-27") == 0);

    printf("test_readCSVToArray_normal passed!\n");
    free(list);
}

void test_addMachine_normal() {
    printf("\nRunning test_addMachine_normal...\n");
    clear_csv();

    Machine *list = NULL;
    int count = 0;

    FILE *mockInput = fopen("mock_input.txt", "w");
    assert(mockInput != NULL);
    fputs("Test Machine\nE999\nOperational\n2030-01-01\n", mockInput);
    fclose(mockInput);

    freopen("mock_input.txt", "r", stdin);
    addMachine(TEST_FILE, &list, &count);

    Machine *list2 = NULL;
    int count2 = readCSVToArray(TEST_FILE, &list2);

    assert(count2 == 1);
    assert(strcmp(list2[0].name, "Test Machine") == 0);
    assert(strcmp(list2[0].code, "E999") == 0);
    assert(strcmp(list2[0].status, "Operational") == 0);
    assert(strcmp(list2[0].maintenanceDate, "2030-01-01") == 0);

    printf("test_addMachine_normal passed!\n");
    free(list);
    free(list2);
}

// Boundary tests
void test_readCSV_emptyFile() {
    printf("\nRunning test_readCSV_emptyFile...\n");
    clear_csv();

    Machine *list = NULL;
    int count = readCSVToArray(TEST_FILE, &list);

    assert(count == 0);
    printf("test_readCSV_emptyFile passed!\n");
    free(list);
}

void test_addMachine_firstEntry() {
    printf("\nRunning test_addMachine_firstEntry...\n");
    clear_csv();

    Machine *list = NULL;
    int count = 0;

    FILE *mockInput = fopen("mock_input.txt", "w");
    fputs("BoundaryMachine\nE001\nOperational\n2025-12-31\n", mockInput);
    fclose(mockInput);

    freopen("mock_input.txt", "r", stdin);
    addMachine(TEST_FILE, &list, &count);

    Machine *list2 = NULL;
    int count2 = readCSVToArray(TEST_FILE, &list2);

    assert(count2 == 1);
    assert(strcmp(list2[0].code, "E001") == 0);

    printf("test_addMachine_firstEntry passed!\n");
    free(list);
    free(list2);
}

// Extreme tests
void test_addMachine_longInput() {
    printf("\nRunning test_addMachine_longInput...\n");
    clear_csv();

    char longName[300];
    memset(longName, 'A', 299);
    longName[299] = '\0';

    Machine *list = NULL;
    int count = 0;

    FILE *mockInput = fopen("mock_input.txt", "w");
    fprintf(mockInput, "%s\nE123\nStopped\n2031-01-01\n", longName);
    fclose(mockInput);

    freopen("mock_input.txt", "r", stdin);
    addMachine(TEST_FILE, &list, &count);

    Machine *list2 = NULL;
    int count2 = readCSVToArray(TEST_FILE, &list2);

    assert(count2 == 1);
    assert(strncmp(list2[0].name, "A", 1) == 0);  // Should start with 'A'

    printf("test_addMachine_longInput passed!\n");
    free(list);
    free(list2);
}

void test_readCSV_invalidFormat() {
    printf("\nRunning test_readCSV_invalidFormat...\n");

    FILE *fp = fopen(TEST_FILE, "w");
    assert(fp != NULL);
    fprintf(fp, "Missing,Comma,Here\nBrokenLineWithoutEnoughFields\n");
    fclose(fp);

    Machine *list = NULL;
    int count = readCSVToArray(TEST_FILE, &list);

    assert(count >= 0); // Function should not crash
    printf("test_readCSV_invalidFormat passed!\n");

    free(list);
}

// memory safety tests
void test_memoryLeaks() {
    printf("\nRunning test_memoryLeaks...\n");
    create_test_csv();

    for (int i = 0; i < 100; i++) {
        Machine *list = NULL;
        int count = readCSVToArray(TEST_FILE, &list);
        free(list); // make sure every allocation freed
    }

    printf("test_memoryLeaks passed! (use Valgrind to confirm)\n");
}

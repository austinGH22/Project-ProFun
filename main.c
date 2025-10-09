#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main()
{
    Machine *list = NULL;
    int count = 0;
    int choice;
    char input[100];
    int c;

    count = readCSVToArray("data.csv", &list);
    while (1)
    {
        printf("\n======== Factory Equipment Management ========\n");
        printf("1) Read CSV\n2) Add Machine\n3) Search Machine\n4) Update Machine\n5) Delete Machine\n6) Exit\n7) Run Unit Tests\n");
        printf("Select an option (1-8) : ");

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        int isNumber = 1;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit((unsigned char)input[i]))
            {
                isNumber = 0;
                break;
            }
        }
        if (!isNumber)
        {
            printf("\n ! You can choose only integer(1-8)\n");
            continue;
        }
        choice = atoi(input);
        if (choice < 1 || choice > 8)
        {
            printf("\n ! Only numbers 1-8 can be used.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            free(list);
            list = NULL;
            count = readCSVToArray("data.csv", &list);
            if (count > 0)
            {
                printf("\n--------------- Machine List ---------------\n");
                printf("NAME  |  CODE  |  STATUS  |  MAINTENANCE DATA\n \n");
                for (int i = 0; i < count; i++)
                    printf("%s | %s | %s | %s\n",
                           list[i].name, list[i].code, list[i].status, list[i].maintenanceDate);
            }
            else
                printf("No data found.\n");
            printf("--------------------------------------------- \n");
            break;
        case 2:
            printf("--------------- ADD MENU ---------------\n");
            addMachine("data.csv", &list, &count);
            break;
        case 3:
            printf("search \"Name\" or \"Code\" or \"Status\" or \"Maintenance data\"for search: ");
            char kw[MAX_FIELD];
            if (!fgets(kw, MAX_FIELD, stdin))
            {
                continue;
            }
            kw[strcspn(kw, "\n")] = '\0';
            trimNewline(kw);
            if (strlen(kw) == 0)
            {
                printf("Input must not empty!");
                continue;
            }
            searchMachine(list, count, kw);
            break;
        case 4:
            if (count == 0)
            {
                printf("No data loaded. Read first.\n");
                break;
            }
            updateMachine("data.csv", list, count);
            break;
        case 5:
            if (count == 0)
            {
                printf("No data loaded. Read first.\n");
                break;
            }
            deleteRecordCSV("data.csv", &list, &count);
            break;
        case 6:
            free(list);
            printf("Exiting program...\n");
            return 0;
        case 7:
            printf("===== UNIT TEST START =====\n");
            test_readCSVToArray_normal();
            test_addMachine_normal();
            // Boundary Tests
            test_readCSV_emptyFile();
            test_addMachine_firstEntry();
            // Extreme Tests
            test_addMachine_longInput();
            test_readCSV_invalidFormat();
            // Memory Safety Test
            test_memoryLeaks();
            printf("\n===== ALL TESTS PASSED SUCCESSFULLY =====\n\n");
        case 8:
            //e2e_test();
            break;
        default:
            printf(" Invalid choice.\n");
        }
    }

    return 0;
}

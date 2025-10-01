#include "project.h" //import header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    Machine *list = NULL;
    int n = 0;
    int choice;

    // compusive only 1-5 choice
    do
    {
        printf("##### Factory Equipment Operation Management System #####\n");
        printf("Menu\n");
        printf("1)Search\n");
        printf("2)Add\n");
        printf("3)update\n");
        printf("4)Delete\n");
        printf("5)Exit Program\n");

        printf("Choose function (1-5):");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);

    switch (choice)
    {
    case 1:
        free(list); // ถ้ามี list เดิมอยู่แล้วให้เคลียร์ก่อน
        list = NULL;
        n = readCSVToArray("data.csv", &list);
        if (n > 0)
        {
            printf("✅ Loaded %d records from CSV.\n", n);
        }
        else
        {
            printf("⚠️ No data found.\n");
        }

        free(list); // คืน memory ที่ malloc/realloc ให้ไป
        
        if (n > 0)
        {
            printf("\n--- Machine List ---\n");
            for (int i = 0; i < n; i++)
            {
                printf("%s | %s | %s | %s\n",
                       list[i].name,
                       list[i].code,
                       list[i].status,
                       list[i].maintenanceDate);
            }
        }
        else
        {
            printf("⚠️ No data loaded. Please load first (option 1).\n");
        }
        return 0;
        break;
    case 2:
       
        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    default:
        break;
    }

    return 0;
}

#include "project.h" //import header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    Machine *list = NULL;
    int n = 0;
    int choice;
    // add
    int count = 0;
    // search
    char keyword[50];
    //update

    //delete 
    char deleteID[10];
    // compusive only 1-5 choice
    do
    {
        printf("##### Factory Equipment Operation Management System #####\n");
        printf("Menu\n");
        printf("1)Read\n");
        printf("2)Add\n");
        printf("3)Search\n");
        printf("4)Update\n");
        printf("5)Delete\n");
        printf("6)Exit Program\n");

        printf("Choose function (1-5):");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);

    switch (choice)
    {
    case 1:
        free(list);
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
        addMachine("data.csv", &list, &count);
        break;
    case 3: {
    while (getchar() != '\n');  // เคลียร์ buffer จาก scanf ก่อนหน้า

    printf("Enter keyword to search: ");
    fgets(keyword, sizeof(keyword), stdin);

    trimNewline(keyword);   // ตัด \n ออก
    toLowerCase(keyword);   // ทำเป็นตัวเล็กทั้งหมด

    if (strlen(keyword) == 0) {
        printf("⚠️ Please enter a keyword!\n");
    } else {
        searchMachine(list, count, keyword);
    }
    break;
}

    case 4:
    updateMachine("data.csv", list, count);
        break;
    case 5:
    printf("EquipmentCode that want to delete: ");
    scanf("%s", deleteID);
    deleteRecordCSV("data.csv", deleteID);
        break;
    case 6:
        break;
    default:
        break;
    }

    return 0;
}

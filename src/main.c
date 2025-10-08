#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Machine *list=NULL;
    int count=0;
    int choice;

    while(1){
        printf("\n===== Factory Equipment Management =====\n");
        printf("1) Read CSV\n2) Add Machine\n3) Search Machine\n4) Update Machine\n5) Delete Machine\n6) Exit\n");
        printf("Choose function (1-6): ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                free(list); list=NULL;
                count=readCSVToArray("data.csv",&list);
                if(count>0){
                    printf("\n--- Machine List ---\n");
                    for(int i=0;i<count;i++)
                        printf("%s | %s | %s | %s\n",
                               list[i].name,list[i].code,list[i].status,list[i].maintenanceDate);
                } else printf("⚠️ No data found.\n");
                break;
            case 2: addMachine("data.csv",&list,&count); break;
            case 3:
                if(count==0){ printf("⚠️ No data loaded. Read first.\n"); break;}
                {
                    char kw[MAX_FIELD]; getchar();
                    printf("Enter keyword to search: "); fgets(kw,MAX_FIELD,stdin); trimNewline(kw);
                    searchMachine(list,count,kw);
                }
                break;
            case 4:
                if(count==0){ printf("⚠️ No data loaded. Read first.\n"); break;}
                updateMachine("data.csv",list,count); break;
            case 5:
                if(count==0){ printf("⚠️ No data loaded. Read first.\n"); break;}
                deleteRecordCSV("data.csv",&list,&count); break;
            case 6:
                free(list); printf("👋 Exiting program...\n"); return 0;
            default: printf("❌ Invalid choice.\n");
        }
    }

    return 0;
}

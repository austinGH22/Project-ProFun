#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    int found=0;
    char kw[MAX_FIELD];       
    strcpy(kw, keyword);
    toLowerCase(kw);

    printf("\n--- Search Results ---\n");
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
        printf("\nSearch \"Name\" or \"Code\" or \"Status\" or \"Maintenance data\"for update (or '0' to return): ");
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
        printf("Choose number to update: ");
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
        printf("\nEnter keyword to search for delete (or '0' to return): ");
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
        if(fcount==0){ printf("❌ No match found.\n"); continue;}

        int choice; printf("Choose number to delete: "); scanf("%d",&choice);
        if(choice<1 || choice>fcount){ printf("❌ Invalid choice.\n"); continue;}
        int index=foundIndexes[choice-1];

        printf("Are you sure to delete (Y/N)? ");
        char confirm; scanf(" %c",&confirm);
        if(confirm!='Y' && confirm!='y'){ printf("❌ Cancelled.\n"); return;}

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

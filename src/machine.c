#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Validation functions
int validateMachineName(const char *name) {
    if (!name || strlen(name) == 0 || strlen(name) >= MAX_FIELD) {
        return 0;
    }
    return 1;
}

int validateMachineCode(const char *code) {
    if (!code || strlen(code) == 0 || strlen(code) >= MAX_FIELD) {
        return 0;
    }
    return 1;
}

int validateMachineStatus(const char *status) {
    if (!status || strlen(status) == 0 || strlen(status) >= MAX_FIELD) {
        return 0;
    }
    return 1;
}

int validateMaintenanceDate(const char *date) {
    if (!date || strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
        return 0;
    }
    
    // Check if all other characters are digits
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            return 0;
        }
    }
    return 1;
}

// Machine operations
Machine createMachine(const char *name, const char *code, const char *status, const char *date) {
    Machine machine = {0}; // Initialize all fields to zero/empty
    
    if (validateMachineName(name) && validateMachineCode(code) && 
        validateMachineStatus(status) && validateMaintenanceDate(date)) {
        strncpy(machine.name, name, MAX_FIELD-1);
        strncpy(machine.code, code, MAX_FIELD-1);
        strncpy(machine.status, status, MAX_FIELD-1);
        strncpy(machine.maintenanceDate, date, MAX_FIELD-1);
    }
    
    return machine;
}

void printMachine(const Machine *machine) {
    if (!machine) return;
    printf("%s | %s | %s | %s\n",
           machine->name, machine->code,
           machine->status, machine->maintenanceDate);
}

int compareMachines(const Machine *m1, const Machine *m2) {
    if (!m1 || !m2) return 0;
    return strcmp(m1->code, m2->code) == 0;
}

// File operations
int saveMachineToFile(const char *filename, const Machine *machine) {
    if (!filename || !machine) return 0;
    
    FILE *fp = fopen(filename, "a");
    if (!fp) return 0;
    
    fprintf(fp, "%s,%s,%s,%s\n",
            machine->name, machine->code,
            machine->status, machine->maintenanceDate);
    fclose(fp);
    return 1;
}

int loadMachinesFromFile(const char *filename, Machine **machines, int *count) {
    if (!filename || !machines || !count) return 0;
    
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;
    
    int capacity = 10;
    *count = 0;
    Machine *temp = malloc(capacity * sizeof(Machine));
    if (!temp) {
        fclose(fp);
        return 0;
    }
    
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        if (*count >= capacity) {
            capacity *= 2;
            Machine *new_temp = realloc(temp, capacity * sizeof(Machine));
            if (!new_temp) {
                free(temp);
                fclose(fp);
                return 0;
            }
            temp = new_temp;
        }
        
        char name[MAX_FIELD], code[MAX_FIELD], status[MAX_FIELD], date[MAX_FIELD];
        if (sscanf(line, " %49[^,],%49[^,],%49[^,],%49[^,\n]",
                   name, code, status, date) == 4) {
            temp[*count] = createMachine(name, code, status, date);
            (*count)++;
        }
    }
    
    if (*count > 0) {
        Machine *final = realloc(temp, *count * sizeof(Machine));
        if (final) temp = final;
    }
    
    fclose(fp);
    if (*machines) free(*machines);
    *machines = temp;
    return 1;
}
#ifndef MACHINE_H
#define MACHINE_H

#include "project.h"

// Machine validation functions
int validateMachineName(const char *name);
int validateMachineCode(const char *code);
int validateMachineStatus(const char *status);
int validateMaintenanceDate(const char *date);

// Machine operations
Machine createMachine(const char *name, const char *code, const char *status, const char *date);
void printMachine(const Machine *machine);
int compareMachines(const Machine *m1, const Machine *m2);

// File operations
int saveMachineToFile(const char *filename, const Machine *machine);
int loadMachinesFromFile(const char *filename, Machine **machines, int *count);

#endif // MACHINE_H
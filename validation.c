#include "validation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validateMenuChoice(const char *input) {
    if (!validateEmptyInput(input)) return 0;
    if (!validateNumericInput(input)) return 0;
    
    int choice = atoi(input);
    return (choice >= 1 && choice <= 6);
}

int validateInputLength(const char *input, int maxLength) {
    if (!input) return 0;
    return strlen(input) < maxLength;
}

int validateDateFormat(const char *date) {
    if (!date || strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    
    // Check year
    for (int i = 0; i < 4; i++)
        if (!isdigit(date[i])) return 0;
        
    // Check month
    for (int i = 5; i < 7; i++)
        if (!isdigit(date[i])) return 0;
        
    // Check day
    for (int i = 8; i < 10; i++)
        if (!isdigit(date[i])) return 0;
        
    // Convert and validate ranges
    int year = (date[0]-'0')*1000 + (date[1]-'0')*100 + (date[2]-'0')*10 + (date[3]-'0');
    int month = (date[5]-'0')*10 + (date[6]-'0');
    int day = (date[8]-'0')*10 + (date[9]-'0');
    
    if (year < 2000 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    
    return 1;
}

int validateEmptyInput(const char *input) {
    if (!input) return 0;
    return strlen(input) > 0;
}

int validateNumericInput(const char *input) {
    if (!input) return 0;
    for (int i = 0; input[i]; i++) {
        if (!isdigit(input[i])) return 0;
    }
    return 1;
}

void printInputTooLong(void) {
    printf("Error: Input is too long.\n");
}

void printInvalidDate(void) {
    printf("Error: Invalid date format. Use YYYY-MM-DD.\n");
}

void printEmptyInput(void) {
    printf("Error: Input cannot be empty.\n");
}

void printInvalidNumber(void) {
    printf("Error: Input must be a number.\n");
}

void printInvalidChoice(void) {
    printf("Error: Invalid menu choice.\n");
}
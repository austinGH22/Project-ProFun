#ifndef VALIDATION_H
#define VALIDATION_H

// Input validation functions
int validateMenuChoice(const char *input);
int validateInputLength(const char *input, int maxLength);
int validateDateFormat(const char *date);
int validateEmptyInput(const char *input);
int validateNumericInput(const char *input);

// Error message functions
void printInputTooLong(void);
void printInvalidDate(void);
void printEmptyInput(void);
void printInvalidNumber(void);
void printInvalidChoice(void);

#endif // VALIDATION_H
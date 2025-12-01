// log.h
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

extern const int MAX_STRING_SIZE;

char* exponentToString(int base, int exponent);
char* doubleToString(double value, char* format);
char* intToString(int value);
void writeTableRowToConsole(int columns, ...);
void writeTableRowToFile(FILE* file, int columns, ...);

#endif

// log.c
#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

const int MAX_STRING_SIZE = 256;

char *exponentToString(int base, int exponent) {
  char *string = (char *) malloc(MAX_STRING_SIZE * sizeof(char));

  snprintf(string, MAX_STRING_SIZE, "%d^%d", base, exponent);

  return string;
}

char *doubleToString(double value, char *format) {
  char *string = (char *) malloc(MAX_STRING_SIZE * sizeof(char));

  snprintf(string, MAX_STRING_SIZE, format, value);

  return string;
}

char *intToString(int value) {
  char *string = (char *) malloc(MAX_STRING_SIZE * sizeof(char));

  snprintf(string, MAX_STRING_SIZE, "%d", value);

  return string;
}

void writeTableRowToConsole(int columns, ...) {
  va_list args;
  va_start(args, columns);

  for (int i = 0; i < columns; i++) {
    const char *column_value = va_arg(args, const char *);

    printf("%-20s", column_value);
  }

  printf("\n");

  va_end(args);
}

void writeTableRowToFile(FILE *file, int columns, ...) {
  va_list args;
  va_start(args, columns);

  for (int i = 0; i < columns; i++) {
    const char *column_value = va_arg(args, const char *);

    fprintf(file, "%-20s", column_value);

    if (i < columns - 1) {
      fprintf(file, ",");
    }
  }

  fprintf(file, "\n");

  va_end(args);
}

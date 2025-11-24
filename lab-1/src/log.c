#include <stdio.h>
#include <stdarg.h>

void log_columns(FILE *f, int columns, ...) {
    va_list args;
    va_start(args, columns);

    for (int i = 0; i < columns; ++i) {
        const char *header = va_arg(args, const char*);
        fprintf(f, "%s", header);
        if (i < columns - 1) {
            fprintf(f, ",");
        }
    }
    
    fprintf(f, "\n");
    va_end(args);
}

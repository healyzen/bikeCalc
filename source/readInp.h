#include <stddef.h>
#include <stdio.h>

void lower(char* s);
char** readRow(const char* input, size_t* items);
char* readUntil(FILE* virta, char erotin, size_t* pituus);
void freeCommands(char** commands, size_t count);

#include <stddef.h>
#include <stdio.h>

void lower(char* s);
/*
void readInput(char* input, char** commands, size_t *count);
*/
char** readRow(const char* input, size_t* items);
char* readUntil(FILE* virta, char erotin, size_t* pituus);
void freeCommands(char** commands, size_t count);

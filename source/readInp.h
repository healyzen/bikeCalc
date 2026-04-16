#include <stddef.h>
#include <stdio.h>

/*CONST*/
enum COM 
{
	ADD,
	REVERSE,
	RESET,
	MONTH_RESET,
	MONTH_SET,
	TOTAL_SET,
	DATE_SET,
	EXIT,
	SAVE,
	HELP
};

enum 
{
	COMMAND_COUNT = 10
};

extern const char *COMMAND_LIST[COMMAND_COUNT];

/*FUNCTIONS*/

void lower(char* s);
void readInput(char* input, char** *commands, size_t *count, int* cmd);
char** readRow(const char* input, size_t* items);
char* readUntil(FILE* virta, char erotin, size_t* pituus);
void freeCommands(char** commands, size_t count);

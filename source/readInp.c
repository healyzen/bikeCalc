#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readInp.h"

const char* COMMAND_LIST[COMMAND_COUNT] = 
{
	"a",
	"r\n",
	"reset\n",
	"mr\n",
	"ms",
	"ts",
	"ds",
	"e\n",
	"s\n",
	"help\n"
};

void lower(char* s)
{
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		s[i] = tolower(s[i]);
	}
}

void readInput(char* input, char** *commands, size_t *count, int* cmd)
{
	int i;
	*cmd = -1;
	*count = 0;
	fgets(input,50+1,stdin);
	lower(input);
	*commands = readRow(input, count);
	
	for (i = 0; i < COMMAND_COUNT; i++)
	{
		if (strcmp((*commands)[0], COMMAND_LIST[i]) == 0)
		{
			*cmd = i;
			break;
		}
	}
}

char** readRow(const char* input, size_t* items)
{
	char* word;
	size_t cap = 1;
	size_t count = 0;
	char** commands = malloc(sizeof(char*)*cap);

	for (word = strtok((char*)input," "); word != NULL; word = strtok(NULL," "))
	{
		if (count == cap)
		{
			cap *= 2;
			commands = realloc(commands,sizeof(char*)*cap);
		}
		commands[count] = malloc(sizeof(char)*(strlen(word)+1));
		strcpy(commands[count],word);
		count++;
	}	
	*items = count;
	commands = realloc(commands, sizeof(char*)*count);
	return commands;
}

char* readUntil(FILE* stream, char sep, size_t* lenght)
{
	char c;
	char* buffer;
	size_t cap = 1;
	size_t len = 0;
	buffer = malloc(sizeof(char)*cap);

	while( (c = fgetc(stream)) != sep && c != EOF)
	{
		if (len == cap)
		{
			cap *= 2;
			buffer = realloc(buffer, sizeof(char)*cap);
		}
		buffer[len++] = c;
	}
	
	if (len > 0 || c == sep)
		buffer = realloc(buffer, sizeof(char)*len+1);
	else 
		buffer = realloc(buffer, 0);
	
	*lenght = len;
	return buffer;
}

void freeCommands(char** commands, size_t count)
{
	size_t i;
	for (i = 0; i < count; i++)
	{
		free(commands[i]);
	}
	free(commands);
}

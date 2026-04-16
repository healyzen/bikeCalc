#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include "readInp.h"
#include "calc.h"

/*
	BIKECALC
	Jesse Naumanen, jesse.naumanen@tuni.fi

	This program is meant to help calculate cycling distances
	
	VERSION 1.2 CHANGELOG:
		- cleaned up code
	
	VERSION 1.1 CHANGELOG:
		- added help function
		- fixed up printing format
		- added last day-distance to saved file
		
	TODO 
		- English version
		- ext. signal handling (SIGINT)
	WIP
		- Automated reading from csv

*/

double VERSION = 1.1;

int main(void)
{
	int saved;
	double total;
	double month;
	double day;
	size_t count;
	char** commands = {0};
	char input[50] = "";
	char fName[50] = "";
	
	if ((_setmode(_fileno(stdout), _O_U16TEXT)) == -1)
	{
		wprintf(L"FAILED TO SET MODE\n");
	}
	wprintf(L"bikeCalc v%1.1f\n", VERSION);
	
	readStartData(fName, &total, &month, &day);
	
	wprintf(L"\nCURRENT STATUS:\n");
	wprintf(L"距離　%5.2f\n今月　%5.2f\n合計　%5.2f\n\n", day, month, total);
	saved = 1;
	while(1)
	{
		wprintf(L"(%d): ",saved);
		readInput(input, commands, &count);
		wprintf(L"\n");
		
		if (strcmp(commands[0],"a") == 0)
		{
			if (count == 1)
				continue;
			saved = 0;
			add(commands, count, &total, &month, &day);
			
		} else if (strcmp(commands[0],"r") == 0 ||
					strcmp(input,"r\n") == 0)
		{
			saved = 0;
			reverse(&total, &month, &day);
			
		} else if (strcmp(input,"reset\n") == 0)
		{
			saved = 0;
			reset(&total,&month,&day);
			
		} else if (strcmp(commands[0],"mr") == 0 || 
					strcmp(input,"mr\n") == 0)
		{
			saved = 0;
			wprintf(L"MONTH RESET:\n");
			month = 0;
			
		} else if (strcmp(commands[0],"ms") == 0)
		{
			if (count == 1)
				continue;
			saved = 0;
			wprintf(L"SET MONTH:\n");
			month = atof(commands[1]);
			
		} else if (strcmp(commands[0],"ts") == 0)
		{
			if (count == 1)
				continue;
			saved = 0;
			wprintf(L"SET TOTAL:\n");
			total = atof(commands[1]);
			
		} else if (strcmp(commands[0],"e") == 0 || 
					strcmp(input,"e\n") == 0)
		{
			if (saved)
			{
				freeCommands(commands, count);
				goto exit;
			} else 
			{
				wprintf(L"!UNSAVED PROGRESS!\n");
				wprintf(L"ARE YOU SURE (y/n): ");
				fgets(input,50+1,stdin);
				if (strcmp(input,"y\n") == 0)
				{
					freeCommands(commands, count);
					goto exit;
				} wprintf(L"RETURNING...\n");
			}
			
		} else if (strcmp(commands[0],"s") == 0 || 
					strcmp(input,"s\n") == 0)
		{
			saved = save(fName, total, month,day);
		} else if (strcmp(commands[0],"help") == 0 || 
					strcmp(input,"help\n") == 0)
		{
			help();
			continue;
		} else
		{
			freeCommands(commands, count);
			continue;
		}
	
		wprintf(L"今月　%5.2f キロ\n", month);
		wprintf(L"合計　%5.2f キロ\n\n",total);
		freeCommands(commands, count);
	}
	
	exit:
	wprintf(L"EXITING...\n");
	
	return 0;
}
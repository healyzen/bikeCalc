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
		- changed to switch case
	
	VERSION 1.1 CHANGELOG:
		- added help function
		- fixed up printing format
		- added last day-distance to saved file
		
	TODO 
		- English version (language switching
		- ext. signal handling (SIGINT)
	WIP
		- Automated reading from csv

*/

double VERSION = 1.2;

int main(void)
{
	int saved;
	double total;
	double month;
	double day;
	size_t count;
	int cmd = 0;
	char** commands = {0};
	char date[11] = "";
	char input[50] = "";
	char fName[50] = "";
	wchar_t printDate[11] = L"0000-00-00\0";
	
	if ((_setmode(_fileno(stdout), _O_U16TEXT)) == -1)
	{
		wprintf(L"FAILED TO SET MODE\n");
	}
	wprintf(L"bikeCalc v%1.1f\n", VERSION);
	
	readStartData(fName, &total, &month, &day, date);
	
	mbstowcs(printDate, (const char*)date, 11);
	printDate[10] = L'\0';
	
	wprintf(L"LAST SAVED: %ls\n", printDate);
	
	
	wprintf(L"\nCURRENT STATUS:\n");
	wprintf(L"距離　%5.2f\n今月　%5.2f\n合計　%5.2f\n\n", day, month, total);
	saved = 1;
	while(1)
	{
		wprintf(L"(%d): ",saved);
		
		readInput(input, &commands, &count, &cmd);
		
		wprintf(L"\n");
		
		switch (cmd)
		{
			case ADD:
				if (count == 1)
					goto fault;
				saved = 0;
				add(commands, count, &total, &month, &day);
				break;
				
			case REVERSE:
				saved = 0;
				reverse(&total, &month, &day);
				break;
				
			case RESET:
				saved = 0;
				reset(&total,&month,&day);
				break;
				
			case MONTH_RESET:
				saved = 0;
				wprintf(L"MONTH RESET:\n");
				month = 0;
				break;
				
			case MONTH_SET:
				if (count == 1)
					goto fault;
				saved = 0;
				wprintf(L"SET MONTH:\n");
				month = atof(commands[1]);
				break;
				
			case TOTAL_SET:
				if (count == 1)
					goto fault;
				saved = 0;
				wprintf(L"SET TOTAL:\n");
				total = atof(commands[1]);
				break;
				
			case DATE_SET:
				if (count == 1)
					goto fault;
				saved = 0;
				wprintf(L"SET DATE:\n");
				strncpy(date, commands[1],10);
				date[10] = '\0';
				mbstowcs(printDate,date,11);
				wprintf(L"DATE SET TO: %ls\n\n",printDate);
				goto fault;
				break;
				
			case EXIT:
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
				break;
				
			case SAVE:
				saved = save(fName,total,month,day,date);
				break;
				
			case HELP:
				help();
				break;
				
			default:
				goto fault;	
		}
		
		wprintf(L"今月　%5.2f キロ\n", month);
		wprintf(L"合計　%5.2f キロ\n\n",total);
		fault:
		freeCommands(commands, count);
	}
	
	exit:
	wprintf(L"EXITING...\n");
	
	return 0;
}
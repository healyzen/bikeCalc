#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <locale.h>
#include "calc.h"
#include "readInp.h"

void readStartData(char* fName, double* total, double* month, double* day)
{
	size_t len;
	FILE * file;
	
	wprintf(L"GIVE FILENAME: ");
	fgets(fName, 50, stdin);
	fName[strlen(fName)-1] = '\0';
	file = fopen(fName, "r");
	
	if (file == NULL)
	{
		wprintf(L"!FILE OPENING FAILED!\nCREATING NEW FILE...\n");
		*total = 0;
		*month = 0;
		*day = 0;
		fclose(file);
		return;
	}
	wprintf(L"FILE OPENED SUCCESSFULLY\n");
	*total = atof(readUntil(file, '\n', &len));
	*month = atof(readUntil(file, '\n', &len));
	*day = atof(readUntil(file, '\n', &len));
	fclose(file);
}

/*void readFromFile()*/

void add(char** list, size_t count, double* total, double* month, double* day)
{
	int i;
	wprintf(L"ADD:\n距離　");
	*day = 0;
	*day += atof(list[1]);
	
	if (count == 2)
	{
		wprintf(L"+%3.2f", *day);
	} else if (count > 2)
	{
		wprintf(L"%3.2f", *day);
		for (i = 2; i < count; i++)
		{
			*day += atof(list[i]);
			wprintf(L" + %3.2f",atof(list[i]));
		}
	}
	wprintf(L" = %3.2f キロ\n", *day);
	*month += *day;
	*total += *day;
}

void reverse(double* total, double* month, double* day)
{
	wprintf(L"REVERSE:\n");
	*day = -(*day);
	*month += *day;
	*total += *day;
	wprintf(L"%3.2f\n", day);
}

void reset(double* total, double* month, double* day)
{
	wprintf(L"FULL RESET:\n");
	*total = 0;
	*month = 0;
	*day = 0;
	wprintf(L"距離　%5.2f キロ\n", day);
}

void help(void)
{
	wprintf(L"LIST OF COMMANDS:\n");
	wprintf(L"NAME		COMMAND	DESCRIPTION:\n");
	wprintf(L"\nADDING: \n");
	wprintf(L"ADD:		a n	(adds numbers after command, SUB using negatives)\n");
	wprintf(L"REVERSE:	r	(reverses previous add)\n");
	wprintf(L"\nSET COMMANDS: \n");
	wprintf(L"RESET:		reset	(fully reset everything to zero)\n");
	wprintf(L"MONTH RESET:	mr	(resets month to 0)\n");
	wprintf(L"SET TOTAL:	ts n	(sets total to first number after command)\n");
	wprintf(L"SET MONTH:	ms n	(sets month to first number after command)\n");
	wprintf(L"\nSAVING AND EXITING: \n");
	wprintf(L"SAVE:		s	(saves current status to file)\n");
	wprintf(L"EXIT:		e	(exits program)\n\n");
}

int save(char* fName, double total, double month, double day)
{
	FILE *file = fopen(fName, "w");
	
	wprintf(L"SAVING:\n");
	wprintf(L"距離　%5.2f キロ\n", day);
	if (file != NULL)
	{
		fprintf(file,"%f\n%f\n%f",total,month,day);
		fclose(file);
		return 1;
			
	}else
		fclose(file);
	return 0;
}
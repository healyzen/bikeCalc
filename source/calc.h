



/*READING*/
void readStartData(char* fName, double* total, double* month, double* day, 
					char date[11]);

/*EDITING*/					
void add(char** list, size_t count, double* total, double* month, double* day);
void reverse(double* total, double* month, double* day);
void reset(double* total, double* month, double* day);
void help(void);

/*SAVING*/
int save(char* fName, double total, double month, double day, char* date);

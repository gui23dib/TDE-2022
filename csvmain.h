#ifndef CSVMAIN_H_INCLUDED
#define CSVMAIN_H_INCLUDED

#define FILE_LINES 535535

#include <stdio.h>

char** openfile(FILE *csvfile);
void destroy(char** linhas);

#endif // CSVMAIN_H_INCLUDED

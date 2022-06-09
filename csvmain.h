#ifndef CSVMAIN_H_INCLUDED
#define CSVMAIN_H_INCLUDED

#include <stdio.h>

void menu(FILE *csvfile);
int openfile(FILE *csvfile);
int case1(FILE *csvfile);
int case2(FILE *csvfile);
void resetfunction(FILE *csvfile);

#endif // CSVMAIN_H_INCLUDED

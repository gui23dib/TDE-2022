#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h" /*biblioteca customizada*/
#include "csvmain.h"

#define SUCCES 0
#define ERROR 1

int main()
{
    FILE *csvfile;

    openfile(csvfile);

    menu();

    return 0;
}

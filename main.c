/**bibliotecas padroes**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/**bibliotecas de usuario**/
#include "csvmain.h" /*conteudos do menu e manipulacao de dados do CSV*/



int main(void)
{
    setlocale(LC_ALL, "UTF-8");

    FILE *csvfile;

    /*ORIGINAL MAIN*/

    openfile(csvfile);

    /*menu(csvfile);*/

    return EXIT_SUCCESS;
}

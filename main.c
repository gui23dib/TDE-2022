#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h" /*biblioteca customizada com os conteudos do menu*/
#include "csvmain.h" /*biblioteca customizada com os conteudos da manipulacao de dados do CSV*/

#define FILENAME "dados_covid_sp.csv"

int main(void)
{
    FILE *csvfile;

    openfile(csvfile);
    case1(csvfile);

    /*menu(csvfile);*/

    return EXIT_SUCCESS;
}

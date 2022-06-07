#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "csvmain.h"

#define SUCCES 0
#define ERROR 1

void menu(FILE *csvfile){
    int menuchoice;

    printf("******************************************************\n");
    printf("* Pesquisa sobre dados de casos e obitos de COVID-19 *\n");
    printf("******************************************************\n");
    printf("1 - Pesquisa casos por cidade (codigo do IBGE)\n");
    printf("2 - Pesquisa obitos por cidade (codigo do IBGE)\n");
    printf("3 - Sair\n");
    printf("Digite uma opcao: ");

    scanf("%i", &menuchoice);

    switch(menuchoice){
        case 1:
            case1(csvfile);
        break;
        case 2:
            printf("caso 2");
        break;
        case 3:
        break;
        default:
            printf("Opcao invalida!\n");
            getch();
            system("cls");
            menu(csvfile);
        break;
    }
}

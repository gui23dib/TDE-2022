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
    printf("1 - Pesquisa de media de casos novos por ano e cidade (codigo do IBGE)\n");
    printf("2 - Pesquisa de media de obitos novos por ano e cidade (codigo do IBGE)\n");
    printf("3 - Sair\n");
    printf("Digite uma opcao: ");

    scanf("%i", &menuchoice);

    switch(menuchoice){
        case 1:
            system("cls");
            case1(csvfile);
        break;
        case 2:
            system("cls");
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

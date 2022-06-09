/**bibliotecas**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "csvmain.h" /*link ao arquivo header*/

void menu(FILE *csvfile){
    int menuchoice;

    printf("******************************************************\n");
    printf("* Pesquisa sobre dados de casos e obitos de COVID-19 *\n");
    printf("******************************************************\n");
    printf("1 - Pesquisa de media de casos novos por ano e cidade (codigo do IBGE)\n");
    printf("2 - Pesquisa de media de obitos novos por ano e cidade (codigo do IBGE)\n");
    printf("2 - Pesquisa de mediana de casos novos por ano e cidade (codigo do IBGE)\n");
    printf("2 - Pesquisa de mediana de obitos novos por ano e cidade (codigo do IBGE)\n");
    printf("5 - Sair\n");
    printf("Digite uma opcao: ");

    scanf("%i", &menuchoice);

    switch(menuchoice){
        case 1:
            system("cls");
            case1(csvfile);
        break;
        case 2:
            system("cls");
            case2(csvfile);
        break;
        case 3:
            system("cls");
            case3(csvfile);
        break;
        case 4:
            system("cls");
            /*case1(csvfile);*/
        break;
        case 5:
            exit(EXIT_SUCCESS);
        break;
        default:
            printf("Opcao invalida!\n");
            getch(); /* Usado para pausar a execucao */
            system("cls");
            menu(csvfile); /* Entra em loop de execucao */
        break;
    }
}

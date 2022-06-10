/**bibliotecas**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "csvmain.h" /*link ao arquivo header*/

void menu(FILE *csvfile){
    int menuchoice;
    setlocale(LC_ALL, "");

    printf("******************************************************\n");
    printf("* Pesquisa sobre dados de casos e �bitos de COVID-19 *\n");
    printf("******************************************************\n");
    printf("1 - Pesquisa de m�dia de casos novos por ano e cidade (c�digo do IBGE)\n");
    printf("2 - Pesquisa de m�dia de �bitos novos por ano e cidade (c�digo do IBGE)\n");
    printf("3 - Pesquisa de mediana de casos novos por ano e cidade (c�digo do IBGE)\n");
    printf("4 - Pesquisa de mediana de �bitos novos por ano e cidade (c�digo do IBGE)\n");
    printf("5 - Sair\n");
    printf("Digite uma op��o: ");

    scanf("%i", &menuchoice);

    do{
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
                case4(csvfile);
            break;
            case 5:
                exit(EXIT_SUCCESS);
            break;
            default:
                printf("Op��o inv�lida!\n");
                getch(); /* Usado para pausar a execucao */
                system("cls");
                menu(csvfile); /* Entra em loop de execucao */
            break;
        }
    }while(menuchoice != 5);
}

#include <stdio.h>
#include <stdlib.h>
#include "csvmain.h"

#define SUCCES 0
#define ERROR 1

#define FILE_NAME "dados_covid_sp.csv"
#define LINE_LENGTH 401
#define MAX_COLUMNS 26
#define SEP ";"
#define MAX_LINES 6000

int openfile(FILE *csvfile){

    csvfile = fopen(FILE_NAME, "r"); /* modo "r" de abertura permite um arquivo de texto para leitura */

    if(csvfile == NULL) {
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
        return ERROR;

    } /*else {
        printf("O arquivo foi executado com sucesso!!!\n");
        getch();
        system("cls");
        return SUCCES;

    }*/

    char linha[LINE_LENGTH], *cabecalho[MAX_COLUMNS], primeira_linha[LINE_LENGTH], * valor;
    int n_colunas = 0, i, n_linhas = 0, valores_contados = 0;

    /**LE {RIMEIRA LINHA**/
    fscanf(csvfile,"%s\n",linha);

    /**Separa o cabecalho**/
    cabecalho[n_colunas] = strtok(linha, SEP);
    while(cabecalho[n_colunas++] != NULL){
        cabecalho[n_colunas] = strtok(NULL, SEP);
    }

    /**Mostra os valores do cabecalho**/
    for (i = 0; i < n_colunas; i++){
        printf("%s\n",cabecalho[i]);
    }

    getch();
    return SUCCES;
}

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "csvmain.h"

#define SUCCES 0
#define ERROR 1

#define FILE_NAME "dados_covid_sp.csv"
#define LINE_LENGTH 1024
#define MAX_COLUMNS 28
#define SEP ";"
#define MAX_LINES 527200

int openfile(FILE *csvfile){

    csvfile = fopen(FILE_NAME, "r"); /* modo "r" de abertura permite um arquivo de texto para leitura */

    if(csvfile == NULL) {
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
        return ERROR;
    }

    printf("Arquvio aberto com sucesso!!!\n");

    /* Ler todas as linhas do CSV */
    size_t tamanho = 0;
    char* linha;
    getline(&linha, &tamanho, csvfile);
    printf("%zu\n", tamanho);
    printf("%s\n", linha);











    /*
    header[columns] = strtok(line, SEP);
    while(header[columns++] != NULL){
        header[columns] = strtok(NULL, SEP);
    }

    for (i = 0; i < columns; i++){
        if(i != columns-1){
            printf("%s\n", header[i]);
        }
    }

    float media = 0;

    /*while(fscanf(csvfile, "%900[^\n]", line)){

        if(linenum == 0){
            strcpy(firstline, line);
        }

        Primeira Coluna
        val = strtok(line, SEP);

        Mostra a primeira linha
        printf("\nPrimeira coluna: %s\n", val);

        /*Segunda Coluna
        val = strtok(NULL, SEP);

        printf("\nSegunda coluna: %s\n", val);


        for(i = 0 ; i < 4 ; i++){  PULA DA TERCEIRA ATE A SETIMA COLUNA (CASOS NOVOS)
            val = strtok(NULL, SEP);
        }

        printf("\nSetima coluna: %s\n", val);

        linenum++;
    } */

    /*Mostra a primeira linha
    printf("\nPrimeira Linha: %s\n", firstline);

    /*Mostra o numero de linhas
    printf("\nNumero de linhas %d\n\n\n", linenum);*/

    getch();
    return SUCCES;
}

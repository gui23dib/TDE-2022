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

// Le o conteudo do csv. Eh necessario chamar o free(linhas) no final do programa
// @returns matriz com as linhas
char** openfile(FILE *csvfile){
    char** matriz = malloc(FILE_LINES * sizeof(char*));

    /*setlocale(LC_ALL, "UTF-8");*/
    csvfile = fopen(FILE_NAME, "r"); /* modo "r" de abertura permite um arquivo de texto para leitura */

    if(csvfile == NULL) {
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
        exit(1);

    } /*else {
        printf("O arquivo foi executado com sucesso!!!\n");
        getch();
        system("cls");
        return SUCCES;

    }*/

    size_t tamanho = 0;
    char* linha_heap;
    char* linha;

    /* 
     * Ler todas as linhas do CSV 
     * Armazena todas as linhas dentro de uma matriz
     */
    getline(&linha, &tamanho, csvfile);
    linha_heap = malloc(tamanho * sizeof(char));

    int i;
    for(i = 0; i < FILE_LINES; ++i){
      strcpy(linha_heap, linha);
      matriz[i] = linha_heap;

      getline(&linha, &tamanho, csvfile);
      linha_heap = malloc(tamanho * sizeof(char));
    }

    return matriz;
}

void destroy(char** linhas) {
  free(linhas);
}

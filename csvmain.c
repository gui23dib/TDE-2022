#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "csvmain.h"

#define FILE_NAME "dados_covid_sp.csv"
#define LINE_LENGTH 1024
#define MAX_COLUMNS 28
#define SEP ";"
#define MAX_LINES 527200

int openfile(FILE *csvfile){

    csvfile = fopen(FILE_NAME, "r"); /* modo "r" de abertura permite um arquivo de texto para leitura */

    if(csvfile == NULL) {
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
        system("pause");
        exit(EXIT_FAILURE);
    } else {
        printf("Arquvio aberto com sucesso!!!\n");
        system("pause");
        system("cls");
        return EXIT_SUCCESS;
    }
}

int case1(FILE *csvfile){

    openfile(csvfile);

    char *val, *line_buf = NULL;
    size_t line_buf_size = 0;
    int i , line_count = 0;
    size_t line_size;
    int contador = 0;
    float junta;

    char type[30], year[10];

    printf("digite o codigo de cidade: "); /** FAZER VERIFICACOES DE ERRO PARA CODIGO INEXISTENTES **/
    scanf("%s", &type);


    printf("digite o ano: ");
    scanf("%s", &year);
    strcat(year, "-");

  /* Extrai o cabecalho (primeira linha) */
  line_size = getline(&line_buf, &line_buf_size, csvfile);

  /* Loop ate o fim do aruivo (EOF) */
  while (line_size >= 0)
  {
    line_count++; /** CONTA A LINHA DO PRINT (((RETIRAR NA VEERSAO FINAL))) **/

    /* Estrutura de decisao para filtragem dos dados */
    if(strstr(line_buf, type) && strstr(line_buf, year)){
        printf("[%06d] %s", line_count, line_buf);

        val = strtok(line_buf, SEP);
        printf("\nPrimeira coluna: %s\n", val);

        val = strtok(NULL, SEP);
        printf("\nSegunda coluna: %s\n", val);

        for(i = 0 ; i < 4 ; i++){  /*PULA DA TERCEIRA ATE A SETIMA COLUNA (CASOS NOVOS)*/
            val = strtok(NULL, SEP);
            junta = atof(val);
            contador++;
        }

        printf("\nSetima coluna: %s\n", val);
    }

    /* Passagem para proxima linha */
    line_size = getline(&line_buf, &line_buf_size, csvfile);
  }

  /* Desalocamento do ponteiro line_buf */
  free(line_buf);
  line_buf = NULL;

  /* Fim do uso do arquivo */
  fclose(csvfile);


    return EXIT_SUCCESS;
}

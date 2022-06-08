#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "csvmain.h"

#define FILENAME "dados_covid_sp.csv"
#define LINE_LENGTH 1024
#define MAX_COLUMNS 28
#define SEP ";"
#define MAX_LINES 527200

int openfile(FILE *csvfile){

    csvfile = fopen(FILENAME, "r"); /* modo "r" de abertura permite um arquivo de texto para leitura */

    if(csvfile == NULL) {
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");

        system("pause");

        exit(EXIT_FAILURE);
    } else {
        printf("Arquivo aberto com sucesso!!!\n");

        system("pause");
        system("cls");

        menu(csvfile);

        return EXIT_SUCCESS;
    }
}

int case1(FILE *csvfile){

    char *val = NULL, *line_buf = NULL;
    int i, contador = 0, veri = 0, line_count = 0;
    size_t line_size, line_buf_size = 0;
    float junta = 0;

    char type[10], year[10];

     printf("Digite o ano: ");
    scanf("%s", &year);
    if(atof(year) < 2020 || atof(year) > 2022){
        printf("Ano invalido, nao existem dados correspondentes a %s\n", year);
        return EXIT_FAILURE;
    }
    strcat(year, "-");

    FILE *verfile = fopen("codigoibgever.txt", "r"); /*abre arquivo de verificacao para codigos validos do IBGE*/
    if(verfile == NULL){
        printf("Erro! O arquivo de verificacao (codigoibgever.txt) nao foi encontrado...\n");
        system("pause");
        return EXIT_FAILURE;
    }

    printf("Digite o codigo de cidade: ");
    scanf("%s", &type);

    while (line_size >= 0){
        if(getline(&line_buf, &line_buf_size, verfile) > 0){ /*leitura do arquivo*/
            if(strstr(line_buf, type) != NULL){ /*comparacao com o arquivo de verificacao, se sim, armazena o valor 1 na variavek veri como VERDADEIRO*/
                veri ++;
                printf("VERIFICACO +1 CODIGO: %s\n\n", line_buf);
            }
        } else {
            break;
        }
    }

    if(veri == 0){ /*faz a verificacao 1 ou 0 para codigos invalidos*/
        printf("Codigo invalido, visite https://www.ibge.gov.br/explica/codigos-dos-municipios.php#SP para verificar os codigos validos dos municipios de Sao Paulo\n");
        return EXIT_FAILURE;
    }
    strcat(type, SEP); /*concatena o separador a string type para verificacao no dataset*/



  /* Extrai o cabecalho (primeira linha) */
  line_size = getline(&line_buf, &line_buf_size, csvfile);

  /* Loop ate o fim do aruivo (EOF) */
  while (line_size >= 0){

    line_count++; /** CONTA A LINHA DO PRINT (((RETIRAR NA VERSAO FINAL))) **/

    if(strstr(line_buf, type) && strstr(line_buf, year)){
       /**printf("[%06d] %s\n", line_count, line_buf);**/ /**PRINT PARA TESTE**/

        val = strtok(line_buf, SEP);
        /*printf("\nPrimeira coluna: %s\n", val);*/

        for(i = 0 ; i < 5 ; i++){
            val = strtok(NULL, SEP);
        }

        junta += atof(val);
        contador++;
    }

    if(getline(&line_buf, &line_buf_size, csvfile) < 0){
        break;
    }
  }

system("pause");
system("cls");

  printf("\nMEDIAZADA %s: %.2f\n\n", type, (junta / contador));

  /* Desalocamento do ponteiro line_buf */
  free(line_buf);
  line_buf = NULL;

  /* Fim do uso do arquivo */
  fclose(csvfile);



    return EXIT_SUCCESS;
}

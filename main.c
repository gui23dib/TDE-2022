#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h" /*biblioteca customizada com os conteudos do menu*/
#include "csvmain.h" /*biblioteca customizada com os conteudos da manipulacao de dados do CSV*/

#define FILENAME "dados_covid_sp.csv"

int main(void)
{
    FILE *csvfile;

    csvfile = fopen(FILENAME, "r"); /* modo "r" de abertura permite um arquivo de texto para leitura */

    if(csvfile == NULL) {
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    printf("Arquivo aberto com sucesso!!!\n");

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

    if(strstr(line_buf, type) && strstr(line_buf, year)){
       printf("[%06d] %s\n", line_count, line_buf);
    }

    line_size = getline(&line_buf, &line_buf_size, csvfile);
  }

  /* Desalocamento do ponteiro line_buf */
  free(line_buf);
  line_buf = NULL;

  /* Fim do uso do arquivo */
  fclose(csvfile);


    /*openfile(csvfile);

    case1(csvfile);

    /*menu(csvfile);*/

    return EXIT_SUCCESS;
}

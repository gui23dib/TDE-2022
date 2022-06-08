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
    int i, j = 0, k, n, line_count = 0;
    size_t line_size, line_buf_size = 0;

    char year[10];

     printf("Digite o ano: ");
    scanf("%s", &year);
    if(atof(year) < 2020 || atof(year) > 2022){
        printf("Ano invalido, nao existem dados correspondentes a %s\n", year);
        return EXIT_FAILURE;
    }
    strcat(year, "-");

    printf("Digite o numero de codigos a serem inseridos: ");
    scanf("%i", &n);

    char type[n][10], aux[10];

    FILE *verfile;

    int veri[n];

    for(i = 0 ; i < n ; i++){

        verfile = fopen("codigoibgever.txt", "r"); /*abre arquivo de verificacao para codigos validos do IBGE*/
        if(verfile == NULL){
            printf("Erro! O arquivo de verificacao (codigoibgever.txt) nao foi encontrado...\n");
            system("pause");
            return EXIT_FAILURE;
        }

        veri[i] = 0;
        printf("Digite o codigo da cidade %i: ", i+1);
        scanf("%s", &type[i]);

        line_size = 1;

        strcpy(aux, type[i]);

        while (line_size >= 0){
            if(getline(&line_buf, &line_buf_size, verfile) > 0){ /*leitura do arquivo*/
                if(strstr(line_buf, aux) != NULL){ /*comparacao com o arquivo de verificacao, se sim, armazena o valor 1 na variavek veri como VERDADEIRO*/
                    veri[i] = 1;
                }
            } else {
                fclose(verfile);
                break;
            }
        }
    }

    for(i = 0 ; i < n ; i++){
        if(veri[i] == 0){ /*faz a verificacao 1 ou 0 para codigos invalidos*/
            printf("\nCodigo (%s) invalido, visite https://www.ibge.gov.br/explica/codigos-dos-municipios.php#SP para verificar os codigos validos dos municipios de Sao Paulo\n", type[i]);
            return EXIT_FAILURE;
        }
        strcat(type[i], SEP); /*concatena o separador a string type para verificacao no dataset*/
    }
    printf("\n");



      /* Extrai o cabecalho (primeira linha) */
      line_size = getline(&line_buf, &line_buf_size, csvfile);

      int contador[n];
      float junta[n];
      float result[n];

      /* Loop ate o fim do arquivo (EOF) */
      for(i = 0 ; i < n ; i++){

        csvfile = fopen(FILENAME, "r");
        printf("Carregando %i. . . \n", i+1);

         /*printf("ENTROU NO LOOP I i = %i\n", i);*/ /**PRINT PARA TESTE**/

        contador[i] = 0;
        junta[i] = 0;
        j = 0;


        aux[0] = '\0';

          strcpy(aux, type[i]);

          /*printf("AUXZADA %s TYPEZADA %s\n", aux, type[i]);*/ /**PRINT PARA TESTE**/

          while (line_size >= 0){

            if(strstr(line_buf, aux) && strstr(line_buf, year)){
               /*printf("%s\n", line_buf);*/ /**PRINT PARA TESTE**/

                val = strtok(line_buf, SEP);

                for(k = 0 ; k < 5 ; k++){
                    val = strtok(NULL, SEP);
                }
                junta[i] += atof(val);
                j++;
            }

            contador[i] = j;
            result[i] = junta[i] / contador[i];

            if(getline(&line_buf, &line_buf_size, csvfile) < 0){
                /*printf(" i: %i junta %.2f cont %i med %f result %f\n", i, junta[i], contador[i], (junta[i]/ contador[i]), result[i]);*/ /**PRINT PARA TESTE**/
                fclose(csvfile);
                break;
            }
          }
      }

    system("pause");
    system("cls");

    year[strlen(year)-1] = '\0';
      printf("Ano: %s\n", year);
    for(i = 0 ; i < n ; i++){
     type[i][strlen(type)-1] = '\0';
      printf("\nMEDIA CIDADE %i (%s): %.2f\n\n", (i+1), type[i], (junta[i] / contador[i]));
    }

  /* Desalocamento do ponteiro line_buf */
  free(line_buf);
  line_buf = NULL;

  /* Fim do uso do arquivo */
  fclose(csvfile);



    return EXIT_SUCCESS;
}

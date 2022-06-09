/**bibliotecas**/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "csvmain.h" /*link ao arquivo header*/

/**pre-definicoes de valores**/
#define FILENAME "dados_covid_sp.csv"
#define SEP ";"

int openfile(FILE *csvfile){

    csvfile = fopen(FILENAME, "r"); /* Abre o arquivo do dataset para leitura (apenas) */

    if(csvfile == NULL) { /* Verifica o retorno da abertura */

        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");

        system("pause");
        exit(EXIT_FAILURE); /* Desliga a aplicacao */

    } else {

        system("cls");
        menu(csvfile); /* Abre o menu caso o arquivo seja aberto propriamente */

        return EXIT_SUCCESS;
    }
}

int case1(FILE *csvfile){

    char *val = NULL, *line_buf = NULL;
    int i, j = 0, k, n;
    size_t line_size, line_buf_size = 0;


    char year[10]; /* String do ano para filtragem dos dados */
        printf("Digite o ano: ");
        scanf("%s", &year);

        if(atof(year) < 2020 || atof(year) > 2022){ /* Verificacao direta (ja que o dataset so consta dados de 2020 ate 2022) */
            printf("Ano invalido, nao existem dados correspondentes a %s, tente novamente\n", year);
            system("pause");
            return EXIT_FAILURE;
        }
    strcat(year, "-"); /* Adiciona a formatacao para que haja concordancia com a formatacao das datas do arquivo */

    printf("Digite o numero de codigos a serem inseridos: ");
    scanf("%i", &n); /* Determina sempre o numero de casos sendo usados assim servindo como parametro dos loops FOR */
    char type[n][10], aux[10], citycodename[n][40];


    FILE *verfile;
    int veri[n]; /* Variavel para verificacao (BOOLEANA) de cada codigo individualmente */
    for(i = 0 ; i < n ; i++){

        verfile = fopen("codigoibgever.txt", "r"); /* Abre arquivo de verificacao para codigos validos do IBGE */
        if(verfile == NULL){ /* Codigo de erro para falha no arquivo */
            printf("Erro! O arquivo de verificacao (codigoibgever.txt) nao foi encontrado...\n");
            system("pause");
            return EXIT_FAILURE;
        }

        veri[i] = 0; /* Esvazia a variavel atual veri[i] */
        printf("Digite o codigo da cidade %i: ", i+1);
        scanf("%s", &type[i]);

        line_size = 1;

        strcpy(aux, type[i]); /* Auxiliar usado para comparacao dos conteudos da type[i] na getline() */

        while (line_size >= 0){
            if(getline(&line_buf, &line_buf_size, verfile) > 0){ /* Leitura (linha por linha) do arquivo */
                if(strstr(line_buf, aux) != NULL && strlen(aux) == 7){ /* Comparacao com o arquivo de verificacao, se sim, armazena o valor 1 na variavel veri[i] como "VERDADEIRO" */
                    val = strtok(line_buf, "3");
                    strcpy(citycodename[i], val);

                    veri[i] = 1;
                }
            } else {
                fclose(verfile); /* Reseta a abertura do arquivo para que haja a releitura no proximo caso i */
                break;
            }
        }
    }

    for(i = 0 ; i < n ; i++){
        if(veri[i] == 0){ /* Faz a verificacao 1 ou 0 para codigos invalidos */
            printf("\nCodigo (%s) invalido, visite https://www.ibge.gov.br/explica/codigos-dos-municipios.php#SP para verificar os codigos validos dos municipios de Sao Paulo\n", type[i]);
            system("pause");
            return EXIT_FAILURE;
        }
        strcat(type[i], SEP); /* Concatena o separador a string type para verificacao no dataset (de acordo com a formatacao) */
    }
    printf("\n");


    /* Extrai o cabecalho (primeira linha) */
    line_size = getline(&line_buf, &line_buf_size, csvfile);

    int contador[n];
    float junta[n];
    float result[n];

    /* Loop ate o fim dos casos */
    for(i = 0 ; i < n ; i++){

        csvfile = fopen(FILENAME, "r"); /* Reset do arquivo para leitura individual do caso i */
        printf("Carregando %i. . . \n", i+1);

        /* Zera os valores das variaveis inteiras e string (aux) */
        contador[i] = 0;
        junta[i] = 0;
        j = 0;
        aux[0] = '\0';

        strcpy(aux, type[i]);

        while (line_size >= 0){ /* Loop ate o fim do arquivo (EOF) */

            if(strstr(line_buf, aux) && strstr(line_buf, year)){ /* Filtra apenas as linhas que contem o codigo e ano escolhidos */
                val = strtok(line_buf, SEP); /* Extrai primeira coluna */

                for(k = 0 ; k < 5 ; k++){
                    val = strtok(NULL, SEP); /* Pula ate a coluna desejada */
                }

                junta[i] += atof(val); /* Acumula o valor da coluna */
                j++; /* Contador de linhas que passaram na filtragem */

            }

            contador[i] = j;
            result[i] = junta[i] / contador[i]; /* Resultado da media */

            if(getline(&line_buf, &line_buf_size, csvfile) < 0){ /* Verificacao do retorno da getline (para identificar EOF) */
                fclose(csvfile); /* Fim do uso do arquivo para loop atual (reset) */
                break;
            }
        }
    }
    printf("Concluido!!! \n");

    system("pause");
    system("cls");

    year[strlen(year)-1] = '\0'; /* Retira a concatenacao anterior de "-" para impressao */
    printf("Media de casos novos por cidade e ano\n");
    printf("Ano: %s\n\n", year);

    for(i = 0 ; i < n ; i++){
        type[i][strlen(type[i])-1] = '\0'; /* Tira a formatacao do separador da type[i] */
        printf("%s", citycodename[i]);
        for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
            printf(" ");
        }
        printf("%.2f\n", result[i]);
    }

    printf("\nDeseja salvar esse resultado (S/N)? ");
    char dec = getch(); /* Uso do get character para capturar um unico caractere */
    printf("%c \n", dec); /* Confirmacao do input */

    /* Estrutura de decisao para verificar validacao da entrada "char dec" para Sim, Nao, ou Invalido */
    if(dec == 'S' || dec == 's'){

        /* Captura da string que nomeia o arquivo, e impressao dos dados */
        printf("Digite o nome do arquivo: ");
        char savedfilename[26];
        scanf("%s", &savedfilename);
        strcat(savedfilename, ".csv");

        FILE* newfile  = fopen ("savedfile.csv", "w"); /* Criacao e abertura do arquivo csv para escrever*/

        fprintf(newfile, "Media de casos novos por cidade e ano\n");
        fprintf(newfile, "Ano: %s\n", year);

        for(i = 0 ; i < n ; i++){
            fprintf(newfile, "%s", citycodename[i]);
            for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
                fprintf(newfile, " ");
            }
            fprintf(newfile, "%.2f\n", result[i]);
        }

        fclose(newfile);
        rename("savedfile.csv", savedfilename);
        printf("Resultado salvo no arquivo %s\n", savedfilename);

        resetfunction(csvfile);

    } else if(dec == 'N' || dec == 'n'){

        resetfunction(csvfile);

    } else {
        printf("Opcao invalida, retornando ao menu . . .\n");
        getch(); /* Getch sem atribuicao para pausa curta no programa */
        system("cls");
        menu(csvfile);
    }

    /* Desalocamento do ponteiro line_buf */
    free(line_buf);
    line_buf = NULL;

    return EXIT_SUCCESS;
}

int case2(FILE *csvfile){

    char *val = NULL, *line_buf = NULL;
    int i, j = 0, k, n;
    size_t line_size, line_buf_size = 0;


    char year[10]; /* String do ano para filtragem dos dados */
    printf("Digite o ano: ");
    scanf("%s", &year);

    if(atof(year) < 2020 || atof(year) > 2022){ /* Verificacao direta (ja que o dataset so consta dados de 2020 ate 2022) */
        printf("Ano invalido, nao existem dados correspondentes a %s, tente novamente\n", year);
        system("pause");
        return EXIT_FAILURE;
    }
    strcat(year, "-"); /* Adiciona a formatacao para que haja concordancia com a formatacao das datas do arquivo */


    printf("Digite o numero de codigos a serem inseridos: ");
    scanf("%i", &n); /* Determina sempre o numero de casos sendo usados assim servindo como parametro dos loops FOR */
    char type[n][10], aux[10], citycodename[n][40];


    FILE *verfile;
    int veri[n]; /* Variavel para verificacao (BOOLEANA) de cada codigo individualmente */
    for(i = 0 ; i < n ; i++){

        verfile = fopen("codigoibgever.txt", "r"); /* Abre arquivo de verificacao para codigos validos do IBGE */
        if(verfile == NULL){ /* Codigo de erro para falha no arquivo */
            printf("Erro! O arquivo de verificacao (codigoibgever.txt) nao foi encontrado...\n");
            system("pause");
            return EXIT_FAILURE;
        }

        veri[i] = 0; /* Esvazia a variavel atual veri[i] */
        printf("Digite o codigo da cidade %i: ", i+1);
        scanf("%s", &type[i]);

        line_size = 1;

        strcpy(aux, type[i]); /* Auxiliar usado para comparacao dos conteudos da type[i] na getline() */

        while (line_size >= 0){
            if(getline(&line_buf, &line_buf_size, verfile) > 0){ /* Leitura (linha por linha) do arquivo */
                if(strstr(line_buf, aux) != NULL){ /* Comparacao com o arquivo de verificacao, se sim, armazena o valor 1 na variavel veri[i] como "VERDADEIRO" */
                    val = strtok(line_buf, "3");
                    strcpy(citycodename[i], val);

                    veri[i] = 1;
                }
            } else {
                fclose(verfile); /* Reseta a abertura do arquivo para que haja a releitura no proximo caso i */
                break;
            }
        }
    }

    for(i = 0 ; i < n ; i++){
        if(veri[i] == 0){ /* Faz a verificacao 1 ou 0 para codigos invalidos */
            printf("\nCodigo (%s) invalido, visite https://www.ibge.gov.br/explica/codigos-dos-municipios.php#SP para verificar os codigos validos dos municipios de Sao Paulo\n", type[i]);
            system("pause");
            return EXIT_FAILURE;
        }
        strcat(type[i], SEP); /* Concatena o separador a string type para verificacao no dataset (de acordo com a formatacao) */
    }
    printf("\n");


    /* Extrai o cabecalho (primeira linha) */
    line_size = getline(&line_buf, &line_buf_size, csvfile);

    int contador[n];
    float junta[n];
    float result[n];

    /* Loop ate o fim dos casos */
    for(i = 0 ; i < n ; i++){

        csvfile = fopen(FILENAME, "r"); /* Reset do arquivo para leitura individual do caso i */
        printf("Carregando %i. . . \n", i+1);

        /* Zera os valores das variaveis inteiras e string (aux) */
        contador[i] = 0;
        junta[i] = 0;
        j = 0;
        aux[0] = '\0';

        strcpy(aux, type[i]);

        while (line_size >= 0){ /* Loop ate o fim do arquivo (EOF) */

            if(strstr(line_buf, aux) && strstr(line_buf, year)){ /* Filtra apenas as linhas que contem o codigo e ano escolhidos */
                val = strtok(line_buf, SEP); /* Extrai primeira coluna */

                for(k = 0 ; k < 9 ; k++){
                    val = strtok(NULL, SEP); /* Pula ate a coluna desejada */
                }

                junta[i] += atof(val); /* Acumula o valor da coluna */
                j++; /* Contador de linhas que passaram na filtragem */

            }

            contador[i] = j;
            result[i] = junta[i] / contador[i]; /* Resultado da media */

            if(getline(&line_buf, &line_buf_size, csvfile) < 0){ /* Verificacao do retorno da getline (para identificar EOF) */
                fclose(csvfile); /* Fim do uso do arquivo para loop atual (reset) */
                break;
            }
        }
    }
    printf("Concluido!!! \n");

    system("pause");
    system("cls");

    year[strlen(year)-1] = '\0'; /* Retira a concatenacao anterior de "-" para impressao */
    printf("Media de obitos novos por cidade e ano\n");
    printf("Ano: %s\n\n", year);

    for(i = 0 ; i < n ; i++){
        type[i][strlen(type[i])-1] = '\0'; /* Tira a formatacao do separador da type[i] */
        printf("%s", citycodename[i]);
        for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
            printf(" ");
        }
        printf("%.2f\n", result[i]);
    }

    printf("\nDeseja salvar esse resultado (S/N)? ");
    char dec = getch(); /* Uso do get character para capturar um unico caractere */
    printf("%c \n", dec); /* Confirmacao do input */

    /* Estrutura de decisao para verificar validacao da entrada "char dec" para Sim, Nao, ou Invalido */
    if(dec == 'S' || dec == 's'){

        /* Captura da string que nomeia o arquivo, e impressao dos dados */
        printf("Digite o nome do arquivo: ");
        char savedfilename[26];
        scanf("%s", &savedfilename);
        strcat(savedfilename, ".csv");

        FILE* newfile  = fopen ("savedfile.csv", "w"); /* Criacao e abertura do arquivo csv para escrever*/

        fprintf(newfile, "Media de obitos novos por cidade e ano\n");
        fprintf(newfile, "Ano: %s\n", year);

        for(i = 0 ; i < n ; i++){
            fprintf(newfile, "%s", citycodename[i]);
            for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
                fprintf(newfile, " ");
            }
            fprintf(newfile, "%.2f\n", result[i]);
        }

        fclose(newfile);
        rename("savedfile.csv", savedfilename);
        printf("Resultado salvo no arquivo %s\n", savedfilename);

        resetfunction(csvfile);

    } else if(dec == 'N' || dec == 'n'){

        resetfunction(csvfile);

    } else {
        printf("Opcao invalida, retornando ao menu . . .\n");
        getch(); /* Getch sem atribuicao para pausa curta no programa */
        system("cls");
        menu(csvfile);
    }

    /* Desalocamento do ponteiro line_buf */
    free(line_buf);
    line_buf = NULL;

    return EXIT_SUCCESS;
}

int case3(FILE *csvfile){

    char *val = NULL, *line_buf = NULL;
    int i, j = 0, k, n;
    size_t line_size, line_buf_size = 0;


    char year[10]; /* String do ano para filtragem dos dados */
    printf("Digite o ano: ");
    scanf("%s", &year);

    if(atof(year) < 2020 || atof(year) > 2022){ /* Verificacao direta (ja que o dataset so consta dados de 2020 ate 2022) */
        printf("Ano invalido, nao existem dados correspondentes a %s, tente novamente\n", year);
        system("pause");
        return EXIT_FAILURE;
    }
    strcat(year, "-"); /* Adiciona a formatacao para que haja concordancia com a formatacao das datas do arquivo */


    printf("Digite o numero de codigos a serem inseridos: ");
    scanf("%i", &n); /* Determina sempre o numero de casos sendo usados assim servindo como parametro dos loops FOR */
    char type[n][10], aux[10], citycodename[n][40];


    FILE *verfile;
    int veri[n]; /* Variavel para verificacao (BOOLEANA) de cada codigo individualmente */
    for(i = 0 ; i < n ; i++){

        verfile = fopen("codigoibgever.txt", "r"); /* Abre arquivo de verificacao para codigos validos do IBGE */
        if(verfile == NULL){ /* Codigo de erro para falha no arquivo */
            printf("Erro! O arquivo de verificacao (codigoibgever.txt) nao foi encontrado...\n");
            system("pause");
            return EXIT_FAILURE;
        }

        veri[i] = 0; /* Esvazia a variavel atual veri[i] */
        printf("Digite o codigo da cidade %i: ", i+1);
        scanf("%s", &type[i]);

        line_size = 1;

        strcpy(aux, type[i]); /* Auxiliar usado para comparacao dos conteudos da type[i] na getline() */

        while (line_size >= 0){
            if(getline(&line_buf, &line_buf_size, verfile) > 0){ /* Leitura (linha por linha) do arquivo */
                if(strstr(line_buf, aux) != NULL){ /* Comparacao com o arquivo de verificacao, se sim, armazena o valor 1 na variavel veri[i] como "VERDADEIRO" */
                    val = strtok(line_buf, "3");
                    strcpy(citycodename[i], val);

                    veri[i] = 1;
                }
            } else {
                fclose(verfile); /* Reseta a abertura do arquivo para que haja a releitura no proximo caso i */
                break;
            }
        }
    }

    for(i = 0 ; i < n ; i++){
        if(veri[i] == 0){ /* Faz a verificacao 1 ou 0 para codigos invalidos */
            printf("\nCodigo (%s) invalido, visite https://www.ibge.gov.br/explica/codigos-dos-municipios.php#SP para verificar os codigos validos dos municipios de Sao Paulo\n", type[i]);
            system("pause");
            return EXIT_FAILURE;
        }
        strcat(type[i], SEP); /* Concatena o separador a string type para verificacao no dataset (de acordo com a formatacao) */
    }
    printf("\n");


    /* Extrai o cabecalho (primeira linha) */
    line_size = getline(&line_buf, &line_buf_size, csvfile);

    int contador[n];
    float junta[n];
    float result[n];
    float singleline[n][1000];

    /* Loop ate o fim dos casos */
    for(i = 0 ; i < n ; i++){

        csvfile = fopen(FILENAME, "r"); /* Reset do arquivo para leitura individual do caso i */
        printf("Carregando %i. . . \n", i+1);

        /* Zera os valores das variaveis inteiras e string (aux) */
        contador[i] = 0;
        junta[i] = 0;
        j = 0;
        aux[0] = '\0';

        strcpy(aux, type[i]);

        while (line_size >= 0){ /* Loop ate o fim do arquivo (EOF) */

            if(strstr(line_buf, aux) && strstr(line_buf, year)){ /* Filtra apenas as linhas que contem o codigo e ano escolhidos */
                val = strtok(line_buf, SEP); /* Extrai primeira coluna */

                j++; /* Contador de linhas que passaram na filtragem */

                for(k = 0 ; k < 6 ; k++){
                    val = strtok(NULL, SEP); /* Pula ate a coluna desejada */
                }

                singleline[i][j] = atof(val);

            }

            contador[i] = j;

            if(getline(&line_buf, &line_buf_size, csvfile) < 0){ /* Verificacao do retorno da getline (para identificar EOF) */
                fclose(csvfile); /* Fim do uso do arquivo para loop atual (reset) */
                break;
            }
        }
    }

    printf("Concluido!!! \n");

    system("pause");
    system("cls");

    int troca, exaux;

    for(k = 0 ; k < n ; k++){

        qsort(singleline[k], n, sizeof(int), cmpfunc);

        if(contador[k] % 2 == 0){
            exaux = contador[k]/2;
            result[k] = (singleline[k][exaux] + singleline[k][exaux+1])/2;
        } else {
            exaux = (contador[k]+1)/2;
            result[k] = singleline[k][exaux];
        }

    }


    year[strlen(year)-1] = '\0'; /* Retira a concatenacao anterior de "-" para impressao */
    printf("Mediana de casos novos por cidade e ano\n");
    printf("Ano: %s\n\n", year);

    for(i = 0 ; i < n ; i++){
        type[i][strlen(type[i])-1] = '\0'; /* Tira a formatacao do separador da type[i] */
        printf("%s", citycodename[i]);
        for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
            printf(" ");
        }
        printf("%.2f\n", result[i]);
    }

    printf("\nDeseja salvar esse resultado (S/N)? ");
    char dec = getch(); /* Uso do get character para capturar um unico caractere */
    printf("%c \n", dec); /* Confirmacao do input */

    /* Estrutura de decisao para verificar validacao da entrada "char dec" para Sim, Nao, ou Invalido */
    if(dec == 'S' || dec == 's'){

        /* Captura da string que nomeia o arquivo, e impressao dos dados */
        printf("Digite o nome do arquivo: ");
        char savedfilename[26];
        scanf("%s", &savedfilename);
        strcat(savedfilename, ".csv");

        FILE* newfile  = fopen ("savedfile.csv", "w"); /* Criacao e abertura do arquivo csv para escrever*/

        fprintf(newfile, "Mediana de casos novos por cidade e ano\n");
        fprintf(newfile, "Ano: %s\n", year);

        for(i = 0 ; i < n ; i++){
            fprintf(newfile, "%s", citycodename[i]);
            for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
                fprintf(newfile, " ");
            }
            fprintf(newfile, "%.2f\n", result[i]);
        }

        fclose(newfile);
        rename("savedfile.csv", savedfilename);
        printf("Resultado salvo no arquivo %s\n", savedfilename);

        resetfunction(csvfile);

    } else if(dec == 'N' || dec == 'n'){

        resetfunction(csvfile);

    } else {
        printf("Opcao invalida, retornando ao menu . . .\n");
        getch(); /* Getch sem atribuicao para pausa curta no programa */
        system("cls");
        menu(csvfile);
    }

    /* Desalocamento do ponteiro line_buf */
    free(line_buf);
    line_buf = NULL;

    return EXIT_SUCCESS;
}

int case4(FILE *csvfile){

    char *val = NULL, *line_buf = NULL;
    int i, j = 0, k, n;
    size_t line_size, line_buf_size = 0;


    char year[10]; /* String do ano para filtragem dos dados */
    printf("Digite o ano: ");
    scanf("%s", &year);

    if(atof(year) < 2020 || atof(year) > 2022){ /* Verificacao direta (ja que o dataset so consta dados de 2020 ate 2022) */
        printf("Ano invalido, nao existem dados correspondentes a %s, tente novamente\n", year);
        system("pause");
        return EXIT_FAILURE;
    }
    strcat(year, "-"); /* Adiciona a formatacao para que haja concordancia com a formatacao das datas do arquivo */


    printf("Digite o numero de codigos a serem inseridos: ");
    scanf("%i", &n); /* Determina sempre o numero de casos sendo usados assim servindo como parametro dos loops FOR */
    char type[n][10], aux[10], citycodename[n][40];


    FILE *verfile;
    int veri[n]; /* Variavel para verificacao (BOOLEANA) de cada codigo individualmente */
    for(i = 0 ; i < n ; i++){

        verfile = fopen("codigoibgever.txt", "r"); /* Abre arquivo de verificacao para codigos validos do IBGE */
        if(verfile == NULL){ /* Codigo de erro para falha no arquivo */
            printf("Erro! O arquivo de verificacao (codigoibgever.txt) nao foi encontrado...\n");
            system("pause");
            return EXIT_FAILURE;
        }

        veri[i] = 0; /* Esvazia a variavel atual veri[i] */
        printf("Digite o codigo da cidade %i: ", i+1);
        scanf("%s", &type[i]);

        line_size = 1;

        strcpy(aux, type[i]); /* Auxiliar usado para comparacao dos conteudos da type[i] na getline() */

        while (line_size >= 0){
            if(getline(&line_buf, &line_buf_size, verfile) > 0){ /* Leitura (linha por linha) do arquivo */
                if(strstr(line_buf, aux) != NULL){ /* Comparacao com o arquivo de verificacao, se sim, armazena o valor 1 na variavel veri[i] como "VERDADEIRO" */
                    val = strtok(line_buf, "3");
                    strcpy(citycodename[i], val);

                    veri[i] = 1;
                }
            } else {
                fclose(verfile); /* Reseta a abertura do arquivo para que haja a releitura no proximo caso i */
                break;
            }
        }
    }

    for(i = 0 ; i < n ; i++){
        if(veri[i] == 0){ /* Faz a verificacao 1 ou 0 para codigos invalidos */
            printf("\nCodigo (%s) invalido, visite https://www.ibge.gov.br/explica/codigos-dos-municipios.php#SP para verificar os codigos validos dos municipios de Sao Paulo\n", type[i]);
            system("pause");
            return EXIT_FAILURE;
        }
        strcat(type[i], SEP); /* Concatena o separador a string type para verificacao no dataset (de acordo com a formatacao) */
    }
    printf("\n");


    /* Extrai o cabecalho (primeira linha) */
    line_size = getline(&line_buf, &line_buf_size, csvfile);

    int contador[n];
    float junta[n];
    float result[n];
    float singleline[n][1000];

    /* Loop ate o fim dos casos */
    for(i = 0 ; i < n ; i++){

        csvfile = fopen(FILENAME, "r"); /* Reset do arquivo para leitura individual do caso i */
        printf("Carregando %i. . . \n", i+1);

        /* Zera os valores das variaveis inteiras e string (aux) */
        contador[i] = 0;
        junta[i] = 0;
        j = 0;
        aux[0] = '\0';

        strcpy(aux, type[i]);

        while (line_size >= 0){ /* Loop ate o fim do arquivo (EOF) */

            if(strstr(line_buf, aux) && strstr(line_buf, year)){ /* Filtra apenas as linhas que contem o codigo e ano escolhidos */
                val = strtok(line_buf, SEP); /* Extrai primeira coluna */

                j++; /* Contador de linhas que passaram na filtragem */

                for(k = 0 ; k < 8 ; k++){
                    val = strtok(NULL, SEP); /* Pula ate a coluna desejada */
                }

                singleline[i][j] = atof(val);

            }

            contador[i] = j;

            if(getline(&line_buf, &line_buf_size, csvfile) < 0){ /* Verificacao do retorno da getline (para identificar EOF) */
                fclose(csvfile); /* Fim do uso do arquivo para loop atual (reset) */
                break;
            }
        }
    }

    printf("Concluido!!! \n");

    system("pause");
    system("cls");

    int troca, exaux;

    for(k = 0 ; k < n ; k++){

        qsort(singleline[k], n, sizeof(int), cmpfunc);

        if(contador[k] % 2 == 0){
            exaux = contador[k]/2;
            result[k] = (singleline[k][exaux] + singleline[k][exaux+1])/2;
        } else {
            exaux = (contador[k]+1)/2;
            result[k] = singleline[k][exaux];
        }

    }


    year[strlen(year)-1] = '\0'; /* Retira a concatenacao anterior de "-" para impressao */
    printf("Mediana de obitos novos por cidade e ano\n");
    printf("Ano: %s\n\n", year);

    for(i = 0 ; i < n ; i++){
        type[i][strlen(type[i])-1] = '\0'; /* Tira a formatacao do separador da type[i] */
        printf("%s", citycodename[i]);
        for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
            printf(" ");
        }
        printf("%.2f\n", result[i]);
    }

    printf("\nDeseja salvar esse resultado (S/N)? ");
    char dec = getch(); /* Uso do get character para capturar um unico caractere */
    printf("%c \n", dec); /* Confirmacao do input */

    /* Estrutura de decisao para verificar validacao da entrada "char dec" para Sim, Nao, ou Invalido */
    if(dec == 'S' || dec == 's'){

        /* Captura da string que nomeia o arquivo, e impressao dos dados */
        printf("Digite o nome do arquivo: ");
        char savedfilename[26];
        scanf("%s", &savedfilename);
        strcat(savedfilename, ".csv");

        FILE* newfile  = fopen ("savedfile.csv", "w"); /* Criacao e abertura do arquivo csv para escrever*/

        fprintf(newfile, "Mediana de obitos novos por cidade e ano\n");
        fprintf(newfile, "Ano: %s\n", year);

        for(i = 0 ; i < n ; i++){
            fprintf(newfile, "%s", citycodename[i]);
            for(k = 0 ; k < (30-strlen(citycodename[i])) ; k++){ /* Padronizacao dos espacos entre os prints */
                fprintf(newfile, " ");
            }
            fprintf(newfile, "%.2f\n", result[i]);
        }

        fclose(newfile);
        rename("savedfile.csv", savedfilename);
        printf("Resultado salvo no arquivo %s\n", savedfilename);

        resetfunction(csvfile);

    } else if(dec == 'N' || dec == 'n'){

        resetfunction(csvfile);

    } else {
        printf("Opcao invalida, retornando ao menu . . .\n");
        getch(); /* Getch sem atribuicao para pausa curta no programa */
        system("cls");
        menu(csvfile);
    }

    /* Desalocamento do ponteiro line_buf */
    free(line_buf);
    line_buf = NULL;

    return EXIT_SUCCESS;
}

void resetfunction(FILE *csvfile){

    char key;

    printf("\nDigite [ENTER] para retornar ao menu anterior\n");

    do{
        key = getch();
    }while(key != 13); /* 13 = representacao ascii da tecla ENTER */

    system("cls");
    menu(csvfile); /* Reseta para o menu */

}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

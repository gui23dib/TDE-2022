/**bibliotecas padroes**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/**GRUPO TDE - BERMUDA 3G**/
/*
* Guilherrme Dib da Silva (6961269)
* Kadish Bernardo Ribeiro da Silva (1673604)
* Murilo Mendes Santo Sardao (7176953)
* Thiago de Andrade Prado (3821314)
* Larissa Pena
* Victor Eduardo
*/

#define FILENAME "teste.csv"

int main(void){
    setlocale(LC_ALL, "UTF-8");

    FILE *csvfile; 

    csvfile = fopen(FILENAME, "r"); 
    if(csvfile == NULL) { 
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
        system("pause");
        exit(EXIT_FAILURE);
    }


    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    
    int v_limit[3];
    int v_count = 0;
    int j = 0, k_num_vetores = 0;

    line_size = getline(&line_buf, &line_buf_size, csvfile); /*extrai cabecalho*/

    while (line_size >= 0){

    line_count++;

    printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count, line_size, line_buf_size, line_buf);

    v_limit[v_count] = atoi(line_buf);
    printf("\nAAAAAAAAAAAAAAAAA: %d\n", v_limit[v_count]);
    v_count++;

    line_size = getline(&line_buf, &line_buf_size, csvfile);


    if(v_count > 2){
        printf("\nENTROU NO TERCEIRO!!!!\n");
        k_num_vetores++;
        char filename[26] ;
        sprintf(filename, "%d", k_num_vetores);

        char num_char[3];

        FILE* newfile  = fopen(filename, "w");
        for(j=0 ; j<3 ; j++){
            sprintf(num_char, "%d\n", v_limit[j]);
            fprintf(newfile, num_char);
        }
        v_count = 0;
        fclose(newfile);
    }

    }

    free(line_buf);
    line_buf = NULL;
    fclose(csvfile);


    return EXIT_SUCCESS;
}

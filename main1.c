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
* Victor Eduardo Rodrigues de Abreu e Silva (8576891)
*/

#define ARQUIVO_BASE "dados_covid_sp_re.csv"
#define TAMANHO_SUBARQUIVOS 10

int main(void){
    setlocale(LC_ALL, "UTF-8");

    FILE *arquivo_csv_base; 

    arquivo_csv_base = fopen(ARQUIVO_BASE, "r"); 
    if(arquivo_csv_base == NULL) { 
        printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
        system("pause");
        exit(EXIT_FAILURE);
    }


    char *conteudo_linha = NULL;
    size_t conteudo_linha_tamanho = 0;
    /*int d_contador_linhas = 0;*/
    ssize_t conteudo_capturado_linha;

    char vetor_limite_de_captura[TAMANHO_SUBARQUIVOS][1024];
    int limitador_iteracoes = 0;
    int numero_k_subarquivos = 0;
    int i = 0;

    conteudo_capturado_linha = getline(&conteudo_linha, &conteudo_linha_tamanho, arquivo_csv_base); /*extrai cabecalho*/

    while (conteudo_capturado_linha >= 0){

        /*printf("chars=%06zd, buf size=%06zu, contents: %s", conteudo_capturado_linha, conteudo_linha_tamanho, conteudo_linha); LINHA DE DEBUG DA LEITURA*/ 

        conteudo_capturado_linha = getline(&conteudo_linha, &conteudo_linha_tamanho, arquivo_csv_base);

        strcpy(vetor_limite_de_captura[limitador_iteracoes], conteudo_linha);
        /*printf("\nLinha atual: %d\n", vetor_limite_de_captura[limitador_iteracoes]);*/

        limitador_iteracoes++;


        if(limitador_iteracoes >= TAMANHO_SUBARQUIVOS){
            numero_k_subarquivos++;
            printf("\nSUBARQUIVO %i CRIADO COM SUCESSO!!!\n", numero_k_subarquivos);

            char nome_subarquivo[26] ;
            sprintf(nome_subarquivo, "%d", numero_k_subarquivos); /*transforma o inteiro do contador numero_k_subarquivos em uma string em nome_subarquivo*/

            FILE* novo_subarquivo_atual  = fopen(nome_subarquivo, "w"); /*cria o novo_subarquivo_atual com o nome atribuido anteriormente (modo de escrita write)*/
            for(i=0 ; i<TAMANHO_SUBARQUIVOS ; i++){
                fprintf(novo_subarquivo_atual, vetor_limite_de_captura[i]);
            }
            limitador_iteracoes = 0;
            fclose(novo_subarquivo_atual);
        }

    }

    /* limpeza do buffer das variaveis*/
    free(conteudo_linha);
    conteudo_linha = NULL;
    fclose(arquivo_csv_base);
    free(conteudo_linha);

    printf("\n");

    return EXIT_SUCCESS;
}
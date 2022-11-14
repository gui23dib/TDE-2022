/**bibliotecas padroes**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/**GRUPO TDE - BERMUDA 3G**/
/*
* Guilherme Dib da Silva (6961269)
* Kadish Bernardo Ribeiro da Silva (1673604)
* Murilo Mendes Santo Sardao (7176953)
* Thiago de Andrade Prado (3821314)
* Larissa Sena Pereira (1309661)
* Victor Eduardo Rodrigues de Abreu e Silva (8576891)
*/

/**definicao de constantes**/
#define ARQUIVO_BASE "dados_covid_sp_teste.csv"
#define SEPARADOR ";"
#define TAMANHO_SUBARQUIVOS 365
#define MAX_LINE 2048

#define true 1
#define false 0

void verificar_arquivo(FILE *fp){ 
   /*checa se o retorno do arquivo e nulo*/
   if(fp == NULL) { 
      printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
      system("pause");
      exit(EXIT_FAILURE); /*desliga o programa*/
   }
}

int contar_linhas(char *filename) {                                 
  FILE *fp = fopen(filename,"r");
   int ch=0, linhas=0;
   verificar_arquivo(fp);
   do{
      ch = fgetc(fp);
      if(ch == '\n') linhas++;
   }while(!feof(fp)); /*vai iterar incrementando nas linhas ate o fim do arquivo*/
   fclose(fp);
   return linhas;
}

int separacao_arquivos(void){
   setlocale(LC_ALL, "UTF-8");

   FILE *arquivo_csv_base; 
   arquivo_csv_base = fopen(ARQUIVO_BASE, "r"); 
   verificar_arquivo(arquivo_csv_base); 
   /*abre e verifica status*/

   char conteudo_atual[MAX_LINE]; /*string temporaria para conteudo do fgets()*/
   fgets(conteudo_atual, MAX_LINE, arquivo_csv_base); /*extrai cabecalho do arquivo csv*/

   FILE* subarquivo_atual;
   char nome_subarquivo[MAX_LINE];
   int i = 0;

   do{
      fgets(conteudo_atual, MAX_LINE, arquivo_csv_base); 
      /*captura a linha atual da interacao*/

      sprintf(nome_subarquivo, "%d", i);
      subarquivo_atual = fopen(nome_subarquivo, "a");
         fprintf(subarquivo_atual, conteudo_atual);
      fclose(subarquivo_atual);
      /*abre um arquivo temporario e adiciona a nova linha da iteracao*/

      if(contar_linhas(nome_subarquivo) == TAMANHO_SUBARQUIVOS){ 
         i++;
      } /*avanca o subarquivo usado a cada 10 linhas no subarquivo atual*/

   }while(!feof(arquivo_csv_base));

   fclose(arquivo_csv_base);
   printf("\n");

   sprintf(nome_subarquivo, "%d", (i+1));
   FILE *fp = fopen(nome_subarquivo, "r");
   if(fp){
      /*caso os arquivosterminem em i*/
      fclose(fp);
      return i;
   } else { 
      /*caso o arquivo adicional i+1 exista*/
      fclose(fp);
      return i+1;
   }
}

int ordenacao_subarquivo(int subarquivo){

   char nome_subarquivo[26];
   sprintf(nome_subarquivo, "%d", subarquivo);

   int i;
   const int tamanho_subarquivo = contar_linhas(nome_subarquivo);

   FILE* novo_subarquivo_atual  = fopen(nome_subarquivo, "r+");

   char conteudo_subarquivo_string[MAX_LINE]; /*dado descartado da separacao de colunas*/
   char conteudo_subarquivo_seguro[tamanho_subarquivo][MAX_LINE]; /*dado descartado da separacao de colunas*/
   char conteudo_subarquivo_coluna[tamanho_subarquivo][MAX_LINE]; //TODO: SEGMENTATION FAULT ERROR (RESOLVIDO EM TAMANHO_SUBARQUIVOS = 365)

   for(i=0 ; i < tamanho_subarquivo ; i++){
      fgets(conteudo_subarquivo_string, MAX_LINE, novo_subarquivo_atual);
      strcpy(conteudo_subarquivo_seguro[i], conteudo_subarquivo_string);

      char * token = strtok(conteudo_subarquivo_string, ";");
      token = strtok(NULL, SEPARADOR);
      strcpy(conteudo_subarquivo_coluna[i], token); 
      /*separa e recebe dado da coluna desejada*/
   }
   fclose(novo_subarquivo_atual);

   int troca; /*valor true/false 1 e 0*/
   char aux[MAX_LINE]; /*auziliar para movimentacoes*/
   do {
      troca = false;
      for (i = 0; i < tamanho_subarquivo-1; i++){
         if(atoi(conteudo_subarquivo_coluna[i]) > atoi(conteudo_subarquivo_coluna[i+1])){
            strcpy(aux, conteudo_subarquivo_coluna[i]);
            strcpy(conteudo_subarquivo_coluna[i], conteudo_subarquivo_coluna[i+1]);
            strcpy(conteudo_subarquivo_coluna[i+1], aux);

            strcpy(aux, conteudo_subarquivo_seguro[i]);
            strcpy(conteudo_subarquivo_seguro[i], conteudo_subarquivo_seguro[i+1]);
            strcpy(conteudo_subarquivo_seguro[i+1], aux);
            troca = true;
         }
      }
   } while(troca);
   /*bubble sort para ordenacao interna*/
      
   novo_subarquivo_atual  = fopen(nome_subarquivo, "w");
   for(i=0 ; i < tamanho_subarquivo ; i++){
      fprintf(novo_subarquivo_atual, conteudo_subarquivo_seguro[i]);
   }

   fclose(novo_subarquivo_atual);

   return EXIT_SUCCESS;
}

int main(){
   /* COMECO ETAPAS DE DIVISAO */
   int numero_subarquivos = separacao_arquivos();
   printf("\t%i ARQUIVOS SEPARADOS E PREENCHIDOS CORRETAMENTE!\n", numero_subarquivos);
   for(int i=0 ; i<numero_subarquivos ; i++){
      printf("%i  ", i);
      ordenacao_subarquivo(i);
   }
   printf("ARQUIVOS ORDENADOS COM SUCESSO!\n");
   /* FIM ETAPAS DE DIVISAO */

   return EXIT_SUCCESS;
}
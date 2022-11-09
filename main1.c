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
* Larissa Sena Pereira ()
* Victor Eduardo Rodrigues de Abreu e Silva (8576891)
*/

#define _OPEN_SYS_ITOA_EXT
#define ARQUIVO_BASE "dados_covid_sp_re.csv"
#define TAMANHO_SUBARQUIVOS 10
#define MAX_LINE 2048
#define MAX_LINE 2048

void verificar_arquivo(FILE *fp){
   if(fp == NULL) { 
      printf("Erro! O arquivo nao foi aberto devidamente, ou nao foi encontrado...\n");
      system("pause");
      exit(EXIT_FAILURE);
   }
}

int contar_linhas(char *filename) {                                 
  FILE *fp = fopen(filename,"r");
   int ch=0;
   int lines=0;
   if (fp == NULL){
      return 0;
   }
   do{
      ch = fgetc(fp);
      if(ch == '\n'){
         lines++;
      }
   }while(!feof(fp));
   fclose(fp);
   return lines;
}

int main(void){
   setlocale(LC_ALL, "UTF-8");

   FILE *arquivo_csv_base; 
   arquivo_csv_base = fopen(ARQUIVO_BASE, "r"); 
   verificar_arquivo(arquivo_csv_base);

   char conteudo_atual[MAX_LINE]; /*string temporaria*/
   fgets(conteudo_atual, MAX_LINE, arquivo_csv_base); /*extrai cabecalho do arquvio csv*/

   FILE* subarquivo_atual;
   char nome_subarquivo[MAX_LINE];
   int i = 0;

   do{
      fgets(conteudo_atual, MAX_LINE, arquivo_csv_base);

      sprintf(nome_subarquivo, "%d", i);
      subarquivo_atual = fopen(nome_subarquivo, "a");
         fprintf(subarquivo_atual, conteudo_atual);
      fclose(subarquivo_atual);

      if(contar_linhas(nome_subarquivo) == TAMANHO_SUBARQUIVOS){
         printf("ARQUIVO %i CRIADO E PREENCHIDO CORRETAMENTE\n", i);
         i++;
      }
      
   }while(!feof(arquivo_csv_base));

   /* limpeza do buffer das variaveis*/
   fclose(arquivo_csv_base);

   printf("\n");

   return EXIT_SUCCESS;
}
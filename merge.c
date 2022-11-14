#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 365
#define D_NUMERO_SUBARQUIVOS 5
#define MAX_LINE 2048

#define ARQUIVO_FINAL "ARQUIVO_FINAL.csv"

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

const char* torneio_arvore(){
   FILE* subarquivo_atual  = fopen( "0", "r+");

   char *line = NULL;   /*ponteiro do conteudo da linha lida*/
   size_t len = 0;
   ssize_t read;  /*tamanho da linha lida*/
   read = getline(&line, &len, subarquivo_atual);

   fclose(subarquivo_atual);

   return line; /*retorna o conteudo da linha lida*/
}

int main(void) {
   int linhas_arquivo_final;
   const int total_linhas_soma_subarquivos = (((D_NUMERO_SUBARQUIVOS-1)*TAMANHO_SUBARQUIVOS) + (contar_linhas("4")+1));
   FILE*fp = fopen(ARQUIVO_FINAL,"w");
   fclose(fp);

   do{
      fp = fopen(ARQUIVO_FINAL,"a");
      fprintf(fp, torneio_arvore());
      fclose(fp);
      linhas_arquivo_final = contar_linhas(ARQUIVO_FINAL);
      printf("%i\n", linhas_arquivo_final);
   }while(linhas_arquivo_final < total_linhas_soma_subarquivos);
   /*while para verificar que arquvio final tenha um numero de linhas igual ao numero total de linhas de todos os subarquivos*/

   return EXIT_SUCCESS;
}
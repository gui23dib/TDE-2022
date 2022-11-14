#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 10
#define D_NUMERO_SUBARQUIVOS 10
#define MAX_LINE 2048

#define ARQUIVO_FINAL "arquivo_final.csv"

#define true 1
#define false 0

int contar_linhas(char filename) {
   FILE*fp = fopen(filename,"r");
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

void iteracao_arvore(char filename) {

   char nome_subarquivo_i_atual[MAX_LINE];
   char conteudo_linha[D_NUMERO_SUBARQUIVOS][MAX_LINE];

   FILE*subarquivo_atual;

   for(int i=0; i<D_NUMERO_SUBARQUIVOS; i++) {

      sprintf(nome_subarquivo_i_atual, "%d", i);
      subarquivo_atual = fopen(nome_subarquivo_i_atual, "r");
      fgets(conteudo_linha[i], MAX_LINE, subarquivo_atual);


   }
}

int main(void) {




   return EXIT_SUCCESS;
}
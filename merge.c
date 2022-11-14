#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 365
#define D_NUMERO_SUBARQUIVOS 4
#define MAX_LINE 2048

#define ARQUIVO_FINAL "arquivo_final.csv"

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
   return "ISSO E UM VENCEDOR\n";
}

int main(void) {
   int linhas_arquivo_final, i=0;
   FILE*fp = fopen("ARQUIVO_FINAL","w");
   fclose(fp);
   char vencedor_arvore[MAX_LINE]; 

   do{
      i++;
      fp = fopen("ARQUIVO_FINAL","a");
      /*sprintf(conteudo_atual, "%d\n", i);*/
      fprintf(fp, torneio_arvore());
      fclose(fp);
      linhas_arquivo_final = contar_linhas("ARQUIVO_FINAL");
      printf("%i\n", linhas_arquivo_final);
   }while(linhas_arquivo_final < (((D_NUMERO_SUBARQUIVOS-1)*TAMANHO_SUBARQUIVOS) + (contar_linhas("4")-1)));


   return EXIT_SUCCESS;
}
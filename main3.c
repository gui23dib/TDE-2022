#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 4
#define D_NUMERO_SUBARQUIVOS 3
#define MAX_LINE 2048

#define ARQUIVO_FINAL "arquivo_final.csv"

#define true 1
#define false 0

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

void apagar_linha_disputa(int nome_subarquivo_vencedor){
   char nome_subarquivo_vencedor_string[26];
   sprintf(nome_subarquivo_vencedor_string, "%d", nome_subarquivo_vencedor);

   printf("ENTROU NA FUNCAO / ARQUIVO VENCEDOR %i\n", nome_subarquivo_vencedor);

   char *conteudo_linha = NULL;
   size_t conteudo_linha_tamanho = 0;
   ssize_t conteudo_capturado_linha;
   int conteudo_temp[TAMANHO_SUBARQUIVOS-2];
   int i = 0;

   FILE *subarquivo_atual = fopen(nome_subarquivo_vencedor_string, "r");

   getline(&conteudo_linha, &conteudo_linha_tamanho, subarquivo_atual); /*O PROBLEMA CRASHA AQ*/

   int digito_vencedor = atoi(conteudo_linha);
   char digito_vencedor_string[26];
   sprintf(digito_vencedor_string, "%d\n", digito_vencedor);

   FILE *arquivo_final = fopen(ARQUIVO_FINAL, "a");
      fprintf(arquivo_final, digito_vencedor_string);
   fclose(arquivo_final);

   do{
      conteudo_capturado_linha = getline(&conteudo_linha, &conteudo_linha_tamanho, subarquivo_atual);
      conteudo_temp[i] = atoi(conteudo_linha);
      printf("NOVAS LINHAS TEMPORARIAS %i : %i\n", i+1, conteudo_temp[i]);
      i++;
   }while (conteudo_capturado_linha > 0);
   fclose(subarquivo_atual);

   FILE *arquivo_temporario = fopen("temp", "w");
   char linha_atual[26];

   for(i=0 ; i<TAMANHO_SUBARQUIVOS ; i++){
      sprintf(linha_atual, "%i\n", conteudo_temp[i]);
      if(conteudo_temp[i] == 0) break;
      fprintf(arquivo_temporario, linha_atual);
   }
   fclose(arquivo_temporario);

   remove(nome_subarquivo_vencedor_string);
   rename("temp", nome_subarquivo_vencedor_string);

   /*arquivo_final = fopen(nome_subarquivo_vencedor_string, "r");
   char string[100];
   fgets(string, 100, arquivo_final);
   fgets(string, 100, arquivo_final);
   char comp = "0";
   if(string == comp){
      printf("OPS ESSE E O UTLIMO\n");
      fclose(arquivo_final);
      if (remove(nome_subarquivo_vencedor_string)) {
      printf("O ARQUIVO %i FOI EXCLUIDO.\n", nome_subarquivo_vencedor); 
   } else {
      printf("O ARQUIVO %i NAAAAO FOI EXCLUIDO\n");
   }
   }
   fclose(arquivo_final);*/
   /*int result = rename("temp", nome_subarquivo_vencedor_string);
   if (result == 0) {
      printf("O ARQUIVO TEMPORARIO FOI RENOMEADO.\n"); 
   } else {
      printf("The file could not be renamed.\n");
   }*/
}

void disputa_arvore(){
   char bloco_disputa_atual_string[1000];
   int bloco_disputa_int[D_NUMERO_SUBARQUIVOS];
   int i;

   char nome_subarquivo[26];
   FILE *subarquivo_atual;
   for(i=0 ; i<D_NUMERO_SUBARQUIVOS; i++){
      sprintf(nome_subarquivo, "%d", (i+1));
      subarquivo_atual = fopen(nome_subarquivo, "r");
      fgets(bloco_disputa_atual_string, 100, subarquivo_atual);
      bloco_disputa_int[i] = atoi(bloco_disputa_atual_string);
      fclose(subarquivo_atual);
      printf("DISPUTA = SUBARQUIVO %i: %d\n", i+1, bloco_disputa_int[i]);
   }

   int numero_menor_disputa_atual = bloco_disputa_int[0];
   int indice_menor_disputa_atual = 1;
   for(i = 0 ; i < D_NUMERO_SUBARQUIVOS ; i++){
      if(bloco_disputa_int[i] < numero_menor_disputa_atual){
         numero_menor_disputa_atual = bloco_disputa_int[i];
         indice_menor_disputa_atual = i+1;
      }
   }

   printf("VENCEDOR DA DISPUTA: %d / NOME DO ARQUIVO %d\n\n", numero_menor_disputa_atual, indice_menor_disputa_atual);

   apagar_linha_disputa(indice_menor_disputa_atual);
}

void iteracao_arvore(char *arquivo){
   /*FILE *arquivo_final = fopen(ARQUIVO_FINAL, "a");*/
   disputa_arvore();
   /*fprintf(arquivo_final, "linha X\n");
   fclose(arquivo_final);*/
}

int main(void){
   int linhas_arquivo_final = 0;
   char *conteudo_linha = NULL;
   size_t conteudo_linha_tamanho = 0;
   ssize_t conteudo_capturado_linha;

   do{
      iteracao_arvore(ARQUIVO_FINAL);
      linhas_arquivo_final = 0;
      linhas_arquivo_final = contar_linhas(ARQUIVO_FINAL);
      printf("O arquivo final tem %d linhas\n", linhas_arquivo_final);
      printf("---------------------\n\n", linhas_arquivo_final);
   }while(linhas_arquivo_final < (TAMANHO_SUBARQUIVOS * D_NUMERO_SUBARQUIVOS));

   return EXIT_SUCCESS;
}
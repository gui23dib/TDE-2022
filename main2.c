#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 10
#define D_NUMERO_SUBARQUIVOS 10
#define MAX_LINE 2048

#define true 1
#define false 0

int main(void){

   int numero_k_subarquivos = 0;
   int i, j;
   
   for(i=0 ; i<D_NUMERO_SUBARQUIVOS ; i++){

      char nome_subarquivo[26];
      sprintf(nome_subarquivo, "%d", i);

      FILE* novo_subarquivo_atual  = fopen(nome_subarquivo, "r+");
      printf("\nSUBARQUIVO %i ABERTO\n", i); /*DEBUG*/

      char conteudo_subarquivo_string[TAMANHO_SUBARQUIVOS][MAX_LINE];
      char conteudo_subarquivo_seguro[TAMANHO_SUBARQUIVOS][MAX_LINE];
      char conteudo_subarquivo_coluna[TAMANHO_SUBARQUIVOS][MAX_LINE];

      for(j=0 ; j < TAMANHO_SUBARQUIVOS ; j++){
         fgets(conteudo_subarquivo_string[j], MAX_LINE, novo_subarquivo_atual);
         strcpy(conteudo_subarquivo_seguro[j], conteudo_subarquivo_string[j]);

         char * token = strtok(conteudo_subarquivo_string[j], ";");
         token = strtok(NULL, ";");
         strcpy(conteudo_subarquivo_coluna[j], token);


         printf("\n%s\n", token);
      }
      fclose(novo_subarquivo_atual);

      int troca;
      char aux[MAX_LINE];
      char aux_seguro[MAX_LINE];
      do {
         troca = false;
         for (j = 0; j < TAMANHO_SUBARQUIVOS-1; j++){
            if(atoi(conteudo_subarquivo_coluna[j]) > atoi(conteudo_subarquivo_coluna[j+1])){
               strcpy(aux, conteudo_subarquivo_coluna[j]);
               strcpy(conteudo_subarquivo_coluna[j], conteudo_subarquivo_coluna[j+1]);
               strcpy(conteudo_subarquivo_coluna[j+1], aux);

               strcpy(aux_seguro, conteudo_subarquivo_seguro[j]);
               strcpy(conteudo_subarquivo_seguro[j], conteudo_subarquivo_seguro[j+1]);
               strcpy(conteudo_subarquivo_seguro[j+1], aux_seguro);
               troca = true;
            }
         }
      } while(troca);

      
      novo_subarquivo_atual  = fopen(nome_subarquivo, "w");
      for(j=0 ; j < TAMANHO_SUBARQUIVOS ; j++){
         /*printf("conteudo_subarquivo %d : %d\n", i, conteudo_subarquivo_int[j]);*/ /* DEBUG */
         fprintf(novo_subarquivo_atual, conteudo_subarquivo_seguro[j]);
      }

      fclose(novo_subarquivo_atual);
      printf("\tORDENADO COM SUCESSO!\n", i);

   }

   printf("\n");

   return EXIT_SUCCESS;
}

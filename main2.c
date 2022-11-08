#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 4
#define D_NUMERO_SUBARQUIVOS 3
#define MAX_LINE 2048

#define true 1
#define false 0

int main(void){

   int numero_k_subarquivos = 0;
   int i, j;
   
   for(i=0 ; i<D_NUMERO_SUBARQUIVOS ; i++){

      char nome_subarquivo[26] ;
      sprintf(nome_subarquivo, "%d", i);

      FILE* novo_subarquivo_atual  = fopen(nome_subarquivo, "r+");
      printf("\nSUBARQUIVO %i ABERTO\n", i); /*DEBUG*/

      char conteudo_subarquivo_string[TAMANHO_SUBARQUIVOS][MAX_LINE];
      int conteudo_subarquivo_int[TAMANHO_SUBARQUIVOS];

      for(j=0 ; j < TAMANHO_SUBARQUIVOS ; j++){
         fgets(conteudo_subarquivo_string[j], MAX_LINE, novo_subarquivo_atual);
         conteudo_subarquivo_int[j] = atoi(conteudo_subarquivo_string[j]);
      }
      fclose(novo_subarquivo_atual);

      int troca;
      int aux;
      do {
         troca = false;
         for (j = 0; j < TAMANHO_SUBARQUIVOS-1; j++){
            if(conteudo_subarquivo_int[j] > conteudo_subarquivo_int[j+1]){
               aux = conteudo_subarquivo_int[j];
               conteudo_subarquivo_int[j] = conteudo_subarquivo_int[j+1];
               conteudo_subarquivo_int[j+1] = aux;
               troca = true;
            }
         }
      } while(troca);

      
      novo_subarquivo_atual  = fopen(nome_subarquivo, "w");
      for(j=0 ; j < TAMANHO_SUBARQUIVOS ; j++){
         /*printf("conteudo_subarquivo %d : %d\n", i, conteudo_subarquivo_int[j]);*/ /* DEBUG */
         fprintf(novo_subarquivo_atual, "%d\n", conteudo_subarquivo_int[j]);
      }

      fclose(novo_subarquivo_atual);
      printf("\tORDENADO COM SUCESSO!\n", i);

   }

   printf("\n");

   return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 4
#define D_NUMERO_SUBARQUIVOS 3
#define MAX_LINE 2048
#define TAM_STR 128

#define ARQUIVO_FINAL "arquivo_final.csv"

#define true 1
#define false 0

int contar_linhas(char *filename) {                                 
  FILE *fp = fopen(filename,"r");
   int ch=0;
   int lines=0;
   if(fp == NULL) return 0;
   do{
      ch = fgetc(fp);
      if(ch == '\n'){
         lines++;
      }
   }while(!feof(fp));
   fclose(fp);
   return lines;
}

void iteracao_arvore(){

   int cria_arquivo_stack(char *mensagem, int tipo) {
      FILE *arquivo_disputa_atual;
      arquivo_disputa_atual = fopen("stack_disputa", "a");
      if(tipo == 0){ /*1 para normal e 0 para fim de arquivo*/
         printf("ACABOU O ARQUIVO!\n");
         fprintf(arquivo_disputa_atual, "NULL\n");
         fclose(arquivo_disputa_atual);
         return 1;
      } 
      fprintf(arquivo_disputa_atual, mensagem);
      printf("%s", mensagem);
      fclose(arquivo_disputa_atual);
      return 0;
   }

   void iteracao_stack_disputa(){
      char nome_subarquivo_i_atual[100];
      char conteudo_linha[TAM_STR];

      FILE *subarquivo_atual;
      for(int i = 0 ; i < D_NUMERO_SUBARQUIVOS ; i++){
         subarquivo_atual = fopen(itoa(i, nome_subarquivo_i_atual, 100), "r");
         if(fgets(conteudo_linha, TAM_STR, subarquivo_atual) == NULL){
            fclose(subarquivo_atual);
            cria_arquivo_stack("NULL\n", 0);
            continue;
         }
         fclose(subarquivo_atual);
         cria_arquivo_stack(conteudo_linha, 1);
      }
   }

   int apagar_primeira_linha(char *nome_subarquivo){
      int numero_de_linhas = contar_linhas(nome_subarquivo);
      
      FILE *arquivo = fopen(nome_subarquivo, "r");
         char conteudo_linha[TAM_STR];
         fgets(conteudo_linha, TAM_STR, arquivo);

         char conteudo_temp[numero_de_linhas-1][TAM_STR]; /*LINHAS TOTAIS DO SUBARQUIVO -1 (LINHA A SER APAGADA)*/
         int i = 0;
         while(fgets(conteudo_linha, TAM_STR, arquivo) != NULL){
            strcpy(conteudo_temp[i], conteudo_linha);
            i++;
         }
      fclose(arquivo);

      FILE *arquivo_temp = fopen("temp", "w");
         for(i = 0 ; i < numero_de_linhas-1 ; i++){
            fprintf(arquivo_temp, conteudo_temp[i]);
         }
      fclose(arquivo_temp);

      remove(nome_subarquivo);
      rename("temp", nome_subarquivo);

      return 0;
   }

   void vencedor_disputa(char *string_vencedor){
      FILE *arquivo = fopen("arquivo_final.csv", "a");
         fprintf(arquivo, string_vencedor);
      fclose(arquivo);
   }

   int iteracao_disputa(){

      int menor_elemento_stack(int tamanho_vetor, int stack_inteiros[D_NUMERO_SUBARQUIVOS]){
         int menor_elemento = stack_inteiros[0];
         int indice_posicao_menor;

         for(int i = 0; i < tamanho_vetor ; i++){
            if(stack_inteiros[i] < menor_elemento){
               menor_elemento = stack_inteiros[i];
               indice_posicao_menor = i;
            }
         }

         return indice_posicao_menor;
      }

      char nome_subarquivo_i_atual[100];
      char conteudo_linha[TAM_STR];

      int vetor_stack_inteiros[D_NUMERO_SUBARQUIVOS]; /*armazena stack como inteiros para torneio*/

      FILE *arquivo_stack = fopen("stack_disputa", "r");
      for(int i = 0 ; i < D_NUMERO_SUBARQUIVOS ; i++){
         fgets(conteudo_linha, TAM_STR, arquivo_stack);
         vetor_stack_inteiros[i] = atoi(conteudo_linha);
         /*if(strcmp(conteudo_linha, "NULL\n") != 0){ //0 como retorno de strcmp() para strings iguais
            apagar_primeira_linha(itoa(i, buffer_parametro, TAM_STR));
         }*/
      }
      fclose(arquivo_stack);

      int indice_menor_elemento = menor_elemento_stack(D_NUMERO_SUBARQUIVOS, vetor_stack_inteiros);
      printf("VENCEDOR = ARQUIVO %d || NUMERO %d\n", indice_menor_elemento, vetor_stack_inteiros[indice_menor_elemento]);
      char buffer_parametro[TAM_STR];
      apagar_primeira_linha(itoa(indice_menor_elemento, buffer_parametro, TAM_STR));
      vencedor_disputa(itoa(vetor_stack_inteiros[indice_menor_elemento], buffer_parametro, TAM_STR));
      remove("stack_disputa");
      return 0;
   }


   iteracao_stack_disputa();
   iteracao_disputa();

}

int main(void){
   int linhas_arquivo_final = 0;
   char *conteudo_linha = NULL;
   size_t conteudo_linha_tamanho = 0;
   ssize_t conteudo_capturado_linha;

   do{
      linhas_arquivo_final = 0;
      linhas_arquivo_final = contar_linhas(ARQUIVO_FINAL);
      iteracao_arvore();
      printf("O arquivo final tem %d linhas\n", linhas_arquivo_final);
      printf("------------------------------------------\n\n", linhas_arquivo_final);
   }while(linhas_arquivo_final < (TAMANHO_SUBARQUIVOS * D_NUMERO_SUBARQUIVOS));

   return EXIT_SUCCESS;
}
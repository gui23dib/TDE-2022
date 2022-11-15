#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_SUBARQUIVOS 365
#define D_NUMERO_SUBARQUIVOS 5
#define MAX_LINE 2048
#define SEPARADOR ";"

#define ARQUIVO_FINAL "ARQUIVO_FINAL.csv"
#define ARQUIVO_BASE "dados_covid_sp_teste.csv"

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

void apagar_primeira_linha(char * nome_subarquivo){
   FILE * input = fopen(nome_subarquivo, "r");
   FILE * output = fopen("temp", "w");
   char texto[2048] = "";

   fgets(texto, 2048, input);
   printf("LINHA APAGADA: %s\n", texto);
   memset(texto, 0, sizeof(char) * 2048);

   while(fgets(texto, 2048, input) != NULL){
      fputs(texto, output);
      memset(texto, 0, sizeof(char) * 2048);
   }
   fclose(input);
   fclose(output);

   remove(nome_subarquivo);
   rename("temp", nome_subarquivo);
}

const char* ler_primeira_linha(int num_subarquivo){
   char nome_subarquivo[26];
   sprintf(nome_subarquivo, "%d", num_subarquivo);

   if(contar_linhas(nome_subarquivo) == 0){
      printf("VAZIO! ");
      return "-\n";
   }

   FILE* subarquivo_atual = fopen(nome_subarquivo, "r+");
      char *line = NULL;   /*ponteiro do conteudo da linha lida*/
      size_t len = 0;   
      ssize_t read;  /*tamanho da linha lida*/
      read = getline(&line, &len, subarquivo_atual);
   fclose(subarquivo_atual);

   return line;
}

const char* torneio_arvore(){
   char conteudo_subarquivos[D_NUMERO_SUBARQUIVOS][MAX_LINE]; 
   int i;

   char conteudo_subarquivo_seguro[TAMANHO_SUBARQUIVOS][MAX_LINE]; /*dado descartado da separacao de colunas*/
   char conteudo_subarquivo_coluna[TAMANHO_SUBARQUIVOS][MAX_LINE];

   for(i = 0 ; i < D_NUMERO_SUBARQUIVOS ; i++){
      strcpy(conteudo_subarquivos[i], ler_primeira_linha(i));
      strcpy(conteudo_subarquivo_seguro[i], conteudo_subarquivos[i]);

      char * token = strtok(conteudo_subarquivos[i], ";");
      token = strtok(NULL, SEPARADOR);
      strcpy(conteudo_subarquivo_coluna[i], token);
   }

   char* menor_numero = conteudo_subarquivo_coluna[0];
   int int_arquivo_vencedor = 0;

   for(i = 0 ; i < D_NUMERO_SUBARQUIVOS ; i++){
      if(atoi(conteudo_subarquivo_coluna[i]) < atoi(menor_numero)){
         menor_numero = conteudo_subarquivos[i];
         int_arquivo_vencedor = i;
      }
   }

   char* conteudo_vencedor = conteudo_subarquivo_seguro[int_arquivo_vencedor];
   char nome_subarquivo_vencedor[26];
   sprintf(nome_subarquivo_vencedor, "%d", int_arquivo_vencedor);
   printf("SUBARQUIVO VENCEDOR: %s\n", nome_subarquivo_vencedor);
   apagar_primeira_linha(nome_subarquivo_vencedor);
   printf("%s\n", conteudo_vencedor);

   return conteudo_vencedor; /*retorna o conteudo da linha lida*/
}

int main(void) {
   int linhas_arquivo_final;
   const int total_linhas_soma_subarquivos = (((D_NUMERO_SUBARQUIVOS-1)*TAMANHO_SUBARQUIVOS) + (contar_linhas("4")+1));
   const int total_linhas_arquivo_base = contar_linhas(ARQUIVO_BASE);
   
   FILE*fp = fopen(ARQUIVO_FINAL,"w");
   verificar_arquivo(fp);
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
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

int arquivos_apagados = 0;

int main(void);

void verificar_arquivo(FILE *fp, char *filename){ 
   /*checa se o retorno do arquivo e nulo*/
   if(fp == NULL) { 
      printf("Erro! O arquivo %s nao foi aberto devidamente, ou nao foi encontrado...\n", filename);
      system("pause");
      exit(EXIT_FAILURE); /*desliga o programa*/
   }
}

int contar_linhas(char *filename) {                                 
  FILE *fp = fopen(filename,"r");
   int ch=0, linhas=0;
   verificar_arquivo(fp, filename);
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

int apagar_arquivo_vazio(char * nome_subarquivo){
   remove(nome_subarquivo);
   char nome_subarquivo_velho[26];
   char nome_subarquivo_novo[26];

   if(atoi(nome_subarquivo) == (D_NUMERO_SUBARQUIVOS-arquivos_apagados)){
      return 0;
   }

   for(int i = (atoi(nome_subarquivo)+1) ; i < (D_NUMERO_SUBARQUIVOS-arquivos_apagados) ; i++){
      sprintf(nome_subarquivo_velho, "%d", i);
      sprintf(nome_subarquivo_novo, "%d", i-1);
      rename(nome_subarquivo_velho, nome_subarquivo_novo);
   }
   arquivos_apagados++;
   return 0;
}

const char* ler_primeira_linha(int num_subarquivo){
   char nome_subarquivo[26];
   sprintf(nome_subarquivo, "%d", num_subarquivo);

   if(contar_linhas(nome_subarquivo) == 0){
      apagar_arquivo_vazio(nome_subarquivo);
      printf("Apagando arquivo %i... \n%i arquivos apagados no total!\n", num_subarquivo, arquivos_apagados);
      return "---";
   } else {
      FILE* subarquivo_atual = fopen(nome_subarquivo, "r+");
         char *line = NULL;   /*ponteiro do conteudo da linha lida*/
         size_t len = 0;   
         ssize_t read;  /*tamanho da linha lida*/
         read = getline(&line, &len, subarquivo_atual);
      fclose(subarquivo_atual);
      return line;
   }
}

const char* torneio_arvore(){
   char conteudo_subarquivos[D_NUMERO_SUBARQUIVOS-arquivos_apagados][MAX_LINE]; 
   int i;

   char conteudo_subarquivo_seguro[TAMANHO_SUBARQUIVOS][MAX_LINE]; /*dado descartado da separacao de colunas*/
   char conteudo_subarquivo_coluna[TAMANHO_SUBARQUIVOS][MAX_LINE];

   for(i = 0 ; i < D_NUMERO_SUBARQUIVOS-arquivos_apagados ; i++){
      if(strcmp(ler_primeira_linha(i), "---") == 0){
         continue;
      }
      strcpy(conteudo_subarquivos[i], ler_primeira_linha(i));
      strcpy(conteudo_subarquivo_seguro[i], conteudo_subarquivos[i]);

      char * token = strtok(conteudo_subarquivos[i], ";");
      token = strtok(NULL, SEPARADOR);
      strcpy(conteudo_subarquivo_coluna[i], token);
   }

   char* menor_numero = conteudo_subarquivo_coluna[0];
   int int_arquivo_vencedor = 0;

   for(i = 0 ; i < D_NUMERO_SUBARQUIVOS-arquivos_apagados ; i++){
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

   return conteudo_vencedor; /*retorna o conteudo da linha lida*/
}

int main(void) {
   int linhas_arquivo_final;
   char nome_ultimo_subarquivo[26];
   sprintf(nome_ultimo_subarquivo, "%d", D_NUMERO_SUBARQUIVOS-arquivos_apagados-1);
   const int total_linhas_soma_subarquivos = (D_NUMERO_SUBARQUIVOS-1)*TAMANHO_SUBARQUIVOS + contar_linhas(nome_ultimo_subarquivo)+1;
   const int total_linhas_arquivo_base = contar_linhas(ARQUIVO_BASE);
   
   FILE*fp = fopen(ARQUIVO_FINAL,"w");
   verificar_arquivo(fp, ARQUIVO_FINAL);
   fclose(fp);

   do{
      fp = fopen(ARQUIVO_FINAL,"a");
      fprintf(fp, torneio_arvore());
      fclose(fp);
      linhas_arquivo_final = contar_linhas(ARQUIVO_FINAL);
   }while(linhas_arquivo_final < total_linhas_soma_subarquivos);
   printf("\nO ARQUIVO FINAL ESTA COMPLETAMENTE ORDENADO!\n");
   /*while para verificar que arquvio final tenha um numero de linhas igual ao numero total de linhas de todos os subarquivos*/

   return EXIT_SUCCESS;
}

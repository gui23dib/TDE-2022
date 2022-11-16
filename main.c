/**bibliotecas padroes**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/**GRUPO TDE - BERMUDA 3G**/
/*
* Guilherme Dib da Silva (6961269)
* Kadish Bernardo Ribeiro da Silva (1673604)
* Murilo Mendes Santo Sardao (7176953)
* Thiago de Andrade Prado (3821314)
* Larissa Sena Pereira (1309661)
* Victor Eduardo Rodrigues de Abreu e Silva (8576891)
*/

/**definicao de constantes**/
#define SEPARADOR ";"
#define TAMANHO_SUBARQUIVOS 365
#define MAX_LINE 2048

#define ARQUIVO_FINAL "ARQUIVO_FINAL.csv"
#define ARQUIVO_BASE "dados_covid_sp_teste.csv"

#define true 1
#define false 0

int arquivos_apagados = 0;

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
   }while(!feof(fp)); 
   /*itera incrementando nas linhas ate o fim do arquivo*/
   fclose(fp);
   return linhas;
}

int separacao_arquivos(void){
   setlocale(LC_ALL, "UTF-8");

   FILE *arquivo_csv_base; 
   arquivo_csv_base = fopen(ARQUIVO_BASE, "r"); 
   verificar_arquivo(arquivo_csv_base); 
   /*abre e verifica status*/

   char conteudo_atual[MAX_LINE]; /*string temporaria para conteudo do fgets()*/
   fgets(conteudo_atual, MAX_LINE, arquivo_csv_base); /*extrai cabecalho do arquivo csv*/

   FILE* subarquivo_atual; 
   char nome_subarquivo[MAX_LINE];
   int i = 0;

   do{
      fgets(conteudo_atual, MAX_LINE, arquivo_csv_base); 
      /*captura a linha atual da interacao*/

      sprintf(nome_subarquivo, "%d", i);
      subarquivo_atual = fopen(nome_subarquivo, "a");
         fprintf(subarquivo_atual, conteudo_atual);
      fclose(subarquivo_atual);
      /*abre um arquivo temporario e adiciona a nova linha da iteracao*/

      if(contar_linhas(nome_subarquivo) == TAMANHO_SUBARQUIVOS){ 
         i++;
      } /*avanca o subarquivo usado a cada 10 linhas no subarquivo atual*/

   }while(!feof(arquivo_csv_base));

   fclose(arquivo_csv_base);
   printf("\n");

   sprintf(nome_subarquivo, "%d", (i+1));
   FILE *fp = fopen(nome_subarquivo, "r");
   if(fp){
      /*caso os arquivosterminem em i*/
      fclose(fp);
      return i;
   } else { 
      /*caso o arquivo adicional i+1 exista*/
      fclose(fp);
      return i+1;
   }
}

int ordenacao_subarquivo(int subarquivo){

   char nome_subarquivo[26];
   sprintf(nome_subarquivo, "%d", subarquivo);

   int i;
   const int tamanho_subarquivo = contar_linhas(nome_subarquivo);

   FILE* novo_subarquivo_atual  = fopen(nome_subarquivo, "r+");

   char conteudo_subarquivo_string[MAX_LINE]; /*dado descartado da separacao de colunas*/
   char conteudo_subarquivo_seguro[tamanho_subarquivo][MAX_LINE]; /*dado descartado da separacao de colunas*/
   char conteudo_subarquivo_coluna[tamanho_subarquivo][MAX_LINE]; /*dado da coluna escolhida*/

   for(i=0 ; i < tamanho_subarquivo ; i++){
      fgets(conteudo_subarquivo_string, MAX_LINE, novo_subarquivo_atual);
      strcpy(conteudo_subarquivo_seguro[i], conteudo_subarquivo_string);
      /*captura a linha atual e a copia para a varaivel "segura"*/

      char * token = strtok(conteudo_subarquivo_string, ";");
      token = strtok(NULL, SEPARADOR);
      strcpy(conteudo_subarquivo_coluna[i], token); 
      /*separa e recebe dado da coluna desejada*/
   }
   fclose(novo_subarquivo_atual);

   int troca; /*valor true/false 1 e 0*/
   char aux[MAX_LINE]; /*auxiliar para movimentacoes das variaveis*/
   do {
      troca = false;
      for (i = 0; i < tamanho_subarquivo-1; i++){
         if(atoi(conteudo_subarquivo_coluna[i]) > atoi(conteudo_subarquivo_coluna[i+1])){
            strcpy(aux, conteudo_subarquivo_coluna[i]);
            strcpy(conteudo_subarquivo_coluna[i], conteudo_subarquivo_coluna[i+1]);
            strcpy(conteudo_subarquivo_coluna[i+1], aux);
            /*faz as movimentacoes logicas do valor da coluna*/

            strcpy(aux, conteudo_subarquivo_seguro[i]);
            strcpy(conteudo_subarquivo_seguro[i], conteudo_subarquivo_seguro[i+1]);
            strcpy(conteudo_subarquivo_seguro[i+1], aux);
            /*acompanha as movimentacoes principais com a variavel segura*/
            troca = true;
         }
      }
   } while(troca);
   /*bubble sort para ordenacao interna*/
      
   novo_subarquivo_atual  = fopen(nome_subarquivo, "w");
   for(i=0 ; i < tamanho_subarquivo ; i++){
      fprintf(novo_subarquivo_atual, conteudo_subarquivo_seguro[i]);
   }
   /*reabre o arquivo e escreve por cima do antigo todos os dados em ordem*/

   fclose(novo_subarquivo_atual);

   return EXIT_SUCCESS;
}

void apagar_primeira_linha(char * nome_subarquivo, int numero_subarquivos){
   FILE * input = fopen(nome_subarquivo, "r");
   FILE * output = fopen("temp", "w");
   char texto[MAX_LINE] = "";

   fgets(texto, MAX_LINE, input);
   printf("LINHA APAGADA: %s\n", texto);
   memset(texto, 0, sizeof(char) * MAX_LINE);
   /*abre o arquivo e retira somente a primeira linha*/


   while(fgets(texto, MAX_LINE, input) != NULL){
      fputs(texto, output);
      memset(texto, 0, sizeof(char) * MAX_LINE);
   }
   /*continua lendo o arquivo a partir da segunda linha e imprimindo os dados em um arquivo temporario*/

   fclose(input);
   fclose(output);

   remove(nome_subarquivo);
   rename("temp", nome_subarquivo);
   /*deleta o arquivo original e renomea o temporario para o nome do original*/
}

int apagar_arquivo_vazio(char * nome_subarquivo, int numero_subarquivos){
   remove(nome_subarquivo);
   /*deleta o arquivo vazio*/

   char nome_subarquivo_velho[26];
   char nome_subarquivo_novo[26];

   if(atoi(nome_subarquivo) == (numero_subarquivos-arquivos_apagados)){
      return 0;
   }
   /*verifica se e o ultimo arquivo a ser apagado e entao sai da funcao*/

   for(int i = (atoi(nome_subarquivo)+1) ; i < (numero_subarquivos-arquivos_apagados) ; i++){
      sprintf(nome_subarquivo_velho, "%d", i);
      sprintf(nome_subarquivo_novo, "%d", i-1);
      rename(nome_subarquivo_velho, nome_subarquivo_novo);
   }
   arquivos_apagados++;
   /*renomea todos os arquivos seguintes como o anterior e incrementa a variavel de arquivos_apagados*/

   return 0;
}

const char* ler_primeira_linha(int num_subarquivo, int numero_subarquivos){
   char nome_subarquivo[26];
   sprintf(nome_subarquivo, "%d", num_subarquivo);

   if(contar_linhas(nome_subarquivo) == 0){
      apagar_arquivo_vazio(nome_subarquivo, numero_subarquivos);
      printf("Apagando arquivo %i... \n%i arquivos apagados no total!\n", num_subarquivo, arquivos_apagados);
      return "---";
   /*verifica se o arquivo nao tem mais linhas e entao chama a funcao de apagar arquivos*/
   } else {
      FILE* subarquivo_atual = fopen(nome_subarquivo, "r+");
         char *line = NULL;   /*ponteiro do conteudo da linha lida*/
         size_t len = 0;   
         ssize_t read;  /*tamanho da linha lida*/
         read = getline(&line, &len, subarquivo_atual);
      fclose(subarquivo_atual);
      return line;
      /*le a primeira linha do arquivo passado por parametro e retorna o conteudo da linha*/
   }
}

const char* torneio_arvore(int numero_subarquivos){
   char conteudo_subarquivos[numero_subarquivos-arquivos_apagados][MAX_LINE]; 
   int i;

   char conteudo_subarquivo_seguro[TAMANHO_SUBARQUIVOS][MAX_LINE]; /*dado descartado da separacao de colunas*/
   char conteudo_subarquivo_coluna[TAMANHO_SUBARQUIVOS][MAX_LINE];

   for(i = 0 ; i < numero_subarquivos-arquivos_apagados ; i++){
      if(strcmp(ler_primeira_linha(i, numero_subarquivos), "---") == 0){
         continue;
      }
      strcpy(conteudo_subarquivos[i], ler_primeira_linha(i, numero_subarquivos));
      strcpy(conteudo_subarquivo_seguro[i], conteudo_subarquivos[i]);

      char * token = strtok(conteudo_subarquivos[i], ";");
      token = strtok(NULL, SEPARADOR);
      strcpy(conteudo_subarquivo_coluna[i], token);
   }

   char* menor_numero = conteudo_subarquivo_coluna[0];
   int int_arquivo_vencedor = 0;

   for(i = 0 ; i < numero_subarquivos-arquivos_apagados ; i++){
      if(atoi(conteudo_subarquivo_coluna[i]) < atoi(menor_numero)){
         menor_numero = conteudo_subarquivos[i];
         int_arquivo_vencedor = i;
      }
   }

   char* conteudo_vencedor = conteudo_subarquivo_seguro[int_arquivo_vencedor];
   char nome_subarquivo_vencedor[26];
   sprintf(nome_subarquivo_vencedor, "%d", int_arquivo_vencedor);
   printf("SUBARQUIVO VENCEDOR: %s\n", nome_subarquivo_vencedor);
   apagar_primeira_linha(nome_subarquivo_vencedor, numero_subarquivos);

   return conteudo_vencedor; /*retorna o conteudo da linha lida*/
}

int merge_arquivos(int numero_subarquivos){
   int linhas_arquivo_final;
   char nome_ultimo_subarquivo[26];
   sprintf(nome_ultimo_subarquivo, "%d", numero_subarquivos-arquivos_apagados-1);
   const int total_linhas_soma_subarquivos = (numero_subarquivos-1)*TAMANHO_SUBARQUIVOS + contar_linhas(nome_ultimo_subarquivo)+1;
   const int total_linhas_arquivo_base = contar_linhas(ARQUIVO_BASE);
   
   FILE*fp = fopen(ARQUIVO_FINAL,"w");
   verificar_arquivo(fp);
   fclose(fp);

   do{
      fp = fopen(ARQUIVO_FINAL,"a");
      fprintf(fp, torneio_arvore(numero_subarquivos));
      fclose(fp);
      linhas_arquivo_final = contar_linhas(ARQUIVO_FINAL);
   }while(linhas_arquivo_final < total_linhas_soma_subarquivos);
   /*while para verificar que arquvio final tenha um numero de linhas igual ao numero total de linhas de todos os subarquivos*/

   return EXIT_SUCCESS;
}

int main(){
   /* COMECO ETAPAS DE DIVISAO */
   int numero_subarquivos = separacao_arquivos();
   int i;
   printf("\t%i ARQUIVOS SEPARADOS E PREENCHIDOS CORRETAMENTE!\n", numero_subarquivos);
   for(i=0 ; i<numero_subarquivos ; i++){
      printf("%i  ", i);
      ordenacao_subarquivo(i);
   }
   printf("ARQUIVOS ORDENADOS COM SUCESSO!\n");

   printf("INICIANDO ARVORE DE TORNEIO PARA FUNDIR ARQUIVOS...\n");
   merge_arquivos(i);
   printf("\nO ARQUIVO FINAL ESTA COMPLETAMENTE ORDENADO!\n");
   /* FIM ETAPAS DE DIVISAO */

   remove("0");

   return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "csvmain.h"

// Le o conteudo do csv. Eh necessario chamar o free(linhas) no final do programa
// @returns matriz com as linhas
char** openfile(){
  char** matriz = malloc(FILE_LINES * sizeof(char*));

  setlocale(LC_ALL, "Portuguese");
  FILE *csvfile;
  csvfile = fopen(FILE_NAME, "r"); /* modo "r" de abertura permite um arquivo de texto para leitura */

  if(csvfile == NULL) {
    printf("Erro! O arquivo não foi aberto devidamente, ou não foi encontrado...\n");
    exit(1);
  }

  size_t tamanho = 0;
  char* linha_heap;
  char* linha;

  /* 
   * Ler todas as linhas do CSV 
   * Armazena todas as linhas dentro de uma matriz
   */
  int i;
  for(i = 0; i < FILE_LINES; ++i){
    getline(&linha, &tamanho, csvfile);
    linha_heap = malloc(tamanho * sizeof(char));
    strcpy(linha_heap, linha);
    matriz[i] = linha_heap;
  }

  fclose(csvfile);
  return matriz;
}

char*** get_tokens(char** linhas) {
  char** vetor_linhas;
  char** tokens;
  vetor_linhas = malloc(FILE_LINES * sizeof(vetor_linhas));
  tokens = malloc(MAX_COLUMNS * sizeof(tokens));

  int i;
  for (i = 0; i < FILE_LINES; ++i) {
    int j;
    for (j = 1; j < MAX_COLUMNS; ++j) {
  }
}

  return vetor_linhas;
}

void destroy(char** linhas) {
  free(linhas);
}

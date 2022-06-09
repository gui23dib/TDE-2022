/**bibliotecas padroes**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/**bibliotecas de usuario**/
#include "csvmain.h" /*conteudos do menu e manipulacao de dados do CSV*/

/**PARTICIPANTES**/
/*
* Guilherrme Dib da Silva (6961269)
* Kadish Bernardo Ribeiro da Silva (1673604)
* Miguel Lima do Nascimento (7408743)
* Murilo Mendes Santo Sardao (7176953)
* Thiago de Andrade Prado ()
*/

int main(void)
{
    setlocale(LC_ALL, "UTF-8");

    FILE *csvfile; /* Variavel de arquivo pelo stdio.h */

    openfile(csvfile); /* Funcao de abertura do arquivo */

    return EXIT_SUCCESS;
}

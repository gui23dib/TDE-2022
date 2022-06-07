#include "menu.h" /*biblioteca customizada*/
#include "csvmain.h"

#include <stdio.h>

int main()
{
    char** linhas = openfile();
    for (int i = 0; i < FILE_LINES; ++i) {
      printf("%s\n", linhas[i]);
    }

    menu();
    destroy(linhas);
    return 0;
}

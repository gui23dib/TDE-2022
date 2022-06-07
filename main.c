#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h" /*biblioteca customizada*/
#include "csvmain.h"

#define SUCCES 0
#define ERROR 1

#define FILENAME "dados_covid_sp.csv"

int main(void)
{
  /* Open the file for reading */
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  size_t line_size;
  FILE *fp = fopen(FILENAME, "r");
  if (!fp)
  {
    fprintf(stderr, "Error opening file '%s'\n", FILENAME);
    return EXIT_FAILURE;
  }

    char type[30];

    scanf("%s", &type);
  /* Get the first line of the file. */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Loop through until we are done with the file. */
  while (line_size >= 0)
  {
    /* Increment our line count */
    line_count++;

    /* Show the line details */
    if(strstr(line_buf, type))
    printf("[%06d] %s", line_count, line_buf);

    /* Get the next line */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  /* Free the allocated line buffer */
  free(line_buf);
  line_buf = NULL;

  /* Close the file now that we are done with it */
  fclose(fp);

  return EXIT_SUCCESS;
}

/*int main()
{
    FILE *csvfile;

    openfile(csvfile);

    menu(csvfile);

    return 0;
}*/

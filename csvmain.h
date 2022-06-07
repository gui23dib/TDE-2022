#ifndef CSVMAIN_H_INCLUDED
#define CSVMAIN_H_INCLUDED

#define FILE_LINES 535535
#define FILE_NAME "dados_covid_sp.csv"
#define LINE_LENGTH 1024
#define MAX_COLUMNS 28
#define SEP ";"

char** openfile();
char*** get_tokens(char** linha);
void destroy(char** linhas);

#endif // CSVMAIN_H_INCLUDED

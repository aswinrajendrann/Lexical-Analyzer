#ifndef LEXER_H
#define LEXER_H

#include<stdio.h>
#define MAX_LEXEME 100
#define MAX_TOKENS 1000

//structure to store all lexeme , their types and line number
typedef struct
{
    char lexeme[MAX_LEXEME];
    char type[50];
    int lnum;
}Token;

void lexical_analyzer(FILE *fp);
void process_line(char *line);

#endif
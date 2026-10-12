#ifndef TOKEN_H
#define TOKEN_H

#include<stdio.h>

int is_keyword(char *word);
int is_identifier(char *word);
int is_constant(char *word);
int is_operator(char ch);
int is_specialCharacter(char ch);
int is_multioperator(char *op);

#endif
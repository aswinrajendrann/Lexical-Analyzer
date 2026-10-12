/*Author : ASWIN RAJENDRAN
 Project : "LEXICAL ANALYZER"*/

#include<stdio.h>
#include "file.h"
#include "lexer.h"
int main()
{
    FILE *fp=openfile("sample.c");//opening file funtion
    lexical_analyzer(fp);
    closefile(fp);//closing file function
}
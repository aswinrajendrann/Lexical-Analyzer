#ifndef FILE_H
#define FILE_H

#include<stdio.h>

FILE *openfile(const char *filename);
void closefile(FILE *fp);

#endif

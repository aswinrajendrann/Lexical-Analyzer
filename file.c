#include<stdio.h>
#include "file.h"

FILE *openfile(const char *filename)//funtion to open file
{
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("Failed to open the file\n");
        return 0;
    }
    return fp;
}

void closefile(FILE*fp)//funtion to close file
{
    if(fp!=NULL)
    {
        fclose(fp);
    }
}
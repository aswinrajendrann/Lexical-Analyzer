#include<stdio.h>
#include "token.h"
#include<string.h>
#include<ctype.h>

char *keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

char operators[] = {'+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~','.'};

char *multi_operators[] = {"==", "!=", "<=", ">=", "++", "--", "&&", "||", "<<", ">>", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "->"};

char special[]={'{','}','(',')',';',':',']','[',','};

int is_keyword(char *word)//function to check if it is valid keyword
{
    for(int i=0;i<32;i++)
    {
        if(strcmp(word,keywords[i])==0)
        return 1;
    }
    return 0;
}

int is_identifier(char *word)//function to check for valid identifiers
{
    int flag=0;
    if(isalpha(word[0]))
    {
        for(int j=1;word[j]!='\0';j++)
        {
            if(!isalnum(word[j]))//identifiers only consist of alphabets and numbers
            {
                flag=1;
                break;
            }
        }
    }
    if(flag==1)
    return 0;
    else
    return 1;
}

int is_constant(char *word)//function to check for constant
{
    if((word[0]=='0'&&(word[1]=='x'||word[1]=='X')))//condition to handle hexadecimal numbers
    {
        int count =0;
        for(int i=2;word[i]!='\0';i++)
        {
            if(isxdigit(word[i]))
            {
                count++;
            }
            else
            {
                return 0;
            }
        }
        if(count>0)
        return 1;
        else
        return 0;
    }
    if(word[0]=='e'||word[0]=='E')//condtion to handle scientific notation
    return 0;
    int e_count=0,e_pos,other_count=0;
    for(int i=0;word[i]!='\0';i++)
    {
        if(word[i]=='e'||word[i]=='E')
        {
            e_count++;
            e_pos=i;
        }
    }
    if(e_count>1)
    return 0;
    int dot_count=0,digit_count=0;
    if(e_count==1)
    {
        for(int i=0;i<e_pos;i++)
        {
            if(isdigit(word[i])||word[i]=='.')
            {
                if(word[i]=='.')
                dot_count++;
                else
                digit_count++;
            }
            else
            {
                other_count++;
            }
        }
        if(other_count==0&&digit_count>0&&dot_count<=1)
        {
            digit_count=0,other_count=0;
            if(word[1+e_pos]=='-'||word[1+e_pos]=='+')
            e_pos++;
            for(int i=e_pos+1;word[i]!='\0';i++)
            {
                if(isdigit(word[i]))
                digit_count++;
                else
                other_count++;

            }
            if(digit_count>=1&&other_count==0)
            return 1;
            else
            return 0;
        }
        else
        {
            return 0;
        }
    }
    if(isdigit(word[0])||word[0]=='.')//condition to handle floating point numbers
    {
        int dot_count=0,flag=0,digit_count=0;
        for(int j=0;word[j]!='\0';j++)
        {
            if(isdigit(word[j]))
            digit_count++;
            if(word[j]=='.')
            dot_count++;
            if(isalpha(word[j]))
            flag++;
        }
        if((digit_count>0)&&(dot_count<=1)&&(flag==0))
        return 1;
        else
        return 0;
    }
    
    int flag=0;
    for(int i=0;word[i]!='\0';i++)
    {
        if(!isdigit(word[i]))
        return 0;
    }
    return 1;
}

int is_operator(char ch)//function to check for valid operators
{
    for(int i=0;i<14;i++)
    {
        if(ch==operators[i])
        {
            return 1;
        }
    }
    return 0;
}

int is_specialCharacter(char ch)//function to check for valid special characters
{
    for(int i=0;i<9;i++)
    {
        if(ch==special[i])
        return 1;
    }
    return 0;
}

int is_multioperator(char *op)//function to check for valid double operators
{
    for(int i=0;i<21;i++)
    {
        if(strcmp(op,multi_operators[i])==0)
        return 1;
    }
    return 0;
}
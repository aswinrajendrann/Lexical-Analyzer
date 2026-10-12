#include<stdio.h>
#include"lexer.h"
#include"token.h"
#include<ctype.h>
#include<string.h>

Token tokens[MAX_TOKENS];
int tokencount=0;
int line_num=0;
int in_comment=0;
void lexical_analyzer(FILE *fp)
{
    char line[100];
    while(fgets(line,sizeof(line),fp)!=NULL)//reading line by line from file till end of file
    {
        line_num++;
        process_line(line);
    }
    printf("LEXEME\t\t\tTYPE\t\t\tLINE NUMBER\n");
    printf("------------------------------------------------------------\n");
    for(int i=0;i<tokencount;i++)  //printing all lexeme type and line number
    {
        printf("%-20s\t",tokens[i].lexeme);
        printf("%-20s\t",tokens[i].type);
        printf("%d\n",tokens[i].lnum);
    }
}

void process_line(char *line)  //function to process each line
{
    int i,j,k;
    char word[100];
    for(i=0;line[i]!='\0'&&line[i]!='\n';i++) //loop will run till \n
    {
        if(in_comment==1)  // checking if we are still inside a comment block
        {
            for(int j=i;line[j]!='\0';j++)  //loop to check if comment closing is present in the line
            {
                if((line[j]=='*'&&line[j+1]=='/'))
                {
                    in_comment=0;  //if closing is found , we set in_comment to 0
                    i=j+2;    //we bring i to index and */
                    break;
                }
            }
            if(in_comment==0 && (line[i]=='\n' || line[i]=='\0'))//checking if it is end of line or null character
            break;
            if(in_comment==1)
            continue;
        }
        if(line[i]=='#'&&in_comment==0)//condition to check if it is preprocessor directory
        {
            k=0;
            for(j=i;line[j]!=' '&&line[j]!='<'&&line[j]!='\n'&&line[j]!='\0';j++)  //loop to extract v+each word
            {
                word[k]=line[j];    //extracting word
                k++;
            }
            i=j-1;
            word[k]='\0';      //adding \0 to the end of the word
            strcpy(tokens[tokencount].lexeme,word);
            strcpy(tokens[tokencount].type,"PREPROCESSOR DIRECTORY");
            tokens[tokencount].lnum=line_num;
            tokencount++;
        }

        else if(line[i]=='/'&&line[i+1]=='/'&&in_comment==0) // condition to check if it is single comment
        {
            return;
        }
        else if(line[i]=='/'&&line[i+1]=='*'&&in_comment==0)//condition to check if it is a starting of multi line comment
        {
            in_comment=1;//setting in_comment=1
            for(int j=i+2;line[j]!='\0';j++)
            {
                if((line[j]=='*'&&line[j+1]=='/'))//checking if closing of multi line comment is present
                {
                    in_comment=0;
                    i=j+1;
                    break;
                }
            }
        }
        else if((isalpha(line[i])||line[i]=='_')&&in_comment==0)//condition to check for keywords and identifier
        {
            k=0;
            //collecting the word
            for(j=i;!is_specialCharacter(line[j])&&!is_operator(line[j])&&line[j]!='.'&&line[j]!=' '&&line[j]!='\n'&&line[j]!='\0';j++)  //loop to extract v+each word
            {
                word[k]=line[j];    //extracting word
                k++;
            }
            i=j-1;
            word[k]='\0';      //adding \0 to the end of the word
            if(is_keyword(word))//checking if the word is keyword
            {

                strcpy(tokens[tokencount].lexeme,word);
                strcpy(tokens[tokencount].type,"KEYWORD");
                tokens[tokencount].lnum=line_num;
                tokencount++;

            }
            else
            {
                if(is_identifier(word))//checking if the word is identifier
                {
                    strcpy(tokens[tokencount].lexeme,word);
                    strcpy(tokens[tokencount].type,"IDENTIFIER");
                    tokens[tokencount].lnum=line_num;
                    tokencount++;
                }
                else
                {
                    strcpy(tokens[tokencount].lexeme,word);
                    strcpy(tokens[tokencount].type,"INVALID TOKEN");
                    tokens[tokencount].lnum=line_num;
                    tokencount++;
                }
            }
        }
        //condition to check if it is constant
        else if(isdigit(line[i])||(line[i]=='.'&&isdigit(line[i+1]))&&in_comment==0)
        {
            k=0;
            //collecting the constant 
            for(j=i;(((!is_operator(line[j])||line[j]=='.')&&!is_specialCharacter(line[j])&&line[j]!=' '&&line[j]!='\n'&&line[j]!='\0')||((j>i)&&(line[j-1]=='e'||line[j-1]=='E')&&(line[j]=='+'||line[j]=='-')));j++)  //loop to extract v+each word
            {
                word[k]=line[j];    //extracting word
                k++;
            }
            i=j-1;
            word[k]='\0';      //adding \0 to the end of the word
            if(is_constant(word))//checking if it is a contant
            {
                strcpy(tokens[tokencount].lexeme,word);
                strcpy(tokens[tokencount].type,"CONSTANT");
                tokens[tokencount].lnum=line_num;
                tokencount++;
            }
            else
            {
                strcpy(tokens[tokencount].lexeme,word);
                strcpy(tokens[tokencount].type,"INVALID TOKEN");
                tokens[tokencount].lnum=line_num;
                tokencount++;
            }
        }
        else if(is_operator(line[i])&&in_comment==0)//checking if the character is operator
        {
            char op[3];
            tokens[tokencount].lexeme[0]=line[i];
            tokens[tokencount].lexeme[1]='\0';
            op[0]=line[i];
            op[1]=line[i+1];//collecting next character also to check if it is operator
            if(is_multioperator(op))//checking if it is a valid double operator
            {
                tokens[tokencount].lexeme[1]=line[i+1];
                tokens[tokencount].lexeme[2]='\0';
                i++;
            }
            strcpy(tokens[tokencount].type,"OPERATOR");
            tokens[tokencount].lnum=line_num;
            tokencount++;
        }
        else if(is_specialCharacter(line[i])&&in_comment==0)//checking whether the character is a special character
        {
            tokens[tokencount].lexeme[0]=line[i];
            tokens[tokencount].lexeme[1]='\0';
            strcpy(tokens[tokencount].type,"SPECIAL CHARACTER");
            tokens[tokencount].lnum=line_num;
            tokencount++;
        }
        else if(line[i]=='"'&&in_comment==0)//checking if it is a beginning of a string
        {
            k=0;
            word[k++]='"';
            for(j=i+1;line[j]!='\0';j++)//collecting till \0
            {
                word[k++]=line[j];
                if(line[j]=='\\'&&line[j+1]!='\0')
                {
                    j++;
                    word[k++]=line[j];
                }
                else if(line[j]=='"')
                {
                    break;
                }
            }
            
            if(line[j]=='"') //collecting till closing  "
            {
                word[k]='\0';
                strcpy(tokens[tokencount].lexeme,word);
                strcpy(tokens[tokencount].type,"STRING");
                tokens[tokencount].lnum=line_num;
                tokencount++;
                i=j;
            }
            else//if no closing  "  is given in that line , we print invalid string
            {
                word[k]='\0';
                strcpy(tokens[tokencount].lexeme,word);
                strcpy(tokens[tokencount].type,"INVALID STRING");
                tokens[tokencount].lnum=line_num;
                tokencount++;
                i=j-1;
            }
        }
        else if(line[i]=='\''&&in_comment==0)//checking if it is a ' , to check for character
        {
            k=0;
            word[k++]='\'';
            for(j=i+1;line[j]!='\0';j++)//collecting the word
            {
                word[k++]=line[j];
                if(line[j]=='\\'&&line[j+1]!='\0')//to read escape sequences also
                {
                    j++;
                    word[k++]=line[j];
                }
                else if(line[j]=='\'')
                {
                    break;
                }
            }
            if(line[j]=='\'')
            {
                word[k]='\0';
                int count=0;
                for(int l=1;word[l]!='\'';l++)
                {
                    //checking for valid escape sequences
                    if(word[l]=='\\' && (word[l+1]=='n'||word[l+1]=='t'||word[l+1]=='b'||word[l+1]=='r'||word[l+1]=='f'||word[l+1]=='v'||word[l+1]=='a'||word[l+1]=='\\'||word[l+1]=='\''||word[l+1]=='"'||word[l+1]=='0'))
                    {
                        count++;
                        l++;
                    }
                    else
                    {
                        count++;
                    }
                    
                }
                if(count==1)//if character count inside ' ' is 1, it is a valid character
                {
                    strcpy(tokens[tokencount].lexeme,word);
                    strcpy(tokens[tokencount].type,"CHARACTER");
                    tokens[tokencount].lnum=line_num;
                    tokencount++;
                }
                else
                {
                    strcpy(tokens[tokencount].lexeme,word);
                    strcpy(tokens[tokencount].type,"INVALID CHARACTER");
                    tokens[tokencount].lnum=line_num;
                    tokencount++;
                }
                i=j;
            }
            else
            {
                word[k]='\0';
                strcpy(tokens[tokencount].lexeme,word);
                strcpy(tokens[tokencount].type,"INVALID CHARACTER");
                tokens[tokencount].lnum=line_num;
                tokencount++;
                i=j-1;
            }
        }
        else if(line[i]==' '&&in_comment==0) //if the character is space , we skip it
        {
            continue;
        }
        else
        {
            word[0]=line[i];
            word[1]='\0';
            strcpy(tokens[tokencount].lexeme,word);
            strcpy(tokens[tokencount].type,"INVALID TOKEN");
            tokens[tokencount].lnum=line_num;
            tokencount++;
        }
    }
}
//Sample code for testing

#include <stdio.h>

#define MAX 100

int main()
{
    int a = 10;
    float b = 1.5e-3;
    char c = '\n';
    char *message = "Hello \"World\"";

    // Check operators and conditions
    if (a >= 10 && b != 0)
    {
        printf("%s%c", message, c);
    }

    a++;
    a += 5;

    /* Multi-line comment
       for testing */

    return 0;
}
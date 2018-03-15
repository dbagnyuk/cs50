#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string str = GetString();
    char ini;
    
    if (str != NULL)
    {
        if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'))
        {
            ini = str[0];
            printf("%c", toupper(ini));
        }
        for (int i = 0, n = strlen(str); i < n; i++)
        {
            if ((str[i] == ' ') && (str[i+1] != ' '))
            {
                ini = str[i+1];
                printf("%c", toupper(ini));
            }
        }
    }
    printf("\n");
}
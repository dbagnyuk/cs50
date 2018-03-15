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
            if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')/* || (str[i] == '\'')*/) && ((str[i+1] >= 'a' && str[i+1] <= 'z') || (str[i+1] >= 'A' && str[i+1] <= 'Z')))
            {
                ini = str[i+1];
                printf("%c", toupper(ini));
            }
        }
    }
    printf("\n");
}
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char Crypt (int Key, int Letter);

int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf ("Usage: ./caesar [key]\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string str = GetString();
    
    int length = 0;
    while (str[length] != '\0')
    {
        if (isalpha(str[length]))
        {
           char letter = Crypt(key,str[length]);
           printf ("%c", letter);
        }
        else
        {
           printf ("%c", str[length]);
        }
        length++;
    }
        printf ("\n");
}

char Crypt (int Key, int Letter)
{
    if (isupper(Letter))
    {
        Letter = Letter + (Key % 26);
        if (Letter > 90)
        {
           Letter = Letter - 26;
        }
    }
    else if (islower(Letter))
    {
        Letter = Letter + (Key % 26);
        if (Letter > 122)
        {
           Letter = Letter - 26;
        }
    }
    return Letter;
}

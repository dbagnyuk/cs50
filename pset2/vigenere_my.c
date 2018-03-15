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
        printf ("Usage: ./vigenere [key word]\n");
        return 1;
    }

    string key = argv[1];
    
    int i = 0;
    while (key[i] != '\0')
    {
        if (isalpha(key[i]) == 0)
        {
            printf ("Usage: key word include only alphabet\n");
            return 1;
        }
        i++;
    }

    printf ("Enter the text for crypt: ");
    string str = GetString();
    
    printf ("Key word: %s\n", key);
    printf ("Decrypted string: %s\n", str);
    printf ("Crypted string: ");

    int len_str = 0;
    int len_key = 0;
    while (str[len_str] != '\0')
    {
        if (isalpha(str[len_str]))
        {
        char letter = Crypt(key[len_key],str[len_str]);
        printf ("%c", letter);

        len_key++;
            if (key[len_key] == '\0')
            {
                len_key = 0;
            }
        }
        else
        {
        printf ("%c", str[len_str]);
        }
        len_str++;
    }
    printf ("\n");
}

char Crypt (int Key, int Letter)
{
    if (isupper(Key))
    {
        Key = Key - 65;
    }
    else if (islower(Key))
    {
        Key = Key - 97;
    }
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

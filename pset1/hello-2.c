#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Sate your name: ");
    string s = GetString();
    printf("Hello, %s!\n", s);
}
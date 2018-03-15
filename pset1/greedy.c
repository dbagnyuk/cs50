#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float m;
    
    do
    {
    printf("How much change is owed? ");
    m = GetFloat();
    }
    while (m <= 0);

    int r = roundf(m * 100);

    int i =  0;
    int a =  1; //  1¢
    int ai = 0;
    int b =  5; //  5¢
    int bi = 0;
    int c = 10; // 10¢
    int ci = 0;
    int d = 25; // 25¢
    int di = 0;
    
    while (r >= d)
    {
        r = r - d;
        i++;
        di++;
    }
    while (r >= c)
    {
        r = r - c;
        i++;
        ci++;
    }
    while (r >= b)
    {
        r = r - b;
        i++;
        bi++;
    }
    while (r >= a)
    {
        r = r - a;
        i++;
        ai++;
    }

    printf("%d\n", i);
}

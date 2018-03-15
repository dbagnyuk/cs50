#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand (time(NULL));

    // initialize the Array
    const int iArraySize = 25;
    int iArray[iArraySize];
    
    // filling Array with random numbers
    for (int i = 0; i < iArraySize; ++i)
    {
        iArray[i] = rand() % 21;
    }
    
    // print out the Array
    printf ("Output Array: ");
    for (int i = 0; i < iArraySize; ++i)
    {
        printf ("%d ", iArray[i]);
    }
    printf ("\n");

    // sort Array by Selection
    for (int i = 0; i < iArraySize - 1; ++i)
    {
        int iMin = iArray[i];
        int iMinPos = i;
        for (int j = i + 1; j < iArraySize; ++j)
        {
            if (iMin > iArray[j])
            {
                iMin = iArray[j];
                iMinPos = j;
            }
        }
        int tmp = iArray[i];
        iArray[i] = iMin;
        iArray[iMinPos] = tmp;
    }

    // print out sorted Array
    printf ("Output Array after sort: ");
    for (int i = 0; i < iArraySize; ++i)
    {
        printf ("%d ", iArray[i]);
    }
    printf ("\n");
    
    return 0;
}
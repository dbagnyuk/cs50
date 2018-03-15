#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand (time(NULL));

    // initialize the Array
    const int iArraySize = 10;
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

    // ask the user what number must be founded
    printf ("Enter the number for search: ");
    int nSearch = GetInt();
    int nLower = 0;
    int nUpper = iArraySize - 1;
    //printf ("\n");
    
    // sort Array
    int iBubble;
    do
    {
        iBubble = 0;
        for (int i = 0; i < iArraySize - 1; ++i)
        {
            if (iArray[i] > iArray[i + 1])
            {
                int tmp = iArray[i];
                iArray[i] = iArray[i + 1];
                iArray[i + 1] = tmp;
                ++iBubble;
            }
        }
    } while (iBubble > 0);

    // print out sorted Array
    printf ("Output Array after sort: ");
    for (int i = 0; i < iArraySize; ++i)
    {
        printf ("%d ", iArray[i]);
    }
    printf ("\n");
    
    // search the number witch user give
    while(nLower <= nUpper)
    {
        // find the middle
        int iMiddle = (nLower + nUpper) / 2;
        if (nSearch == iArray[iMiddle])
        {
            printf ("We founded your number %d in Array.\n", nSearch);
            return 0;
        }
        else if (nSearch < iArray[iMiddle])
        {
            nUpper = iMiddle - 1;
        }
        else if (nSearch > iArray[iMiddle])
        {
            nLower = iMiddle + 1;
        }
    }
    printf ("Number is not exist in Array.\n");

    return 0;
}
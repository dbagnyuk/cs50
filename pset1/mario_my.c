#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h,p;
    do
    {
        printf("Please enter how high the pyramid must be (count of rows between 1 and 23 rows): ");
        h = GetInt();
        if (h == 0)
        {
          exit(0);
        }
    }
    while (h < 1 || h > 23);
    printf("The pyramid high is %d row, so:\n", h);    
    
    p = h;
    
    for (int row = 1; row <= h; row++)
    {
      for (int column = p-row; column > 0; column--)
      {
        printf(" ");
      }
      for (int column = row+1; column > 0; column--)
      {
        printf("#");
      }
      printf("\n");
    }
}

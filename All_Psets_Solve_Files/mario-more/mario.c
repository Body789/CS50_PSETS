#include <stdio.h>
#include <cs50.h>

int main(void)
{
//storing hieght in variable
    int h;
//prompt user for hiegt
    do
    {
        h = get_int("Hieght: ");
    }
    while (h < 1 || h > 8);
//loop for lines
    for (int i = 0; i < h; i++)
  {
      //loop for spaces
      for (int d = h-1; d > i; d--)
      {
            printf(" ");
      }
      //loop for hashes
      for (int j = -1; j < i; j++)
      {
         printf("#");
      }
         printf("  ");
    for (int k = -1; k < i; k++)
    {
        printf("#");
    }
        printf("\n");
  }
}
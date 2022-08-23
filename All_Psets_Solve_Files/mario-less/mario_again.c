#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h = 0;
    do
    {
        h = get_int("enter hieght: ");
    }
    while(h < 1 || h > 8);
    for(int i = 0; i < h; i++)
    {
        for(int j = h - 1; j > i; j--)
        {
            printf(".");
        }
        for(int x = -1; x < i; x++)
        {
            printf("#");
        }
        printf("  ");
        for(int n = -1; n < i; n++)
        {
            printf("#");
        }
        printf("\n");
    }
}
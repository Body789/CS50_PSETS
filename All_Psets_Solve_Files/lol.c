#include <stdio.h>

int main(void)
{
    int i[4] = {9, 6, 7, 8};
    int b[2] = {5,6};
    b[0] = i[0];
    b[0] = 7;
    printf("%i\n", i[0]);
}
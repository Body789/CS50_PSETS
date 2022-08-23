#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{
    int b = get_int("n: ");
    b = collatz(b);
    printf("%i\n", b);
}

int collatz(int n)
{
    if( n == 1)
        return 0;
    else if (n % 2 == 0)
        return 1 + collatz(n/2);
    else
        return 1 + collatz(n * 3 + 1);
}
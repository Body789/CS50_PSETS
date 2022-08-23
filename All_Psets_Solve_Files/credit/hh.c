#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdbool.h>

long get_number(void);
int get_length(long x);
int checksum(long x,int l);

int main(void)
{
    long credit_number = get_number();
    int length = get_length(credit_number);
    int ch = checksum(credit_number,2);
    printf("%i",ch);
    if(length !=13 && length !=15 && length !=13 && length != 16)
    {
        printf("INVALID\n");
    }
    else if(length == 15 && ((340000000000000 <= credit_number && credit_number < 350000000000000) || (370000000000000 <= credit_number && credit_number < 380000000000000)) && ch != 0)
    {
        printf("AMEX\n");
    }
    else if((length == 13 || length == 16) && ((4000000000000 <= credit_number && credit_number < 5000000000000) || (4000000000000000 <= credit_number && credit_number < 5000000000000000)) && ch != 0)
    {
        printf("VISA\n");
    }
    else if(length == 16 && 5100000000000000 <= credit_number && credit_number < 5600000000000000 && ch != 0)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

long get_number(void)
{
    long n;
    do
    {
    n = get_long("Number: ");
    }
    while(n<0);
    return n;
}

int get_length(long n)
{
    int i;
    for(i = 0; n>=1; i++)
    {
        n = n * 0.1;
    }
    return i;
}

int checksum(long x,int l)
{
        int sum1 =0;
        int sum2 = 0;
        int sum = 0;
        int multi = 0;
        int y = 0;
        int m;
        long t = x;
    for(int i = 1; i <= l; i++)
    {
        double s = i;
        double n = 10;
        double z = pow(n, s);
        long b = z;
         t = (x % b);
        if(i % 2 == 0)
        {
        y = t % (b/10);
        m = y;
        t = t - y;
        t = t / (b/10);
        multi = t * 2;
        //t = 0;
        }
        else if(i % 2 != 0 && i > 1)
        {
        y = t % (b/10);
        t = t - y;
        t = t / (b/10);
        multi = 0;
        }
        if(multi > 9)
        {
            multi = multi - 9;
        }
        sum1 = sum1 + multi;
        sum2 = sum2 + t;
        sum = sum2 + sum1;
    }
/*        bool k;
        if(sum % 10 == 0)
        {
             k = 1;
        }
        else
        {
             k = 0;
        }*/
        return m;
}
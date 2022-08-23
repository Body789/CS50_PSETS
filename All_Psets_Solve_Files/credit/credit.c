#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_length(long card);
int check(int card[], int length);
//the functions are above
int main(void)
{
    //main variables
    long credit_number = get_long("enter number: ");
    int length = get_length(credit_number);
    int nums[length];
    //adding digits to array
    for (int i = length - 1; i >= 0; i--)
    {
        int x = credit_number % 10;
        nums[i] = x;
        credit_number -= x;
        credit_number /= 10;
    }
    //checking
    int h = check(nums, length);
    //printf("%i",h);
    //determining
    if (h != 0)
    {
        if (length == 15 && nums[0] == 3 && (nums[1] == 3 || nums[1] == 7))
        {
            printf("AMEX\n");
            return 0;
        }
        else if (length == 16 && nums[0] == 5 && (nums[1] == 1 || nums[1] == 2 || nums[1] == 3 || nums[1] == 4 || nums[1] == 5))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if ((length == 16 || length == 13) && nums[0] == 4)
        {
            printf("VISA\n");
            return 0;
        }
    }
    printf("INVALID\n");
}
int get_length(long card)
{
    int i;
    for (i = 0; card >= 1; i++)
    {
        card /= 10;
    }
    return i;
}
//check func
//fafdf
//fff
//fggg
//ffaaa
int check(int card[], int length)
{
    int z;
    int sum = 0;
    for (int i = length - 2; i >= 0; i -= 2)
    {
        z = card[i] * 2;
        if (z > 9)
        {
            sum += z % 10;
            z = trunc(z / 10);
            sum += z;
        }
        else
        {
            sum += z;
        }
    }
    for (int i = length - 1; i >= 0; i -= 2)
    {
        z = card[i];
        sum += z;
    }
    return sum % 10 == 0;
}
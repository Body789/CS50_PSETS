#include <stdio.h>
#include <cs50.h>

bool valid_triangle(double x, double y, double z);

int main()
{
    double side[3];
for (int i = 0; i <3; i++)
    {
    do
    {
    side[i] = get_double("side: ");
    }
    while (side[i] <= 0);
    }
if (valid_triangle(side[0], side[1], side[2]) != 0)
{
    printf("valid\n");
}
else
{
    printf("invalid\n");
}
}

bool valid_triangle(double x, double y, double z)
{
    double s = x + y + z;
    if (x > s/2 || y > s/2 || z > s/2)
    {
        return false;
    }
        return true;
}
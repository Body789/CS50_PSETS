#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument

    // Make sure every character in argv[1] is a digit

    // Convert argv[1] from a `string` to an `int`

    // Prompt user for plaintext

    // For each character in the plaintext:

    // Rotate the character if it's a letter

    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Make sure every character in argv[1] is a digit
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Convert argv[1] from a `string` to an `int`
    int k = atoi(argv[1]);
    // Prompt user for plaintext
    string main = get_string("plaintext: ");
    int b = strlen(main);
    printf("ciphertext: ");
    // For each character in the plaintext:
    for (int i = 0; i < b; i++)
    {
        // Rotate the character if it's a letter
        printf("%c", rotate(main[i], k));
    }
    printf("\n");
}

bool only_digits(string s)
{
    bool flag = true;
    int l = strlen(s);
    for (int i = 0; i < l; i++)
    {
        if (isdigit(s[i]) == false)
        {
            flag =  false;
        }
    }
    return flag;
}

char rotate(char c, int n)
{
    if (isalpha(c))
    {
        if (islower(c))
        {
            c -= 'a';
            c = (c + n) % 26;
            c += 'a';
        }
        else
        {
            c -= 'A';
            c = (c + n) % 26;
            c += 'A';
        }
    }
    return c;
}
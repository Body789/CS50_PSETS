//check yhat key length is 26
//chek for non repeated characters
//check that characters are alphapetic

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//for strlen and others

//function will encrypt
char rotate(char c, string s);
int main(int argc, string argv[])
{
    //check that argument contains key
    if (argc != 2)
    {
        //printing error message
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //check that argument is correct
    if (strlen(argv[1]) != 26)
    {
        //printing error message
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        char n = argv[1][i];
        for (int j = 0; j < i; j++)
        {
            if (toupper(argv[1][j]) == toupper(n))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }
    //check if each character is alphapetic
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    //getting plaintext from the user
    string plain_text = get_string("Plain text:  ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain_text); i++)
    {
        if (isalpha(plain_text[i]))
        {
            printf("%c", rotate(plain_text[i], argv[1]));
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
}

char rotate(char c, string s)
{
    //rotate lower into lower
    if (islower(c))
    {
        c -= 'a';
        int v = c;
        c = tolower(s[v]);
    }
    //rotate upper into upper
    if (isupper(c))
    {
        c -= 'A';
        int v = c;
        c = toupper(s[v]);
    }
    return c;
}
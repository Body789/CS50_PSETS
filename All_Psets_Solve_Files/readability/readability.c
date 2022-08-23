#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//libraries
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
//functions
int main(void)
{
    //grade
    //man
    //girl
    //kkkk
    //;lkj
    //ىتن
    string text = get_string("Text: ");
    float L = count_letters(text);
    float S = count_sentences(text);
    float m = count_words(text);
    L = L / m * 100;
    S = S / m * 100;
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    //lkldfk
    int count = 0;
    int l = strlen(text);
    for (int i = 0; i < l; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}
//vas
int count_words(string text)
{
    int count = 0;
    int l = strlen(text);
    for (int i = 0; i < l; i++)
    {
        char c = text[i];
        if (c == ' ')
        {
            count++;
        }
    }
    return count + 1;
}
//kjjsdfl
int count_sentences(string text)
{
    int count = 0;
    int l = strlen(text);
    for (int i = 0; i < l; i++)
    {
        char c = text[i];
        if (c == '.' || c == '?' || c == '!')
        {
            count++;
        }
    }
    return count;
}
# Import
from cs50 import get_string

# Main program


def main():
    # Getting text from user
    text = get_string('Text: ')
    # Calculating average number of letters per 100 words
    L = letters(text) / words(text) * 100
    # Calculating average number of sentences per 100 words
    S = sentences(text) / words(text) * 100
    # Calculating grade
    grade = round(0.0588 * L - 0.296 * S - 15.8)
    # Detecting best output
    if grade < 1:
        print('Before Grade 1')
    elif grade > 16:
        print('Grade 16+')
    else:
        print(f'Grade {grade}')

# Function to calculate number of words


def words(t):
    # Variable to store number of words
    sum = 1
    # Loop to check each caracter
    for c in t:
        # check if new word
        if c == ' ':
            sum += 1
    return sum

# Function to calculate number of letters


def letters(t):
    # Variable to store number of letters
    sum = 0
    # Loop to check each caracter
    for c in t:
        # check if alphabetic
        if c.isalpha():
            sum += 1
    return sum

# Function to calculate number of sentences


def sentences(t):
    # Variable to store number of sentences
    sum = 0
    # Loop to check each caracter
    for c in t:
        # check if end of sentence
        if c in ['?', '.', '!']:
            sum += 1
    return sum


main()
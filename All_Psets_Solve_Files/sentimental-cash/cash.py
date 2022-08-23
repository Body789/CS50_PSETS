# Function to get cents
from cs50 import get_float

# The main program


def main():
    # returning least number of coins
    c = get_float('How mush? ')
    while c < 0:
        c = get_float('How mush? ')
    c *= 100
    sum = 0
    coins = q(c)
    sum += coins
    c -= coins * 25
    coins = d(c)
    sum += coins
    c -= coins * 10
    coins = n(c)
    sum += coins
    c -= coins * 5
    coins = ce(c)
    sum += coins
    c -= coins * 1
    print(sum)

# Function tp calculate quarters


def q(x):
    # Number of quarters
    i = 0
    # Checking if number greater than a quarter
    while x > 24:
        # Updating value
        x -= 25
        i += 1
    return i

# Function tp calculate dimes


def d(x):
    # Number of dimes
    i = 0
    # Checking if number greater than a dime
    while x > 9:
        # Updating value
        x -= 10
        i += 1
    return i

# Function tp calculate nickles


def n(x):
    # Number of nickles
    i = 0
    # Checking if number greater than a nickle
    while x > 4:
        # Updating value
        x -= 5
        i += 1
    return i

# Function tp calculate cents


def ce(x):
    # Number of quarters
    i = 0
    # Checking if number greater than a cent
    while x > 0:
        # Updating value
        x -= 1
        i += 1
    return i


main()
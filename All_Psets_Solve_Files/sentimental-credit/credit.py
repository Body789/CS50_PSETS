# Function to get card number
from cs50 import get_string

# Mian function


def main():
    # Getting card number from the user
    card_number = get_string('Number: ')
    # Check card validity
    if check_validity(card_number) == True:
        # If valid detect type
        detect_type(card_number)
    else:
        print('INVALID')

# Function check validity


def check_validity(number):
    # variable to store sum
    sum = 0
    # Count i
    i = len(number) - 1
    # Check length
    if len(number) not in range(13, 17):
        return False
    else:
        # Revese the string
        number = number[::-1]
        # Loop to play with every number
        for num in number:
            # Check if number should be squared
            if i in range(len(number) - 2, -1, -2):
                l = int(num) * 2
                # Add num digits
                if l > 9:
                    sum += int(str(l)[0]) + int(str(l)[1])
                else:
                    sum += l
            else:
                sum += int(num)
            i -= 1
            # print(sum)
    if sum % 10 == 0:
        return True
    return False

# Function to detect type


def detect_type(number):
    if len(number) == 15:
        if int(number[0]) == 3:
            if int(number[1]) in [3, 7]:
                print('AMEX')
    if len(number) == 16:
        if int(number[0]) == 5:
            if int(number[1]) in range(1, 6):
                print('MASTERCARD')
    if len(number) in range(13, 17):
        if int(number[0]) == 4:
            print('VISA')
    else:
        print('INVALID')
    return


main()
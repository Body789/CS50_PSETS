# function to get hieght value
from cs50 import get_int

# variable to store hieght
h = get_int('Height: ')
# loop to check that the value is correct
while h < 1 or h > 8:
    # ask again
    h = get_int('Height: ')

# loop to print hashes
for i in range(1, h+1):
    # print space
    print(' ' * (h - i), end='')
    print('#' * i)

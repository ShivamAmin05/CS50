# TODO
from cs50 import get_int

height = get_int("Height: ")

while(height < 1 or height > 8):
    height = get_int("Enter a num 1-8, Height: ")

for i in range(1, height + 1):
    # uses concatonation inorder to print the spaces and hashes a certain number of times without needing to write another for loop
    print(" " * (height - i), end="")
    print("#" * (i), end="")

    print("  ", end="")
    print("#" * i)


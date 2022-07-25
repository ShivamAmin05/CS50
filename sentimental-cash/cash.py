# TODO
from cs50 import get_float


def coins(change, coin):
    if coin == "quarter":
        quarters = 0
        while(change - 25 >= 0):
            change -= 25
            quarters += 1
        return quarters
    if coin == "dime":
        dimes = 0
        while(change - 10 >= 0):
            change -= 10
            dimes += 1
        return dimes
    if coin == "nickel":
        nickels = 0
        while(change - 5 >= 0):
            change -= 5
            nickels += 1
        return nickels
    if coin == "penny":
        pennies = 0
        while(change - 1 >= 0):
            change -= 1
            pennies += 1
        return pennies


change = get_float("Change Owed: ") * 100
while change < 0:
    change = get_float("Enter a non-negative value: ") * 100

quarters = coins(change, "quarter")
change -= (quarters * 25)
dimes = coins(change, "dime")
change -= (dimes * 10)
nickels = coins(change, "nickel")
change -= (nickels * 5)
pennies = coins(change, "penny")
change -= (pennies * 1)

total = quarters + dimes + nickels + pennies
print(total)
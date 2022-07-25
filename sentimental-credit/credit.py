# TODO
from cs50 import get_int


def checksum(cardnum):
    reversenum = cardnum[::-1]
    sum = 0
    for i, element in enumerate(reversenum):
        if i % 2 == 0:
            sum += int(reversenum[i])
        else:
            # if there is more then 1 digit when the num is multiplied by 2, the number is slit up into two digits and added to the sum
            if int(reversenum[i]) * 2 > 9:
                digits = str(int(reversenum[i]) * 2)
                sum += int(digits[0]) + int(digits[1])
            else:
                sum += int(reversenum[i]) * 2
    return(sum % 10)


cardnum = str(get_int("Enter a card number: "))
is_valid = checksum(cardnum)
if(is_valid == 0):
    if(len(cardnum) == 15):
        if((cardnum[0] == "3" and cardnum[1] == "4") or (cardnum[0] == "3" and cardnum[1] == "7")):
            print("AMEX")
        else:
            print("INVALID")
    elif(len(cardnum) == 16):
        if(cardnum[0] == "5"):
            if(cardnum[1] == "1" or cardnum[1] == "2" or cardnum[1] == "3" or cardnum[1] == "4" or cardnum[1] == "5"):
                print("MASTERCARD")
            else:
                print("INVALID")
        elif(cardnum[0] == "4"):
            print("VISA")
        else:
            print("INVALID")
    elif(len(cardnum) == 13):
        if(cardnum[0] == "4"):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
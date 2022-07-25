#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //used to perform Luhn's algorithm
    long cardnum = get_long("Enter your credit card number: ");
    //used after carnum has been modifed, inorder to check the length and the first two digits
    long cardnum2 = cardnum;
    //used to see what the first digit of the card is
    int dig = 0;
    // used by the alogrithm to see if thesum of the final equation has a zero as its last digit
    long total = 0;
    //set to one because the counter starts at teh second to last number
    int i = 1;
    //sets length to one because later length increments up until the last two digits
    int length = 1;
    while (cardnum > 0)
    {
        // gets the number, then divides by ten and repeats till all digits are found
        dig = cardnum % 10;
        cardnum /= 10;
        //adds every digit to the total and multiplies every other digit starting from the second to last digit by two
        if (i % 2 == 0)
        {
            if (dig * 2 < 10)
            {
                total += dig * 2;
            }
            else
            {
                dig *= 2;
                while (dig > 0)
                {
                    // if a digit is bigger then ten when it is multiplied by two, it is split up into smaller digits and added to the total
                    int subdig = dig % 10;
                    dig /= 10;
                    total += subdig;
                }
            }
        }
        else
        {
            total += dig;
        }
        i++;
    }
    //if the last digit is a zero, the card is valid
    if (total % 10 == 0)
    {
        // printf("%li\n",cardnum);
        int dig2 = 0;
        while (cardnum2 > 9)
        {
            length++;
            dig2 = cardnum2 % 10;
            cardnum2 /= 10;
            dig = cardnum2 % 10;
        }
        // checks to see what type of card it is by looking at the first digit
        if (length == 16)
        {
            if (dig == 4)
            {
                printf("VISA\n");
            }
            else if (dig == 5 && dig2 == 1)
            {
                printf("MASTERCARD\n");
            }
            else if (dig == 5 && dig2 == 2)
            {
                printf("MASTERCARD\n");
            }
            else if (dig == 5 && dig2 == 3)
            {
                printf("MASTERCARD\n");
            }
            else if (dig == 5 && dig2 == 4)
            {
                printf("MASTERCARD\n");
            }
            else if (dig == 5 && dig2 == 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 13)
        {
            if (dig == 4)
            {
                printf("VISA\n");
            }
        }
        else if (length == 15)
        {
            if (dig == 3 && dig2 == 4)
            {
                printf("AMEX\n");
            }
            else if (dig == 3 && dig2 == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
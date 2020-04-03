#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_length(long num);
int check_sum(long num, int len);

int main(void)
{
    long number;
    int length;
    int checksum;
    int start;

    do
    {
        number = get_long("Number: ");    
    }
    while (number < 0);
   
    length = get_length(number);
    checksum = check_sum(number, length);
    start = number / pow(10, length-2);  

    if (checksum % 10 == 0)
    {
        if (length == 15 && (start == 34 || start == 37))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && (start == 51 || start == 52 || start == 53 || start == 54 || start == 55))   
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13 && start / 10 == 4) || (length == 16 && start / 10 == 4))
        {
            printf("VISA\n");
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

int get_length(long num)
{
    int len = 0;

    do
    {
        len += 1;
        num = (num - num % 10) / 10;
    }
    while (num > 0);

    return len;
}

int check_sum(long num, int len)
{
    int c_sum;
    int r;

    for (int i = 1; i <= len; i++)
    {
        r = num % 10;
        num = (num - r) / 10;

        if (i % 2 == 0 && 2 * r >= 10)
        {
            c_sum = c_sum + 1 + (2 * r) % 10;
        }
        else if (i % 2 == 0)
        {
            c_sum += 2 * r;
        }
        else
        {
            c_sum += r;
        }
    }
    return c_sum;
}

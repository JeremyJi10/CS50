#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long n;
    long n1;
    int l = 0;
    int checksum = 0;
    int r;

    do
    {
        n = get_long("Number: ");
    }
    while (l!= 0);

    n1 = n;

    do
    {
        l += 1;
        n1 = (n1 - n1%10) / 10;
    }
    while (n1 > 0);

    n1 = n;

    for (int i = 1; i <= l; i++)
    {
        r = n1 % 10;
        n1 = (n1 - r) / 10;

        if (i % 2 == 0 && 2 * r >= 10)
        {
            checksum = checksum + 1 + (2 * r) % 10;
        }
        else if (i % 2 == 0)
        {
            checksum += 2 * r;
        }
        else
        {
            checksum += r;
        }
    }

    if (checksum % 10 == 0)
    {
        if (l == 15 && (n/10000000000000== 34 || n/10000000000000 == 37))
        {
            printf("AMEX\n");
        }
        else if (l == 16 && (n/100000000000000==51 || n/100000000000000==52 || n/100000000000000==53 || n/100000000000000==54 || n/100000000000000==55))   
        {
            printf("MASTERCARD\n");
        }
        else if ((l == 13 && n/1000000000000 == 4) || (l == 16 && n/1000000000000000 == 4))
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
    

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        printf("%.*s", height - i, "        ");
        printf("%.*s ", i, "########");
        printf(" %.*s\n", i, "########");

        //combined: printf("%.*s%.*s  %.*s\n", height-1, "       ", i, "########", i, "########");
    }
}
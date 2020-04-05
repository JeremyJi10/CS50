#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int num = strlen(argv[1]);
        int clean = 0;
        int duplicate = 0;
        string p_text;
        string c_text;
        string alphabetical_order = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        char processing[100] = "";

        for (int i = 0; argv[1][i] != 0; i++)
        {
            if (toupper(argv[1][i]) >= 65 && toupper(argv[1][i]) <= 90) /* check cleanliness */
            {
                clean ++;
            }

            for (int j = 0; argv[1][j] != 0; j++) /* check duplicate */
            {
                if (argv[1][i] == argv[1][j] && i != j)
                {
                    duplicate ++;
                }
            }
        }

        if (num != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (clean != 26)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (duplicate != 0)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        else
        {
            p_text = get_string("plaintext: ");
            printf("ciphertext: ");

            for (int i = 0; p_text[i] != 0; i++)
            {
                if (p_text[i] >= 65 && p_text[i] <= 90)
                {
                    for (int j = 0; alphabetical_order[j] != 0; j++)
                    {
                        if (p_text[i] == alphabetical_order[j])
                        {
                            printf("%c", toupper(argv[1][j]));
                        }
                    }
                }
                else if (p_text[i] >= 97 && p_text[i] <= 122)
                {
                    for (int j = 0; alphabetical_order[j] != 0; j++)
                    {
                        if (p_text[i] == tolower(alphabetical_order[j]))
                        {
                            printf("%c", tolower(argv[1][j]));
                        }
                    }
                }
                else
                {
                    printf("%c", p_text[i]);
                }
            }
            printf("\n");
            return 0;
        }
    }
}
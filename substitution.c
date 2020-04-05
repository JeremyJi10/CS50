#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check_cleanliness(string key);
int check_duplicate(string key);
string encrypt(string key, string plain);

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
        int clean = check_cleanliness(argv[1]);
        int duplicate = check_duplicate(argv[1]);
        string p_text;
        string c_text;

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
            c_text = encrypt(argv[1], p_text);
            printf("ciphertext: %s\n", c_text);
            return 0;
        }
    }
}

/* defined functions */

int check_cleanliness(string key)
{
    int c_num = 0;

    for (int i = 0; key[i] != 0; i++)
    {
        if (toupper(key[i]) >= 65 && toupper(key[i]) <= 90)
        {
            c_num ++;
        }
    }
    return c_num;
}

int check_duplicate(string key)
{
    int d_num = 0;

    for (int i = 0; key[i] != 0; i++)
    {
        for (int j = 0; key[j] != 0; j++)
        {
            if (key[i] == key[j] && i != j)
            {
                d_num ++;
            }
        }
    }
    return d_num;
}

string encrypt(string key, string plain)
{
    string alphabetical_order = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char processing[100] = "";

    for (int i = 0; plain[i] != 0; i++)
    {
        if (plain[i] >= 65 && plain[i] <= 90)
        {
            for (int j = 0; alphabetical_order[j] != 0; j++)
            {
                if (plain[i] == alphabetical_order[j])
                {
                    char key_upper = toupper(key[j]);
                    
                    strncat(processing, &key_upper, 1);
                }
            }
        }
        else if (plain[i] >= 97 && plain[i] <= 122)
        {
            for (int j = 0; alphabetical_order[j] != 0; j++)
            {
                if (plain[i] == tolower(alphabetical_order[j]))
                {
                    char key_lower = tolower(key[j]);
                    
                    strncat(processing, &key_lower, 1);
                }
            }
        }
        else
        {
            strncat(processing, &plain[i], 1);
        }
    }
    string capher = processing;
    return capher;
}
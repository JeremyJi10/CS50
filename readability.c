#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int letters = 0;
    int words = 0;
    int sentence = 0;
    float r;

    string text = get_string("Text: ");

    for (int i = 0; text[i] != 0; i++)
    {
        if (toupper(text[i]) >= 65 && toupper(text[i]) <= 90)
        {
            letters ++;
        }
        if (letters != 0 && (i == 0 || text[i - 1] == 32))
        {
            words ++;
        }
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence ++;
        }
    }
    r = 0.0588 * ((float) letters * 100 / words) - 0.296 * ((float) sentence / ((float) words / 100)) - 15.8;

    if (r < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (r > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(r));
    }
}


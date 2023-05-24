#include "main.h"

void handComm(char *ln)
{
    int j = 0;
    int InComment = 0;

    while (ln[j] != '\0')
{
        if (ln[j] == '#')
{
InComment = 1;
}
        if (!InComment)
{
            printf("%c", ln[j]);
}
        if (ln[j] == '\n')
{
            InComment = 0;
}
        j++;
}
}

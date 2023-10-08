#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Implementation of library function gets() */
char *gets(char *s)
{
    int c;
    char *dest = s;
    while ((c = getchar()) != '\n' && c != EOF)
        *dest++ = c;
    if (c == EOF && dest == s)
    {
        /* No characters read */
        return NULL;
    }
    *dest++ = '\0'; /* Terminate string */
    return s;
}

char *get_line()
{
    char buf[4];
    char *result;
    gets(buf);
    result = malloc(strlen(buf));
}

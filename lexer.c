#include <string.h>

#include "lexer.h"

int tokenize(char *line, Token tokens[])
{
    int i = 0;
    int count = 0;

    while (line[i] != '\0')
    {
        if (line[i] == ' ' || line[i] == '\n')
        {
            i++;
            continue;
        }

        if (strncmp(&line[i], "print", 5) == 0)
        {
            tokens[count].type = TOKEN_PRINT;
            count++;

            i += 5;
            continue;
        }

        if (line[i] == '(')
        {
            tokens[count].type = TOKEN_LPAREN;
            count++;

            i++;
            continue;
        }

        if (line[i] == ')')
        {
            tokens[count].type = TOKEN_RPAREN;
            count++;

            i++;
            continue;
        }

        if (line[i] == '"')
        {
            i++;

            tokens[count].type = TOKEN_STRING;

            int j = 0;

            while (line[i] != '"' && line[i] != '\0')
            {
                tokens[count].value[j] = line[i];

                i++;
                j++;
            }

            tokens[count].value[j] = '\0';

            count++;

            if (line[i] == '"')
            {
                i++;
            }

            continue;
        }

        i++;
    }

    return count;
}
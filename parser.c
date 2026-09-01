#include <stdio.h>
#include <string.h>

#include "parser.h"

int parse_print(
    Token tokens[],
    int *position,
    int token_count,
    PrintStatement *statement
)
{
    if (*position >= token_count)
    {
        printf("Error: expected '('\n");
        return 0;
    }

    if (tokens[*position].type != TOKEN_LPAREN)
    {
        printf("Error: expected '('\n");
        return 0;
    }

    (*position)++;

    if (*position >= token_count)
    {
        printf("Error: expected string\n");
        return 0;
    }

    if (tokens[*position].type != TOKEN_STRING)
    {
        printf("Error: expected string\n");
        return 0;
    }

    strcpy(statement->value, tokens[*position].value);

    (*position)++;

    if (*position >= token_count)
    {
        printf("Error: expected ')'\n");
        return 0;
    }

    if (tokens[*position].type != TOKEN_RPAREN)
    {
        printf("Error: expected ')'\n");
        return 0;
    }

    (*position)++;

    return 1;
}
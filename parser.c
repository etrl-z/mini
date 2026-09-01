#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

int parse_print(
    Token tokens[],
    int *position,
    int token_count,
    PrintStatement *statement)
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

int parse_if(
    Token tokens[],
    int *position,
    int token_count,
    IfStatement *statement
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
        printf("Error: expected number\n");
        return 0;
    }

    if (tokens[*position].type != TOKEN_NUMBER)
    {
        printf("Error: expected number\n");
        return 0;
    }

    statement->condition = atoi(tokens[*position].value);

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

    if (*position >= token_count)
    {
        printf("Error: expected statement\n");
        return 0;
    }

    if (tokens[*position].type != TOKEN_PRINT)
    {
        printf("Error: expected 'print'\n");
        return 0;
    }

    (*position)++;

    if (!parse_print(
            tokens,
            position,
            token_count,
            &statement->body))
    {
        return 0;
    }

    return 1;
}
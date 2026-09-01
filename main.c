#include <stdio.h>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: mini <file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Error: cannot open file '%s'\n", argv[1]);
        return 1;
    }

    char line[256];

    Token tokens[MAX_TOKENS];
    int token_count = 0;

    while (fgets(line, sizeof(line), file))
    {
        token_count += tokenize(line, &tokens[token_count]);
    }

#pragma region log
    printf("\nTokens:\n");

    for (int i = 0; i < token_count; i++)
    {
        printf("Token %d: type=%d", i, tokens[i].type);

        if (tokens[i].type == TOKEN_STRING || tokens[i].type == TOKEN_NUMBER)
        {
            printf(", value=\"%s\"", tokens[i].value);
        }

        printf("\n");
    }
#pragma endregion log

    int position = 0;

    while (position < token_count)
    {
        // print("Hello World")
        if (tokens[position].type == TOKEN_PRINT)
        {
            position++;

            PrintStatement statement;

            if (parse_print(
                    tokens,
                    &position,
                    token_count,
                    &statement))
            {
                execute_print(&statement);
            }
        }

        // if (1) print("Hello World")
        else if (tokens[position].type == TOKEN_IF)
        {
            position++;

            IfStatement if_statement;

            if (parse_if(
                    tokens,
                    &position,
                    token_count,
                    &if_statement))
            {
                if (if_statement.condition)
                {
                    execute_print(&if_statement.body);
                }
            }
        }
        else
        {
            printf("Error: unexpected token\n");
            break;
        }
    }

    fclose(file);

    return 0;
}
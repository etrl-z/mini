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

    printf("\nTokens:\n");

    for (int i = 0; i < token_count; i++)
    {
        printf("Token %d: type=%d", i, tokens[i].type);

        if (tokens[i].type == TOKEN_STRING)
        {
            printf(", value=\"%s\"", tokens[i].value);
        }

        printf("\n");
    }

    int position = 0;

    PrintStatement statement;

    if (tokens[position].type == TOKEN_PRINT)
    {
        position++;

        if (parse_print(
                tokens,
                &position,
                token_count,
                &statement))
        {
            execute_print(&statement);
        }
    }

    fclose(file);

    return 0;
}
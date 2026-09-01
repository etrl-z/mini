#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 256

typedef enum
{
    TOKEN_PRINT,  // 0
    TOKEN_STRING, // 1
    TOKEN_LPAREN, // 2
    TOKEN_RPAREN, // 3
    TOKEN_EOF,    // 4
    TOKEN_UNKNOWN // 5
} TokenType;

typedef struct
{
    TokenType type;
    char value[256];
} Token;

typedef struct
{
    char value[256];
} PrintStatement;

int tokenize(char *line, Token tokens[]);

int parse_print(
    Token tokens[],
    int *position,
    int token_count,
    PrintStatement *statement);

void execute_print(PrintStatement *statement);

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

void execute_print(PrintStatement *statement)
{
    printf("%s\n", statement->value);
}
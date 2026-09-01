#ifndef PARSER_H
#define PARSER_H

#include "token.h"

typedef struct
{
    char value[256];
} PrintStatement;

int parse_print(
    Token tokens[],
    int *position,
    int token_count,
    PrintStatement *statement
);

#endif
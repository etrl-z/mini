#ifndef PARSER_H
#define PARSER_H

#include "token.h"

/* Contains the value of the Token which is going to be printed if the parser ends up correctly.
*/
typedef struct
{
    char value[256];
} PrintStatement;

/* Checks the correct syntax of the statement 'print("...")' when a print-type Token is encountered.
If the syntax is correct, the statement struct stores the value of the string-type Token which follows the print instruction.
*/
int parse_print(
    Token tokens[],
    int *position,
    int token_count,
    PrintStatement *statement
);

#endif
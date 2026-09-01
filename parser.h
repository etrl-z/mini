#ifndef PARSER_H
#define PARSER_H

#include "token.h"

/* Contains the value of the Token which is going to be printed if the parser ends up correctly.
*/
typedef struct
{
    char value[256];
} PrintStatement;

/* Defines the condition to be evaluated in the If statement. (0: false | 1: true)
*/
typedef struct
{
    int condition;
    PrintStatement body;
} IfStatement;

/* Checks the correct syntax of the statement 'print("...")' when a print-type Token is encountered.
If the syntax is correct, the statement struct stores the value of the string-type Token which follows the print instruction.
*/
int parse_print(
    Token tokens[],
    int *position,
    int token_count,
    PrintStatement *statement
);

/* Checks the correct syntax of the statement 'if("...")' when a if-type Token is encountered.
If the syntax is correct, the statement struct stores the value of the num-type Token which follows the if instruction.
*/
int parse_if(
    Token tokens[],
    int *position,
    int token_count,
    IfStatement *statement
);

#endif
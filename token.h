#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKENS 256

/* defines a struct called Token with two properties:
    - type (enumerator which defines what kind of token the compiler encounters)
    - value (char array - useful for storing the value of string-type tokens) 
*/

typedef enum
{
    TOKEN_PRINT,
    TOKEN_STRING,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct
{
    TokenType type;
    char value[256];
} Token;

#endif
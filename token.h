#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKENS 256

typedef enum
{
    TOKEN_PRINT,
    TOKEN_IF,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

/* Defines a Token struct with two properties:
- type (enumerator which defines what kind of token the compiler encounters)
- value (char array - useful for storing the value of string-type tokens)
*/
typedef struct
{
    TokenType type;
    char value[256];
} Token;

#endif
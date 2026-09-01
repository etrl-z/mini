#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKENS 256

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
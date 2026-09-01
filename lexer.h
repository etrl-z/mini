#ifndef LEXER_H
#define LEXER_H

#include "token.h"

/* Reads one char at time and evaluates wether the char belongs to a determined type of token.
If yes, sets the evaluated type and value to the current token and increments the token count.
Then skips to the next char.
*/
int tokenize(char *line, Token tokens[]);

#endif
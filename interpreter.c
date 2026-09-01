#include <stdio.h>

#include "interpreter.h"

void execute_print(PrintStatement *statement)
{
    printf("%s\n", statement->value);
}
#ifndef parser_h
#define parser_h
#include "../lexer/token.h"
#include <stddef.h>

typedef struct {
  TokenList tokens;
  size_t i;
} Parser;

#endif // parser_h

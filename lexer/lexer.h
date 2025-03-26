#ifndef lexer_h
#define lexer_h
#include "token.h"
#include <stdbool.h>

typedef struct Lexer {
  int current;
  char *source;
  char *filename;
  TokenList tokens;
  int line;
  bool had_error;
} Lexer;

// Functions
void init_lexer(Lexer *lexer, char *code, char *from_file);
void free_lexer(Lexer *lexer);
void lex(Lexer *lexer);
#endif

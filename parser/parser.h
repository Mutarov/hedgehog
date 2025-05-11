#ifndef parser_h
#define parser_h
#include "../lexer/token.h"
#include "../vm/vm.h"
#include "ast.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct parse_result {
  Ast *root;
  bool error;
  char *err_msg;
} parse_result;

typedef struct {
  TokenList tokens;
  size_t i;
  parse_result res;
  Token curr;
} Parser;

void init_parser(Parser *parser, TokenList tokens);
void free_parser(Parser *parser);
void parse(Parser *parser);

#endif // parser_h

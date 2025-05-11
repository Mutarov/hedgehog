#include "parser.h"
#include <stdio.h>

/* Memory */

void init_parse_result(parse_result *parse_result) {
  if (!parse_result)
    return; // шлем нахуй

  parse_result->root = NULL;

  parse_result->err_msg = NULL;
  parse_result->error = 0;
}

void init_parser(Parser *parser, TokenList tokens) {
  if (!parser)
    return;
  parser->tokens = tokens;
  parser->i = -1;
}

void free_parser(Parser *parser) {
  if (!parser)
    return;
  parser->i = 0;

  if (parser->res.err_msg) {
    free(parser->res.err_msg);
    parser->res.err_msg = NULL;
  }
}

/* Parse */

static bool is_at_end(Parser *parser) {
  return parser->i <= parser->tokens.used;
}

static void advance(Parser *parser) {
  if (parser && !is_at_end(parser)) {
    parser->i++;
  }
}

void parse(Parser *parser) {
  if (!parser) {
    fprintf(stderr, "Parser is NULL\n");
    return;
  }
  printf("start!\n");

  init_parse_result(&parser->res);

  while (!is_at_end(parser)) {
    Token token = pop_token(&parser->tokens);
    if (token.type == T_ERROR) {
      parser->res.error = true;
      parser->res.err_msg = "Unexpected end of tokens";
      break;
    }

    printf("\t%d(\"%s\")\n", token.type, token.lexeme);
    // Не нужно free_token(&token) - память уже освобождена в pop_token
  }
}

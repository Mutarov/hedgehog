// Implemetation of lexer.h
#include "lexer.h"
#include "../logging.h"
#include "token.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void unrecognized(Lexer *lexer, char character) {
  if (isprint(character)) {
    L_ERROR("Unrecognized character at %d in %s: %c\n", lexer->line,
            lexer->filename, character);
    lexer->had_error = true;
  } else {
    lexer->had_error = true;
  }
}

static void error(Lexer *lexer, char *message) {
  L_ERROR("Error at %d in %s: %s\n", lexer->line, lexer->filename, message);
  lexer->had_error = true;
}

static char advance(Lexer *lexer) {
  // Function fot increment lexer->current and return character
  lexer->current++;
  return lexer->source[lexer->current - 1];
}

static char peek(Lexer *lexer, int index) {
  if (lexer == NULL || lexer->source == NULL) {
    return '\0'; // Return null character if lexer or source is invalid
  }

  size_t source_length =
      strlen(lexer->source); // Get the length of the source buffer
  size_t peek_index = lexer->current + index; // Calculate the peek index

  // Check if the peek index is within bounds
  if (peek_index >= source_length) {
    return '\0'; // Return null character if out of bounds
  }

  return lexer->source[peek_index]; // Return the character at the peek index
}

bool is_end(Lexer *lexer) { return peek(lexer, 0) == '\0'; }

// match: return true if current char is equal to expected char
static bool match(Lexer *lexer, char expected) {
  if (is_end(lexer)) {
    return 0;
  }
  if (peek(lexer, 0) == expected) {
    lexer->current++;
    return true;
  }
  return false;
}

static Token create_token(TokenType type, const char *lexeme) {
  Token token;
  token.type = type;

  // Гарантируем, что lexeme не NULL и не мусор
  const char *safe_lexeme = lexeme ? lexeme : "(null)";
  token.lexeme = strdup(safe_lexeme);

  // Проверка успешности strdup
  if (!token.lexeme) {
    // В случае ошибки выделения памяти
    token.lexeme = strdup("(alloc error)");
    token.type = type;
  }

  return token;
}

static void skip_whitespaces(Lexer *lexer) {
  for (;;) {
    char c = peek(lexer, 0);
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance(lexer);
      break;
    case '\n':
      lexer->line++;
      advance(lexer);
      break;
    case '/':
      if (peek(lexer, 1) == '/') {
        // A comment goes until the end of the line.
        while (peek(lexer, 0) != '\n' && !is_end(lexer))
          advance(lexer);
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

static Token number(Lexer *lexer) {
  char buffer[64];
  int pos = 1;

  buffer[0] = peek(lexer, -1);

  while (isdigit(peek(lexer, 0)) && pos < 31) {
    buffer[pos++] = advance(lexer);
  }

  if (peek(lexer, 0) == '.' && isdigit(peek(lexer, 1))) {
    buffer[pos++] = advance(lexer);
    while (isdigit(peek(lexer, 0)) && pos < 31) {
      buffer[pos++] = advance(lexer);
    }
  }

  buffer[pos] = '\0';

  return create_token(T_INT_LITERAL, buffer);
}

static Token string(Lexer *lexer) {
    char buffer[256];
    int pos = 0;

    while (peek(lexer, 0) != '"' && !is_end(lexer) && pos < 255) {
        char c = peek(lexer, 0);
        buffer[pos++] = c;
        advance(lexer);
    }

    if (is_end(lexer)) {
        error(lexer, "Unterminated string literal");
        return create_token(T_STR_LITERAL, "(null)");
    }

    advance(lexer); 

    buffer[pos] = '\0';
    return create_token(T_STR_LITERAL, buffer);
}

void init_lexer(Lexer *lexer, char *code, char *from_file) {
  // Initialize lexer
  lexer->filename = from_file;
  init_tokenlist(&lexer->tokens);
  lexer->source = code;
  lexer->current = lexer->line = 0;
  lexer->had_error = false;
}

void lex(Lexer *lexer) {
  if (lexer == NULL || lexer->source == NULL) {
    fprintf(stderr, "Lexer is NULL");
    return;
  }
  while (!is_end(lexer) && !lexer->had_error) {
    skip_whitespaces(lexer);
    char c = advance(lexer);
    if (isdigit(c)) {
      add_token(&lexer->tokens, number(lexer));
      continue;
    }
    switch (c) {
    case '+':
      add_token(&lexer->tokens, create_token(T_PLUS, "+"));
      break;
    case '-':
      add_token(&lexer->tokens, create_token(T_MINUS, "-"));
      break;
    case '*':
      add_token(&lexer->tokens, create_token(T_STAR, "*"));
      break;
    case '/':
      add_token(&lexer->tokens, create_token(T_SLASH, "/"));
      break;
    case ';':
      add_token(&lexer->tokens, create_token(T_SEMICOLON, ";"));
      break;
    case '"':
      add_token(&lexer->tokens, string(lexer));
      break;
    case '.':
      add_token(&lexer->tokens, create_token(T_DOT, "."));
      break;
    case ',':
      add_token(&lexer->tokens, create_token(T_COMMA, ","));
      break;
    case '(':
      add_token(&lexer->tokens, create_token(T_LPAREN, "("));
      break;
    case '{':
      add_token(&lexer->tokens, create_token(T_LBRACE, "{"));
      break;
    case ')':
      add_token(&lexer->tokens, create_token(T_RPAREN, ")"));
      break;
    case '}':
      add_token(&lexer->tokens, create_token(T_RBRACE, "}"));
      break;
    default:
      unrecognized(lexer, peek(lexer, -1));
      break; // TODO: Add Syntax Errors
    }
  }
}

void free_lexer(Lexer *lexer) {
  free_tokenlist(&lexer->tokens);
  lexer->source = NULL;
  lexer->filename = NULL;
  lexer->current = lexer->line = 0;
}

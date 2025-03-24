// Implemetation of lexer.h
#include "lexer.h"
#include "token.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void unrecognized(Lexer *lexer, char character) {
  if (isprint(character)) {
    fprintf(stderr, "Unrecognized character at %d in %s: %c\n", lexer->line,
            lexer->filename, character);
    lexer->had_error = true;
  } else {
    lexer->had_error = true;
  }
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

static Token create_token(Lexer *lexer, TokenType type, char *lexeme) {
  // Adding token to Token_List
  return (Token){type, lexeme};
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
  while (isdigit(peek(lexer, 0)))
    advance(lexer);

  if (peek(lexer, 0) == '.' && isdigit(peek(lexer, 1))) {
    advance(lexer);

    while (isdigit(peek(lexer, 0)))
      advance(lexer);
  }

  return create_token(lexer, T_INT_LITERAL, NULL);
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
      add_token(&lexer->tokens, create_token(lexer, T_PLUS, "+"));
      break;
    case '-':
      add_token(&lexer->tokens, create_token(lexer, T_MINUS, "-"));
      break;
    case '*':
      add_token(&lexer->tokens, create_token(lexer, T_STAR, "*"));
      break;
    case '/':
      add_token(&lexer->tokens, create_token(lexer, T_SLASH, "/"));
      break;
    case ';':
      add_token(&lexer->tokens, create_token(lexer, T_SEMICOLON, ";"));
      break;
    case '.':
      add_token(&lexer->tokens, create_token(lexer, T_DOT, "."));
      break;
    case ',':
      add_token(&lexer->tokens, create_token(lexer, T_COMMA, ","));
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

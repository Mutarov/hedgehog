#include "token.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 5

// INFO: @oneon4i is gay

// WARNING: I'll ban you if you answer "no" on question "Sosal?"

void init_tokenlist(Token_List *tokenlist) {
  tokenlist->tokens = malloc(sizeof(Token) * INITIAL_CAPACITY);
  tokenlist->length = 0;
  tokenlist->capacity = INITIAL_CAPACITY;
}

void add_token(Token_List *list, Token token) {
  if (list->length >= list->capacity) {
    size_t new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
    Token *new_tokens = realloc(list->tokens, new_capacity * sizeof(Token));
    if (!new_tokens) {
      // Handle allocation error
      return;
    }
    list->tokens = new_tokens;
    list->capacity = new_capacity;
  }
  list->tokens[list->length++] = token;
}

void free_token(Token *token) {
  if (token) {
    free(token->lexeme);
  }
}

void free_tokenlist(Token_List *list) {
  if (list && list->tokens) {
    for (size_t i = 0; i < list->length; i++) {
      free_token(&list->tokens[i]);
    }
    free(list->tokens); // Free the array itself
    list->tokens = NULL;
    list->length = 0;
    list->capacity = 0;
  }
}

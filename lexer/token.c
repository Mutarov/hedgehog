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

void add_token(Token_List *tokenlist, Token token) {
  if (tokenlist->length == tokenlist->capacity) {
    tokenlist->capacity *= 2;
    tokenlist->tokens =
        realloc(tokenlist->tokens, sizeof(Token) * tokenlist->capacity);
  }
  tokenlist->tokens[tokenlist->length++] = token;
}

void free_tokenlist(Token_List *tokenlist) {
  free(tokenlist->tokens);
  tokenlist->tokens = NULL;
  tokenlist->length = tokenlist->capacity = 0;
}

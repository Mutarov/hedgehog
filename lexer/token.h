#ifndef token_h
#define token_h
typedef enum {
  T_KEYWORD,     // T_KEYWORD(lexeme: "for")
  T_PLUS,        // +
  T_SLASH,       // /
  T_STAR,        // *
  T_MINUS,       // -
  T_LPAREN,      // (
  T_RPAREN,      // )
  T_LBRACE,      // {
  T_RBRACE,      // }
  T_SEMICOLON,   // ;
  T_COMMA,       // ,
  T_DOT,         // .
  T_IDENTIFIER,  // some_var
  T_STR_LITERAL, // "Sosal?"
  T_INT_LITERAL, // 5
  T_EOF          // End of File
} TokenType;

typedef struct Token {
  TokenType type;
  char *lexeme;
} Token;

typedef struct Token_List {
  Token *tokens;
  int length;
  int capacity;
} Token_List;

// INFO: Functions for Token_List
void init_tokenlist(Token_List *tokenlist);
void add_token(Token_List *tokenlist, Token token);
void free_tokenlist(Token_List *tokenlist);
void free_token(Token *token);
#endif

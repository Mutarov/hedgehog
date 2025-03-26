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
  T_LSBRACE,     // [
  T_RSBRACE,     // ]
  T_SEMICOLON,   // ;
  T_COLON,       // :
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

typedef struct {
  Token *tokens;
  int used;
  int capacity;
} TokenList;

// INFO: Functions for TokenList
void init_tokenlist(TokenList *tokenlist);
void add_token(TokenList *tokenlist, Token token);
void free_tokenlist(TokenList *tokenlist);
void free_token(Token *token);
#endif

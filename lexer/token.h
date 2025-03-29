#ifndef token_h
#define token_h
typedef enum {
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
  T_EOF,         // End of File
  // Keywords
  T_AND,
  T_CLASS,
  T_ELSE,
  T_FALSE,
  T_FOR,
  T_FN,
  T_IF,
  T_NIL,
  T_OR,
  T_PRINT,
  T_RET,
  T_SUPER,
  T_THIS,
  T_TRUE,
  T_LET,
  T_WHILE,
  T_STR,
  T_INT,
  T_BOOL,
  T_EQUAL,
  T_NOT_EQUAL,
  T_GREATER_THAN,
  T_LESS_THAN,
  T_GREATER_THAN_OR_EQUAL,
  T_LESS_THAN_OR_EQUAL,
} TokenType;

typedef struct {
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

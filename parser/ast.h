#include <stdlib.h>

typedef enum {
  PLUS,
  MINUS,
  DIV,
  MUL,
} Oper;

typedef enum {
  BinOp,
  UnaryOp,
  Literal,
} AstNodeType;

typedef enum {
  INT,
} LiteralType;

typedef struct Node {
  AstNodeType type;
  union {
    struct {
      Oper op;
      struct Node *left;
      struct Node *right;
    } binop_node;
    struct {
      LiteralType type;
      union {
        int decimal;
      } data;
    } literal_node;
  } data;
} Node;

typedef struct Node Ast;

// Compiler will be here
//
#include "ast.h"

void free_ast(Ast *node) {
  if (node == NULL) {
    return;
  }

  switch (node->type) {
  case BinOp:
    free_ast(node->data.binop_node.left);
    free_ast(node->data.binop_node.right);
    break;

  case UnaryOp:
    // нехуй делать тут мб потом будет
    break;

  case Literal:
    // Хуй
    break;
  }

  free(node);
}

// Stack implementation for HedgehogVM

#define STACK_SIZE 1024

// Structures
typedef struct {
  int top;
  int used;
  int data[STACK_SIZE]; // Потом вместо int будет Constant
} Stack;

// Functions
void init_stack(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
void free_stack(Stack *stack);

// Stack implementation for HedgehogVM

#define STACK_SIZE 1024

// Structures
typedef struct {
  int top;              // index of stack top
  int used;             // used
  int data[STACK_SIZE]; // data (вам реал нужны какие то обьяснения??)
} Stack;

// Functions
void init_stack(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
void free_stack(Stack *stack);

// Implemetation of stack.h
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// Functions
void push(Stack *s, int x) {
  if (STACK_SIZE == s->top) {
    // Stack overflow
    fprintf(stderr, "VM-Error: stack overflow\n");
    exit(1);
  }

  // if not overflow, push
  s->data[++s->top] = x;
}

int pop(Stack *s) {
  if (s->top == -1 || s->top == 0) {
    // Stack is empty
    fprintf(stderr, "VM-Error: pop from empty stack\n");
    exit(1);
  }

  // if not empty, pop
  return s->data[s->top--];
}

void init_stack(Stack *s) { s->top = -1; }

void free_stack(Stack *s) {
  // free allocated memory
  free(s);
}

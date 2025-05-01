// надо написать книгу как пиздить код професионально
#ifndef chunk_h
#define chunk_h
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode; // SKDG: Whats the difference

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
  int *lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
void freeChunk(Chunk *chunk);
int addConstant(Chunk *chunk, Value value);

#endif

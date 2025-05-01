#ifndef value_h
#define value_h

typedef double Value;

typedef struct {
  int capacity;
  int count;
  Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);

// typedef enum { NONE, NUM, STR, BOOL } ValueType;

// typedef struct {
// ValueType type;
// union val {
// double num;
// char *str;
// bool b;
// };
// } Value;

#endif

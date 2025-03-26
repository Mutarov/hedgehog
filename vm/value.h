#ifndef value_h
#define value_h

typedef enum { NONE, NUM, STR, BOOL } ValueType;

typedef struct {
  ValueType type;
  union val {
    double num;
    char *str;
    bool b;
  };
} Value;

#endif

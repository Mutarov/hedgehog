#include "lexer/lexer.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Check if the filename is provided
  if (argc < 2) {
    printf("usage: %s file\n", argv[0]);
    return 1; // Exit with error code
  }

  // Open the file
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error opening file");
    return 1; // Exit with error code
  }

  // Get file size
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);

  // Allocate memory for the file content
  char *source = malloc(sizeof(char) * (size + 1)); // +1 for null terminator
  if (source == NULL) {
    perror("Error allocating memory");
    fclose(f);
    return 1; // Exit with error code
  }

  // Read file content
  size_t bytes_read = fread(source, sizeof(char), size, f);
  if (bytes_read != size) {
    perror("Error reading file");
    free(source);
    fclose(f);
    return 1; // Exit with error code
  }
  source[size] = '\0'; // Null-terminate the string
  fclose(f);

  // Initialize Lexer
  Lexer lexer;
  init_lexer(&lexer, source, argv[1]);
  lex(&lexer);

  // Print results
  L_INFO("file: %s\n", lexer.filename);
  L_INFO("source: \n%s\n", lexer.source);
  L_INFO("tokens:\n");
  for (int i = 0; i < lexer.tokens.used; i++) {
    printf("\t%d(\"%s\")\n", lexer.tokens.tokens[i].type,
           lexer.tokens.tokens[i].lexeme);
  }

  // Clean up
  free(source);
  free_lexer(&lexer);

  return 0; // Success
}

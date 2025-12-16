#include <stdio.h>

int main(void) {
  const char *start = "ABCABBA";
  const char *end = "CBABAC";

  printf("Generating myers diff for %s and %s\n", start, end);
  return 0;
}

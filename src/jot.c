#include "diff.h"

int main(void) {
  const char *start = "ABCABBA";
  const char *end = "CBABAC";

  myers_diff(start, end);
  return 0;
}

#include "diff.h"
#include <stdio.h>
#include <stddef.h>


int myers_diff(char **start_lines, size_t start_line_count, char **end_lines, size_t end_line_count) {
  size_t i;
  for (i = 0; i < start_line_count; ++i){
    printf("%lu. %s\n", i, start_lines[i]);
  }
  printf("\n\n=========================================================\n\n");
  for (i = 0; i < end_line_count; ++i){
    printf("%lu. %s\n", i, end_lines[i]);
  }

  /* Basic algorithm from Myers diff paper:
   *
   * For D ← 0 to M+N Do
   *  For k ← −D to D in steps of 2 Do
   *    Find the endpoint of the furthest reaching D-path in diagonal k.
   *    If (N,M) is the endpoint Then
   *      The D-path is an optimal solution.
   *      Stop
   */


  return 0;
}

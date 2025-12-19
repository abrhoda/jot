#include "diff.h"
#include <stdio.h>
#include <stddef.h>


int myers_diff(char **start_lines, size_t start_line_count, char **end_lines, size_t end_line_count) {
  size_t max = start_line_count + end_line_count;
  size_t d, k;

  int *d_values = malloc(((max*2)+ 1) * sizeof(int)); /* d can go from [-d, d] */
  int *center = &d_values[max+1];
  int x, y;

  /*
  for (i = 0; i < start_line_count; ++i){
    printf("%lu. %s\n", i, start_lines[i]);
  }
  printf("\n\n=========================================================\n\n");
  for (i = 0; i < end_line_count; ++i){
    printf("%lu. %s\n", i, end_lines[i]);
  }
  */

  /* Basic algorithm from Myers diff paper:
   *
   * For D ← 0 to M+N Do
   *  For k ← −D to D in steps of 2 Do
   *    Find the endpoint of the furthest reaching D-path in diagonal k.
   *    If (N,M) is the endpoint Then
   *      The D-path is an optimal solution.
   *      Stop
   */
  for (d = 0, d <= max; ++d) {
    for (k = -1*d; k <= d; k += 2) {
    }
  }

  return 0;
}

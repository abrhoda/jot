#include "diff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static size_t shortest_edit(char **start_lines, size_t start_lines_count, char **end_lines, size_t end_lines_count) {
  size_t max = start_lines_count + end_lines_count;
  size_t d, k;
  size_t x, y;
  int *v = malloc(((max*2)+ 1) * sizeof(int)); /* v can go from [-d, d] */

  /* because the array is 2*max + 1, the length is always odd and the midpoint is always max + 1 into the array
  int *center = &v[max + 1];
  */

  /*
  for (i = 0; i < start_lines_count; ++i){
    printf("%lu. %s\n", i, start_lines[i]);
  }
  printf("\n\n=========================================================\n\n");
  for (i = 0; i < end_lines_count; ++i){
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
  printf("\n\nFinding shortest edit distance\n\n");
  v[1] = 0; /* is this needed? this might be center + 1 if i am taking center = max + 1 */
  for (d = 0; d <= max; ++d) {
    printf("d = %lu\n", d);
    for (k = -1*d; k <= d; k += 2) {
      /*FIXME wrong because k is size_t and cannot be negative */
      printf("k = %lu\n", k);
      if ((k == -1*d) || (k != d && v[k-1] < v [k+1])) {
        x = v[k+1];
      } else {
        x = v[k-1]+1;
      }
      y = x - k;
      printf("x = %lu\n", x);
      printf("y = %lu\n", y);

       /* FIXME strcmp is fine because we know our strings are properly null terminated. RIGHT? */
      while (x < start_lines_count && y < end_lines_count && strcmp(start_lines[x], end_lines[y]) == 0) {
        printf("taking diag step @ (%lu,%lu)\n", x, y);
        x++;
        y++;
      }
      v[k] = x;
      printf("set v[%lu] = %lu\n", k, x);
      if (x >= start_lines_count && y >= end_lines_count) {
        printf("found shorts amount! returning.\n");
        free(v);
        return d;
      }
    }
  }

  /* NOTE UNREACHABLE */
  printf("UNREACHABLE\n");
  free(v);
  return 0;
}


void myers_diff(char **start_lines, size_t start_lines_count, char **end_lines, size_t end_lines_count) {
  size_t i;
  printf("COMPARING:\n\n");
  for (i = 0; i < start_lines_count; ++i){
    printf("%lu. %s\n", i, start_lines[i]);
  }
  printf("\n\n=========================================================\n\n");
  for (i = 0; i < end_lines_count; ++i){
    printf("%lu. %s\n", i, end_lines[i]);
  }

  i = shortest_edit(start_lines, start_lines_count, end_lines, end_lines_count);
  printf("Achieved in %lu edits\n", i);
  return;
}

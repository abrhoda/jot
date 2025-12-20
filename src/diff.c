#include "diff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static size_t shortest_edit(char **start_lines, size_t start_lines_count, char **end_lines, size_t end_lines_count) {
  /* FIXME unsafe cast of size_t to int */
  int m = start_lines_count;
  int n = end_lines_count;
  int max = m + n;
  int d, k, x, y; 
  int *v = malloc(((max*2)+ 1) * sizeof(int)); /* v can go from [-d, d] */
  int k_centered = max + 1; /* midpoint of v because c doesn't support negative indexing */

  /* default non-0 sentinal value */
  for (k = 0; k < (max*2)+1; ++k) {
    v[k] = -1;
  }
  v[k_centered] = 0;


  /* Basic algorithm from Myers diff paper:
   *
   * For D ← 0 to M+N Do
   *  For k ← −D to D in steps of 2 Do
   *    Find the endpoint of the furthest reaching D-path in diagonal k.
   *    If (N,M) is the endpoint Then
   *      The D-path is an optimal solution.
   *      Stop
   */

  printf("\n\nFinding shortest edit distance: ");

  for (d = 0; d <= max; ++d) {
    /* printf("d = %d\n", d); */

    for (k = -1*d; k <= d; k += 2) {
      k_centered = max + k;

      /*
      printf("k = %d\n", k);
      printf("k_centered = %d\n", k_centered);
      */

      if ((k == -1*d) || (k != d && v[k_centered-1] < v[k_centered+1])) {
        x = v[k_centered+1];
      } else {
        x = v[k_centered-1]+1;
      }
      /* printf("x = %d\n", x); */
      y = x - k;
      /* printf("y = %d\n", y); */

       /* FIXME strcmp is fine because we know our strings are properly null terminated. RIGHT? */
      while (x < m && y < n && strcmp(start_lines[x], end_lines[y]) == 0) {
        /* printf("taking diag step @ (%d,%d)\n", x, y); */
        x++;
        y++;
      }
      v[k_centered] = x;
      /* printf("set v[%d] = %d\n", k, x); */
      if (x >= m && y >= n) {
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

#include "diff.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Basic algorithm from Myers diff paper:
 *
 * For D ← 0 to M+N Do
 *  For k ← −D to D in steps of 2 Do
 *    Find the endpoint of the furthest reaching D-path in diagonal k.
 *    If (N,M) is the endpoint Then
 *      The D-path is an optimal solution.
 *      Stop
 */

/* FIXME this is converting start_lines_count and end_lines_count to ints. they should stay size_t (the correct type) and m, n, max, and d should all be size_t*/
static size_t shortest_edit(char **start_lines, size_t start_lines_count, char **end_lines, size_t end_lines_count) {
  /* variable names follow the naming in the Myers Diff Algorithm paper */
  int m, n, max, d, k, x, y;
  int *v = NULL;

  /* midpoint of v because c doesn't support negative indexing */
  int k_centered;

  /* d = [0, max] where max = start_lines_count + end_lines_count so check that start_lines_count and end_lines_count can be converted to ints */
  if (start_lines_count + end_lines_count > INT_MAX ) {
    fprintf(stderr, "Max difference between lines of files too large.\n");
    return 0;
  }

  if (start_lines_count > (INT_MAX / 2)) {
    fprintf(stderr, "Too many lines in start_lines (%lu). Must be %d or less\n", start_lines_count, INT_MAX/2);
    return 0;
  }

  if (end_lines_count > (INT_MAX / 2)) {
    fprintf(stderr, "Too many lines in end_lines (%lu). Must be %d or less\n", end_lines_count, INT_MAX/2);
    return 0;
  }

  m = start_lines_count;
  n = end_lines_count;
  max = m + n;
  k_centered = max + 1;

  /* v can go from [-d, d] */
  v = malloc(((max*2)+ 1) * sizeof(int));
  if (v == NULL) {
      fprintf(stderr, "Couldn't allocate v buffer\n");
  }

  /* add sentinal values to array */
  for (k = 0; k < (max*2)+1; ++k) {
    v[k] = -1;
  }
  v[k_centered] = 0;

  printf("\n\nFinding shortest edit distance: ");

  for (d = 0; d <= max; ++d) {
    for (k = -1*d; k <= d; k += 2) {
      k_centered = max + k;
      if ((k == -1*d) || (k != d && v[k_centered-1] < v[k_centered+1])) {
        x = v[k_centered+1];
      } else {
        x = v[k_centered-1]+1;
      }
      y = x - k;

       /* FIXME strcmp is fine because we know our strings are properly null terminated. RIGHT? */
      while (x < m && y < n && strcmp(start_lines[x], end_lines[y]) == 0) {
        x++;
        y++;
      }
      v[k_centered] = x;
      if (x >= m && y >= n) {
        free(v);
        return d;
      }
    }
  }

  assert(0 && "Shortest edit script is longer than max.");
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

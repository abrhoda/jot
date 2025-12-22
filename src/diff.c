#include "diff.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Basic algorithm from Myers diff paper:
 *
 * For D ← 0 to M+N Do
 *  For k ← −D to D in steps of 2 Do
 *    Find the endpoint of the furthest reaching D-path in diagonal k.
 *    If (N,M) is the endpoint Then
 *      The D-path is an optimal solution.
 *      Stop
 */
static int shortest_edit(char** start_lines, size_t start_lines_count,
                            char** end_lines, size_t end_lines_count, struct diff *diff) {
  /* NOTE: variable names follow the naming in the Myers Diff Algorithm paper 
   * NOLINTBEGIN(readability-identifier-length)
   */
  int m;
  int n;
  int max;
  int d;
  int k;
  int x;
  int y;
  int* v = NULL;
  /* NOLINTEND(readability-identifier-length)*/

  /* midpoint of v because c doesn't support negative indexing */
  int k_centered;

  /* FIXME this is kind of dirty but this ensures that converting start/end
   * lines to int isn't actually a narrowing op. This conversion should be avoided.
   *
   * d = [0, max] where max = start_lines_count + end_lines_count so check that
   * start_lines_count and end_lines_count can be converted to ints */
  if (start_lines_count + end_lines_count > INT_MAX) {
    fprintf(stderr, "Max difference between lines of files too large.\n");
    return DIFF_EC_FILES_TOO_LARGE;
  }

  m = (int) start_lines_count;
  n = (int) end_lines_count;
  max = m + n;
  k_centered = max + 1;

  /* v can go from [-d, d] */
  v = malloc(((max * 2) + 1) * sizeof(int));
  if (v == NULL) {
    fprintf(stderr, "Couldn't allocate v buffer\n");
    return DIFF_EC_OOM;
  }

  /* add sentinal values to array */
  for (k = 0; k < (max * 2) + 1; ++k) {
    v[k] = -1;
  }
  v[k_centered] = 0;

  printf("\n\nFinding shortest edit distance: ");

  for (d = 0; d <= max; ++d) {
    for (k = -1 * d; k <= d; k += 2) {
      k_centered = max + k;
      if ((k == -1 * d) || (k != d && v[k_centered - 1] < v[k_centered + 1])) {
        x = v[k_centered + 1];
      } else {
        x = v[k_centered - 1] + 1;
      }
      y = x - k;

      /* FIXME strcmp is fine because we know our strings are properly null
       * terminated. RIGHT? */
      while (x < m && y < n && strcmp(start_lines[x], end_lines[y]) == 0) {
        x++;
        y++;
      }
      v[k_centered] = x;
      if (x >= m && y >= n) {
        free(v);
        diff->trace_length = d;
        return DIFF_EC_SUCCESS;
      }
    }
  }

  assert(0 && "Shortest edit script is longer than max.");
  free(v);
  return DIFF_EC_UNREACHABLE;
}

void free_diff(struct diff *diff) {
  size_t count = 0;
  if (diff == NULL) {
    return;
  }
  for (count = 0; count < diff->lines_length; ++count) {
    free(diff->lines[count]);
  }

  for (count = 0; count < diff->trace_length; ++count) {
    free(diff->trace[count]);
  }

  free(diff->lines);
}

enum diff_exit_code myers_diff(char** start_lines, size_t start_lines_count, char** end_lines,
                size_t end_lines_count, struct diff *diff) {
  size_t count;
  enum diff_exit_code diff_exit_code;
  printf("COMPARING:\n\n");
  for (count = 0; count < start_lines_count; ++count) {
    printf("%lu. %s\n", count, start_lines[count]);
  }
  printf("\n\n=========================================================\n\n");
  for (count = 0; count < end_lines_count; ++count) {
    printf("%lu. %s\n", count, end_lines[count]);
  }

  diff_exit_code = shortest_edit(start_lines, start_lines_count, end_lines, end_lines_count, diff);
  printf("Achieved in %lu edits\n", diff->trace_length);
  return diff_exit_code;
}

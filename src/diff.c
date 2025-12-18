#include "diff.h"
#include <stdio.h>
#include <stddef.h>

/*
 * @param start_lines The array of strings that are the lines of the start file
 * @param start_line_count The length of the start array
 * @param end_lines The array of strings that are the lines of the end file
 * @param end_line_count The length of the end array
 *
 * @return 0 for success, non-0 for failure.
 */
int myers_diff(char **start_lines, size_t start_line_count, char **end_lines, size_t end_line_count) {
  size_t i;
  for (i = 0; i < start_line_count; ++i){
    printf("%lu. %s\n", i, start_lines[i]);
  }
  printf("\n\n=========================================================\n\n");
  for (i = 0; i < end_line_count; ++i){
    printf("%lu. %s\n", i, end_lines[i]);
  }
  /*
  size_t max, current_start_line, current_end_line;
  int k, d;
*/

  /* max amount of lines in the resulting diff. This would be if end was completely different than start. 
   * NOTE: don't expect an overflow from adding the line counts but if this is applied to non-text files, this is a risk and uint64_t might be better. */

  /*
  max = line_count_start + line_count_end;
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

  /*
  for (k = 0; k <= max, ++k) {
    for(d = -1*k; d <= k; d += 2) {
      printf("k = %d, d = %d\n",k , d);
    }
  }
  */
  return 0;
}

#ifndef DIFF_H
#define DIFF_H
#include <stddef.h>

enum diff_exit_code {
  DIFF_EC_SUCCESS = 0,
  DIFF_EC_FILES_TOO_LARGE = -1,
  DIFF_EC_OOM = -2,
  DIFF_EC_UNREACHABLE = -3
};

struct trace_point {
  int k;
  int d;
};

struct diff {
  size_t lines_length;
  char** lines;
  struct trace_point **trace;
  size_t trace_length;
};

void free_diff(struct diff *diff);


/*
 * @param start_lines The array of strings that are the lines of the start file
 * @param start_lines_count The length of the start array
 * @param end_lines The array of strings that are the lines of the end file
 * @param end_lines_count The length of the end array
 * @param diff Struct to hold the final diff lines and trace points.
 *
 * @return diff_exit_code value.
 */
enum diff_exit_code myers_diff(char** start_lines, size_t start_lines_count, char** end_lines,
                size_t end_lines_count, struct diff *diff);

#endif

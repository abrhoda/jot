#ifndef DIFF_H
#define DIFF_H
#include <stddef.h>

enum diff_exit_code {
  DIFF_EC_SUCCESS = 0,
  DIFF_EC_FILES_TOO_LARGE = -1,
  DIFF_EC_OOM = -2,
  DIFF_EC_UNREACHABLE = -3
};

struct diff_result {
  void *buffer;
  size_t buffer_length;
  enum diff_exit_code exit_code;
};

void free_diff_result_buffer(struct diff_result *diff_result);

/*
 * @param start_lines The array of strings that are the lines of the start file
 * @param start_lines_count The length of the start array
 * @param end_lines The array of strings that are the lines of the end file
 * @param end_lines_count The length of the end array
 *
 * @return the smallest number of edits required to be applied to start_lines to
arrive at end_lines size_t shortest_edit(char **start_lines, size_t
start_lines_count, char **end_lines, size_t end_lines_count);
 */
/*
 * @param start_lines The array of strings that are the lines of the start file
 * @param start_lines_count The length of the start array
 * @param end_lines The array of strings that are the lines of the end file
 * @param end_lines_count The length of the end array
 *
 * @return diff_exit_code value.
 */
struct diff_result myers_diff(char** start_lines, size_t start_lines_count, char** end_lines,
                size_t end_lines_count);

#endif

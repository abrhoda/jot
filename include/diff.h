#ifndef JOT_DIFF_H
#define JOT_DIFF_H
#include <stddef.h>


struct graph_node {
  struct graph_node *left;
  struct graph_node *right;
};

struct graph {
  struct graph_node *root;
};

/*
 * @param start_lines The array of strings that are the lines of the start file
 * @param start_lines_count The length of the start array
 * @param end_lines The array of strings that are the lines of the end file
 * @param end_lines_count The length of the end array
 *
 * @return the smallest number of edits required to be applied to start_lines to arrive at end_lines
size_t shortest_edit(char **start_lines, size_t start_lines_count, char **end_lines, size_t end_lines_count);
 */
/*
 * @param start_lines The array of strings that are the lines of the start file
 * @param start_lines_count The length of the start array
 * @param end_lines The array of strings that are the lines of the end file
 * @param end_lines_count The length of the end array
 *
 * @return 0 for success, non-0 for failure.
 */
void myers_diff(char **start_lines, size_t start_lines_count, char **end_lines, size_t end_lines_count);

#endif

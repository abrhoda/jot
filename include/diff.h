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

int myers_diff(char **start_lines, size_t start_line_count, char **end_lines, size_t end_line_count);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "diff.h"
#include "file.h"

int main(int argc, char **argv) {
  const char *usage = "jot - a diffing and version tool\n\tUsage: jot <file1> <file2>\n";
  struct file fstart, fend;
  int result = 0;

  if (argc != 3) {
    fprintf(stderr, "Must provide 2 file names as command line arguments.\n");
    fprintf(stderr, "%s", usage);
    exit(EXIT_FAILURE);
  }

  printf("diffing <%s> and <%s>\n", argv[1], argv[2]);

  result = write_file_lines_to_file(argv[1], &fstart);
  result = write_file_lines_to_file(argv[2], &fend);

  myers_diff(fstart.lines, fstart.line_count, fend.lines, fend.line_count);

  free_file(&fstart);
  free_file(&fend);
  return result;
}

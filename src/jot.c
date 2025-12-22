#include <stdio.h>

#include "diff.h"
#include "file.h"

int main(int argc, char** argv) {
  const char* usage =
      "jot - a diffing and version tool\n\tUsage: jot <file1> <file2>\n";
  struct file fstart;
  struct file fend;
  /* TODO make a diff struct instead and pass it in by ref to the myers_diff function and return the result */
  struct diff_result diff_result;
  int result = 0;

  if (argc != 3) {
    fprintf(stderr, "Must provide 2 file names as command line arguments.\n");
    fprintf(stderr, "%s", usage);
    return 1;
  }

  printf("diffing <%s> and <%s>\n", argv[1], argv[2]);

  result = write_file_lines_to_file(argv[1], &fstart);
  result = write_file_lines_to_file(argv[2], &fend);

  diff_result = myers_diff(fstart.lines, fstart.line_count,
                          fend.lines, fend.line_count);

  free_file_lines(&fstart);
  free_file_lines(&fend);
  free_diff_result_buffer(&diff_result);
  return diff_result.exit_code;
}

#include <stdio.h>

#include "diff.h"
#include "file.h"

int main(int argc, char** argv) {
  const char* usage =
      "jot - a diffing and version tool\n\tUsage: jot <file1> <file2>\n";
  struct file fstart;
  struct file fend;
  struct diff diff;
  
  enum file_exit_code file_ec;
  enum diff_exit_code diff_ec;

  int result = 0;

  if (argc != 3) {
    fprintf(stderr, "Must provide 2 file names as command line arguments.\n");
    fprintf(stderr, "%s", usage);
    return 1;
  }

  printf("diffing <%s> and <%s>\n", argv[1], argv[2]);

  file_ec = write_file_lines_to_file(argv[1], &fstart);
  if (file_ec != 0) {
    result = file_ec;
    goto cleanup;
  }
  file_ec = write_file_lines_to_file(argv[2], &fend);
  if (file_ec != 0) {
    result = file_ec;
    goto cleanup;
  }
  diff_ec = myers_diff(fstart.lines, fstart.line_count,
                          fend.lines, fend.line_count, &diff);
  if (diff_ec != 0) {
    result = diff_ec;
    goto cleanup;
  }

cleanup:
  free_file_fields(&fstart);
  free_file_fields(&fend);
  free_diff(&diff);
  return result;
}

#include "file.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

/*
 * FIXME: the file that filename points to must not be empty
 */
enum file_exit_code write_file_lines_to_file(const char* filename,
                                              struct file* file) {
  char buffer[BUFFER_SIZE];
  char** temp_lines = NULL;

  /* initial amount of lines. Will realloc anyway */
  size_t initial_size = INITIAL_LINE_SIZE;
  size_t current_lines_size = initial_size;
  size_t line_count = 0;
  size_t line_len;

  FILE* f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open %s file: %s\n", filename, strerror(errno));
    return FILE_EC_CANNOT_OPEN;
  }

  file->lines = malloc(initial_size * sizeof(char*));
  if (file->lines == NULL) {
    fprintf(stderr, "Error allocating for initial buffer\n");
    fclose(f);
    return FILE_EC_OUT_OF_MEMORY;
  }
  file->name = filename;

  /* check if line_len == 200 && buffer[line_len] != '\0' because it was an
   * overflow */
  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    line_len = strlen(buffer);
    /*
     * Swapping newline for null term
     *
     * TODO how does this handle lines that are just '\n'??
     *
     */
    if (line_len > 0 && buffer[line_len - 1] == '\n') {
      buffer[line_len - 1] = '\0';
    }

    file->lines[line_count] = malloc((line_len + 1) * sizeof(char));
    if (file->lines[line_count] == NULL) {
      /* free all previously parsed strings */
      fprintf(stderr, "Error allocating line at %ld\n", line_count);
      free_file_lines(file);
      fclose(f);
      return FILE_EC_OUT_OF_MEMORY;
    }

    /* FIXME: used memcpy because we know buffer and the line hold the same
     * amount of chars and is correctly '\0' terminated. stncpy wasn't happy
     * because, even though we have line_len and know that the destination can
     * hold exactly line_len chars (null term already persent), strncpy kept
     * warning about trunction happening from source buffer. memcpy works and is
     * portable.
     *
     * strcpy and strncpy deemed bad quality. So memcpy works and is portable.
     * */
    memcpy(file->lines[line_count], buffer, line_len);
    ++line_count;

    /* check if we are at the end of the allocation **lines region. if so,
     * double size. No worries because this is temp. we will shrink with realloc
     * at the end.
     *
     * TODO more intelligently do this. There is a chance we double the size of
     * `lines` at the end of the file if it all lines up prefectly.
     * */
    if (line_count == current_lines_size) {
      current_lines_size = current_lines_size * 2;
      temp_lines = realloc(file->lines, current_lines_size * sizeof(char*));
      if (temp_lines == NULL) {
        /* free all previously parsed strings */
        fprintf(stderr, "Error reallocating lines\n");
        free_file_lines(file);
        fclose(f);
        return FILE_EC_OUT_OF_MEMORY;
      }
      file->lines = temp_lines;
    }
  }
  file->line_count = line_count;

  /* making sure we shrink lines to actually used ammount. */
  if (line_count > 0) {
    temp_lines = realloc(file->lines, line_count * sizeof(char*));
    if (temp_lines != NULL) {
      file->lines = temp_lines;
    }
  } else {
    /* realistically, line will be null already here so this is slightly
     * frivolous */
    free(file);
    file = NULL;
    fprintf(stderr, "Not lines found in file %s\n", filename);
    return FILE_EC_EMPTY_FILE;
  }

  fclose(f);
  return FILE_EC_SUCCESS;
}

void free_file_lines(struct file* file) {
  size_t len = 0;
  if (file == NULL || file->lines == NULL) {
    return;
  }

  while (len < file->line_count) {
    free(file->lines[len]);
    ++len;
  }
  free(file->lines);
}

#ifndef FILE_H
#define FILE_H

#include <stdio.h>

enum {
  INITIAL_LINE_SIZE = 100,
  BUFFER_SIZE = 1024
};

enum file_exit_code {
  FILE_EC_SUCCESS = 0,
  FILE_EC_OUT_OF_MEMORY, /* FIXME this should be in a globale error enum */
  FILE_EC_CANNOT_OPEN,
  FILE_EC_EMPTY_FILE
};

struct file {
  const char* name;
  size_t line_count;
  char** lines;
};

/*
 * @brief frees the lines in the file struct. Does NOT free the file struct itself.
 *
 * @param file Struct to have fields freed.
 */
void free_file_fields(struct file* file);

/*
 * @brief frees the lines in the file struct before freeing the file struct itself.
 * The file struct pointer will be set to NULL at the end of this function.
 *
 *
 * @param file Struct to be freed.
 */
void free_file(struct file* file);

/*
 * @brief reads entire file into the provided file stuct.
 *
 * @detail
 *
 * @param filename Name of the file that will be read into the buffer
 * @param file Destination file struct container to hold file lines.
 *
 * @return 0 for success, non-0 for error
 */
enum file_exit_code write_file_lines_to_file(const char* filename,
                                              struct file* file);

#endif

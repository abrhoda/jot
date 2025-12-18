#ifndef JOT_FILE_H
#define JOT_FILE_H

#include <stdio.h>

/* NOTE: any line over 1024 bytes is a bannable offense */
#define BUFFER_SIZE 1024

enum file_error_code {
  FILE_EC_SUCCESS = 0,
  FILE_EC_OUT_OF_MEMORY, /* FIXME this should be in a globale error enum */
  FILE_EC_CANNOT_OPEN,
  FILE_EC_EMPTY_FILE
};

struct file {
  const char *name;
  size_t line_count;
  char **lines;
};
/*
 * @brief frees the entire file struct
 *
 * @param file The file struct to free. Will be set to NULL at the end of this function.
 */
void free_file(struct file *file);



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
enum file_error_code write_file_lines_to_file(const char *filename, struct file *file);



#endif

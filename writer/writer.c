/*
 * writer.c
 *
 * writes a test file for gb
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "../rom.h"

int main(int argc, char **argv)
{
  char *filename;
  FILE *file;

  char *test =
  // LD A 12|LD B 8 |ADD A B|
  "\x3E\x0C\x06\x08\x80";

  // arg checking
  if (argc != 2) {
    fprintf(stderr, "incorrect use of writer\n");
    fprintf(stderr, "usage: writer <filename>\n");
    exit(1);
  }

  // set filename
  filename = argv[1];

  // open file
  if ((file = fopen(filename, "r+")) == NULL) {
    perror("fopen");
    exit(1);
  }   
  
  // seek to program start
  if (fseek(file, 0x0150, SEEK_SET) == -1) {
    perror("fseek");
    fclose(file);
    exit(1);
  }

  // write test to file 
  errno = 0;
  fwrite(test, 1, 5, file); 
  if (errno != 0) {
    perror("fread");
    fclose(file);
    exit(1);
  }

  printf("write success\n");

  fclose(file);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "jdisk.h"

void usage(char *s)
{
  fprintf(stderr, "usage: jdisk_test CREATE disk-file size\n");
  fprintf(stderr, "       jdisk_test W disk-file string|hex       seek_ptr string\n");
  fprintf(stderr, "       jdisk_test R disk-file string|hex|bytes seek_ptr nbytes\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  int rw;
  int sh;
  unsigned long nb;
  unsigned long sp;
  long size;
  unsigned int i, lba, offset, bytes, j;
  unsigned char *buf, c;
  void *jd;
  unsigned char read_buf[JDISK_SECTOR_SIZE+1];

  if (argc != 6 && argc != 4) usage(NULL);
  if (argc == 4) {
    if (strcmp(argv[1], "CREATE") != 0) usage(NULL);
    if (sscanf(argv[3], "%ld", &size) == 0) usage((char *) "Size must be an integer.\n");
    if (size % JDISK_SECTOR_SIZE != 0) usage((char *) "Size must be a multiple of the sector size.\n");
    jd = jdisk_create(argv[2], size);
    if (jd == NULL) {
      fprintf(stderr, "jdisk_create failed -- here's perror:\n");
      perror("");
      exit(1);
    }
    exit(0);
  }
  if (strlen(argv[1]) != 1) usage((char *) "Bad R|W");
  rw = argv[1][0];
  if (rw != 'R' && rw != 'W') usage((char *) "Bad R|W");
  if (strcmp(argv[3], "string") == 0) {
    sh = 'S';
  } else if (strcmp(argv[3], "hex") == 0) {
    sh = 'H';
  } else if (rw == 'R' && strcmp(argv[3], "bytes") == 0) {
    sh = 'B';
  } else usage ((char *) "Bad string|hex|bytes");
  
  jd = jdisk_attach(argv[2]);
  if (jd == NULL) usage((char *) "disk doesn't exist");

  if (sscanf(argv[4], "%ld", &sp) == 0 || sp > jdisk_size(jd)) usage((char *) "Bad seek pointer");

  if (rw == 'R') {
    nb = atoi(argv[5]);
    if (nb <= 0) usage((char *) "Bad nbytes.");
  } else {
    nb = strlen(argv[5]);
    if (sh == 'H') {
      if (nb % 2 == 1) usage((char *) "Hex string has to have an even number of characters");
      nb /= 2;
    }
  }
  if (sp+nb > jdisk_size(jd)) usage((char *) "Seek_ptr + nbytes is too big.");

  if (rw == 'R') {
    buf = (unsigned char *) malloc(nb);
  } else if (sh == 'S') {
    buf = (unsigned char *) argv[5];
  } else {
    buf = (unsigned char *) malloc(nb);
    for (i = 0; i < nb*2; i++) {
      if (argv[5][i] >= '0' && argv[5][i] <= '9') {
        c = argv[5][i] - '0';
      } else if (argv[5][i] >= 'a' && argv[5][i] <= 'f') {
        c = argv[5][i] - 'a' + 10;
      } else if (argv[5][i] >= 'A' && argv[5][i] <= 'F') {
        c = argv[5][i] - 'A' + 10;
      } else {
        usage((char *) "Non hex character in hex string\n");
      }
      if (i % 2 == 0) {
        buf[i/2] = (c << 4);
      } else {
        buf[i/2] |= (c);
      }
    }
  }

  if (rw == 'W') {
    i = 0;
    while (i < nb) {
      lba = (sp + i) / JDISK_SECTOR_SIZE;
      offset = (sp + i) % JDISK_SECTOR_SIZE;  
      bytes = nb - i;
      if (offset + bytes > JDISK_SECTOR_SIZE) {
        bytes = JDISK_SECTOR_SIZE - offset;
      }
      if (offset == 0 && bytes == JDISK_SECTOR_SIZE) {
        jdisk_write(jd, lba, buf+i);
      } else {
        jdisk_read(jd, lba, read_buf);
        memcpy(read_buf + offset, buf+i, bytes);
        jdisk_write(jd, lba, read_buf);
      }
      i += bytes;
    }
  } else {
    i = 0;
    while (i < nb) {
      lba = (sp + i) / JDISK_SECTOR_SIZE;
      offset = (sp + i) % JDISK_SECTOR_SIZE;  
      bytes = nb - i;
      if (offset + bytes > JDISK_SECTOR_SIZE) {
        bytes = JDISK_SECTOR_SIZE - offset;
      }
      jdisk_read(jd, lba, read_buf);
      if (sh == 'S') {
        read_buf[offset+bytes] = '\0';
        printf("%s", read_buf+offset);
      } else if (sh == 'B') {
        fwrite(read_buf+offset, 1, bytes, stdout);
      } else {
        for (j = 0; j < bytes; j++) {
          if (i + j != 0) {
            if ((i + j) % 16 == 0) { 
              printf("\n");
            } else if ((i + j) % 4 == 0) {
              printf("    ");
            }
          }
          printf(" %02x", read_buf[offset+j]);
        }
      }
      i += bytes;
    }
    if (sh != 'B') printf("\n");
    fflush(stdout);
  }
  exit(0);
}

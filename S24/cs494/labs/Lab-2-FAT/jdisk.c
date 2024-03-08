#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "jdisk.h"

typedef struct {
  unsigned long size;  
  int fd;
  char *fn;
  int reads;
  int writes;
} Disk;

void *jdisk_create(char *fn, unsigned long size)
{
  int fd;
  Disk *d;
  char buf[JDISK_SECTOR_SIZE];
  long i;
  
  if (size <= 0 || size % JDISK_SECTOR_SIZE != 0) return NULL;
  if (size / JDISK_SECTOR_SIZE > 0xffffffff) return NULL;

  fd = open(fn, O_RDWR | O_CREAT | O_EXCL, 0666);
  if (fd < 0) return NULL;

  for (i = 0; i < size; i += JDISK_SECTOR_SIZE) {
    write(fd, buf, JDISK_SECTOR_SIZE);
  }
  
  d = (Disk *) malloc(sizeof(Disk));
  d->size = size;
  d->fd = fd;
  d->fn = strdup(fn);
  d->reads = 0;
  d->writes = 0;
  return (void *) d;
}

void *jdisk_attach(char *fn)
{
  int fd;
  Disk *d;
  off_t zero;

  zero = 0;

  fd = open(fn, O_RDWR);
  if (fd < 0) return NULL;

  d = (Disk *) malloc(sizeof(Disk));
  d->fd = fd;
  d->fn = strdup(fn);
  d->size = lseek(fd, zero, SEEK_END);
  d->reads = 0;
  d->writes = 0;
  if (d->size % JDISK_SECTOR_SIZE != 0) {
    fprintf(stderr, "jdisk_attach: Disk size needs to be a multiple of %d\n",
       JDISK_SECTOR_SIZE);
    exit(1);
  }
  return (void *) d;
}

int jdisk_unattach(void *vd)
{
  Disk *d;

  d = (Disk *) vd;
  free(d->fn);
  if (close(d->fd) != 0) return -1;
  return 0;
}

unsigned long jdisk_size(void *vd)
{
  Disk *d;

  d = (Disk *) vd;
  return d->size;
}

int jdisk_read(void *jd, unsigned int lba, void *buf)
{
  Disk *d;

  d = (Disk *) jd;

  if (lba >= (d->size / JDISK_SECTOR_SIZE)) return -2;
  lseek(d->fd, lba * JDISK_SECTOR_SIZE, SEEK_SET);
  usleep(JDISK_DELAY);
  if (read(d->fd, buf, JDISK_SECTOR_SIZE) != JDISK_SECTOR_SIZE) return -1;
  d->reads++;
  return 0;
}

int jdisk_write(void *jd, unsigned int lba, void *buf)
{
  Disk *d;

  d = (Disk *)jd;
  if (lba >= (d->size / JDISK_SECTOR_SIZE)) return -2;
  lseek(d->fd, lba * JDISK_SECTOR_SIZE, SEEK_SET);
  usleep(JDISK_DELAY);
  if (write(d->fd, buf, JDISK_SECTOR_SIZE) != JDISK_SECTOR_SIZE) return -1;
  d->writes++;
  return 0;
}

long jdisk_reads(void *jd)
{
  Disk *d;

  d = (Disk *)jd;
  return d->reads;
}


long jdisk_writes(void *jd)
{
  Disk *d;

  d = (Disk *)jd;
  return d->writes;
}


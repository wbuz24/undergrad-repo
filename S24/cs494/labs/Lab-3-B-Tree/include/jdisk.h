#ifndef _JDISK_
#define _JDISK_

#define JDISK_SECTOR_SIZE (1024)
#define JDISK_DELAY (1)

void *jdisk_create(char *fn, unsigned long size);
void *jdisk_attach(char *fn);
int jdisk_unattach(void *jd);

int jdisk_read(void *jd, unsigned int lba, void *buf);
int jdisk_write(void *jd, unsigned int lba, void *buf);

unsigned long jdisk_size(void *jd);
long jdisk_reads(void *jd);
long jdisk_writes(void *jd);

#endif

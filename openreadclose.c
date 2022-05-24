#ifndef EMBEDDED
#define _FILE_OFFSET_BITS 64
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#endif

int openreadclose(char *fn, char **buf, size_t *len) {
  int fd=open(fn,O_RDONLY);
  if (fd<0) return -1;
  if (!*buf) {
    off_t o = lseek(fd, 0, SEEK_END);
    if (o < 0 || o > 0x7fffffff) goto error;	// impose sanity limits
    *len = o;
    *buf=(char*)malloc(*len+1);
    if (!*buf) {
error:
      close(fd);
      return -1;
    }
  }
  *len=pread(fd,*buf,*len,0);
  if (*len == (unsigned long)-1)
    (*buf)[0]=0;
  else
    (*buf)[*len]=0;
  return close(fd);
}

#include <fcntl.h>
#include <unistd.h>
#include <write12.h>
#include <stdlib.h>

void opendevconsole() {
  int fd;
  if ((fd=open("/dev/console",O_RDWR|O_NOCTTY))>=0) {
    if (dup2(fd,0) != 0 ||
	dup2(fd,1) != 1 ||
	dup2(fd,2) != 2) {
      __write2("dup2 failed unexpectedly.\n");
      exit(111);
    }
    if (fd>2) close(fd);
  }
}

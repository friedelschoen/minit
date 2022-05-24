#include <stdlib.h>

/* split buf into n strings that are separated by c.  return n as *len.
 * Allocate plus more slots and leave the first ofs of them alone. */
char **split(char *buf,int c,size_t* len,size_t plus,size_t ofs) {
  int n=1;
  char **v=0;
  char **w;
  /* step 1: count tokens */
  char *s;
  for (s=buf; *s; s++) if (*s==c) n++;
  /* step 2: allocate space for pointers */
  v=(char **)malloc((n+plus)*sizeof(char*));
  if (!v) return 0;
  w=v+ofs;
  *w++=buf;
  for (s=buf; ; s++) {
    while (*s && *s!=c) s++;
    if (*s==0) break;
    if (*s==c) {
      *s=0;
      *w++=s+1;
    }
  }
  *len=w-v;
  return v;
}

#ifdef UNITTEST
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main() {
  char inp[]="foo\nbar\nbaz";
  size_t len;
  char** x=split(inp, '\n', &len, 2, 1);
  assert(len==4 && !strcmp(x[1],"foo") && !strcmp(x[2],"bar") && !strcmp(x[3],"baz") && x[4]==NULL);
  free(x);
  char inp2[]="fnord";
  x=split(inp2, '\n', &len, 2, 1);
  assert(len==2 && !strcmp(x[1],"fnord") && x[2]==NULL);
  return 0;
}
#endif

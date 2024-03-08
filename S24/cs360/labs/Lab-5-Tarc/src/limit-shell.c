#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/resource.h>

int main(int argc, char **argv)
{
  int i;
  struct rlimit l;

  if (argc != 2) {
    fprintf(stderr, "usage: limit-shell command - executes command in a subshell limited to 10 open file descriptors\n");
    exit(1);
  }

  i = getrlimit(RLIMIT_NOFILE, &l);
  l.rlim_cur = 10;
  l.rlim_max = 10;
  i = setrlimit(RLIMIT_NOFILE, &l);

  system(argv[1]);
  exit(0);
}

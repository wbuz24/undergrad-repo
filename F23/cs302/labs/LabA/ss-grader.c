#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "fields.h"

int main(int argc, char **argv)
{
  long t0;
  int l, pathlength, ifd, ofd, dummy, pid1, pid2, yourpathlength;
  char *command;
  IS is;

  if (argc != 5) {
    fprintf(stderr, "usage: ss-grader my-spellseeker your-spellseeker spellchecker inputfile\n");
    exit(1);
  }

  l = strlen(argv[1]) + strlen(argv[2]) + strlen(argv[3]) + strlen(argv[4]) + 100;
  t0 = time(0);
  command = (char *) malloc(sizeof(char)*l);
 
  sprintf(command, "%s < %s | %s", argv[1], argv[4], argv[3]);
  is = pipe_inputstruct(command);
  if (get_line(is) != 5 || strcmp(is->fields[0], "OK") != 0) {
    fprintf(stderr, "%s is not a valid input file\n", argv[4]);
    exit(1);
  }
  pathlength = atoi(is->fields[4]);
  jettison_inputstruct(is);

  t0 = time(0) - t0;

  pid1 = fork();
  if (pid1 == 0) {
    ifd = open(argv[4], O_RDONLY);
    dup2(ifd, 0);
    close(ifd);
    ofd = open("your-output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    dup2(ifd, 1);
    close(ofd);
    execl(argv[2], argv[2], NULL);
    exit(1);
  }
  sprintf(command, "%d", t0+1);
  pid2 = fork();
  if (pid2 == 0) {
    execlp("sleep", "sleep", command, NULL);
    exit(1);
  }

  l = wait(&dummy);
  if (l == pid1) {
    sprintf(command, "%s < your-output.txt", argv[3]);
    is = pipe_inputstruct(command);
    if (get_line(is) != 5 || strcmp(is->fields[0], "OK") != 0) {
      printf("Spellchecker did not work on your file: \n\n");
      system(command);
      exit(1);
    }
    yourpathlength = atoi(is->fields[4]);
    if (pathlength == yourpathlength) {
      printf("OK\n");
    } else if (yourpathlength > pathlength) {
      printf("You got a better pathlength than Dr. Plank -- tell him.\n");
    } else {
      printf("Your pathlength is not long enough.\nThe maximum path length is %d.\n", pathlength);
      printf("Yours is %d.\n", yourpathlength);
    }
  } else {
    printf("Sleep Done First\n");
    kill(pid1, SIGKILL);
  }
} 

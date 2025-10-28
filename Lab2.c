#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main () {
  pid_t pid = 0;
  int status;
  const int childNum = 10;

  // list of commands to use
  char *commands[][3] = {
    {"ls", "-l", NULL},
    {"echo", "Hello Sean", NULL},
    {"date", NULL, NULL},
    {"ps", NULL, NULL},
    {"pwd", NULL, NULL},
    {"mkdir", "directory 1", NULL},
    {"whoami", NULL, NULL},
    {"ps", "-ef", NULL},
    {"touch", "file 3", NULL},
    {"man", "ls", NULL}
  };
  
  printf("Parent: %d\n", getpid());
  // spawn processes based on childNum
  for (int a = 0; a < childNum; a++) {
    pid = fork();
    if (pid < 0) {
      // check for error
      perror("Failed to fork");
      exit(EXIT_FAILURE);
    }
    else if (pid == 0){
      // if valid child, run one of the commands from the command list.
      printf("Process ID: %d\t Running: %s\n", getpid(), commands[a][0]);
      execvp(commands[a][0], commands[a]);

      // check for error
      perror("exec failure on process %d", getpid());
      exit(EXIT_FAILURE);
    }
  }

  // wait for children to finish.
  while ((pid = wait(&status)) > 0) {
    printf("Process ID %d finished\n", pid);
  }
  return EXIT_SUCCESS;
}

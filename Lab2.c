#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main () {
  pid_t pid = 0;
  int status;
  const int childNum = 10;
  
  char *commands[][3] = {
    {"ls", "-l", NULL},
    {"echo", "Hello Sean", NULL},
    {"date", NULL, NULL},
    {"ps", NULL, NULL},
    {"echo", "Hows your day?"},
    {"echo", "Message 2", NULL},
    {"echo", "Message 3", NULL},
    {"echo", "Message 4", NULL},
    {"echo", "Message 5", NULL},
    {"echo", "Message 6", NULL}
  };
  
  printf("Parent: %d\n", getpid());
  for (int a = 0; a < childNum; a++) {
    pid = fork();
    if (pid < 0) {
      perror("Failed to fork");
      exit(EXIT_FAILURE);
    }
    else if (pid == 0){
      printf("Process ID: %d\t Running: %s\n", getpid(), commands[a][0]);
      execvp(commands[a][0], commands[a]);
      perror("exec failure on process %d", getpid());
      exit(EXIT_FAILURE);
    }
  }
  
  while ((pid = wait(&status)) > 0) {
    printf("Process ID %d finished\n", pid);
  }
  return EXIT_SUCCESS;
}


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum){printf("\nouch!\n");}


int main() {
  int r;
  signal(SIGINT,handler);
  sleep(10);
  return 0;
}

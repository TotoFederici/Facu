#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void handler(int signum){
  
}



int main(){
  void (*signalreturn)(int);

  signalreturn=signal(SIGINT,SIG_IGN);

  sleep(10);

  return 0;
}
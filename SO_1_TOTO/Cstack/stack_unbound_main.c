#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "cstack.h"
#include "stack_unbound.h"

// gcc stack_unbound_main.c stack_unbound.c -o stack_unbound

// Ejecutar (para mostrar el race condition):
// while true; do ./stack_unbound; done

cstack* stack = NULL;

pthread_mutex_t mutex_stack = PTHREAD_MUTEX_INITIALIZER;

void *function1( ) {
  
  for(int i = 0; i < 1000; ++i)
  {
    //pthread_mutex_lock(&mutex_stack);
    c_push(&stack, i);
    //pthread_mutex_unlock(&mutex_stack);
  }

}

void *function2( ) {
  
  for(int i = 0; i < 1000; ++i)
  {
    //pthread_mutex_lock(&mutex_stack);
    c_push(&stack, i);
    //pthread_mutex_unlock(&mutex_stack);
  }

}


int main()
{
  stack = c_create();
  pthread_t one, two; 
  pthread_create(&one, NULL, function1, NULL);  // create thread
  pthread_create(&two, NULL, function2, NULL);

  pthread_join(one, NULL);
  pthread_join(two, NULL);

  int  counter = 0;

  while(!c_isEmpty(stack))
  {
    counter++;
    c_pop(&stack);
  }

  printf("counter final: %d\n", counter);

  c_stackFree(stack);
 
  return 0;
}
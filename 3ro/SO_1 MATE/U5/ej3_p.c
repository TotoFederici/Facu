#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "timing.h"


#define N 500000000
#define T 6

double* arr;
double min[T];

double* rand_arr(){
    double* arr=malloc(sizeof(double)*N);
    for (int i = 0; i < N; i++){
      arr[i]= ((-1)^(rand()%2))*((rand()%100240)*1.0)/((rand()%10*1.0)+1);
    } 
    return arr;
  }

void print (){
  for(int i=0;i<N;i++){

    printf("%f ",arr[i]);
  }
  printf("\n");
}


void min_search(int id){
  
  unsigned long long int start=id*(N/T);
  unsigned long long int idx=0;
  min[id]=arr[start];
  for(;idx<N/T;idx++){
    if(arr[idx+start]<min[id]){
      min[id] =arr[idx+start];
    }
    
    
  }
}

double minimun(double* arr){
  double min=arr[0];
  for(int i=0;i<T;i++){
    if(arr[i]<min)
      min=arr[i];
  }
  return min;
}

void min_arr(){
  unsigned long long int start;
    
  #pragma omp parallel num_threads(T)
  {
    int id = omp_get_thread_num();
    //printf("ID:%d\n",id);
    //min_search(id);
    #pragma omp private(start,id)
    {

      start=id*(N/T);   
      
      min[id]=arr[start];
      #pragma omp for
      for(unsigned long long idx=0;idx<N;idx++){
        if(arr[idx]<min[id]){
          min[id] =arr[idx];
        }
      }
    }
  }
  double global_min= minimun(min);
  printf("Min:%f\n",global_min);
}

int main(){
  arr=rand_arr(); 
  printf("Termine de hacer el arrroz\n");
  float time;
  TIME_void(min_arr(),&time);
  
  free(arr);
  
  return 0;
  
}
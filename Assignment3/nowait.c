#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 10
 
void print10(){
   for(int i=1;i<=10;i++){
    printf("%d ",i);
   }
   printf("\n");
}
 
void loop(int i){
   printf("Index: %d\n", i);
}
 
int main(){
 
  int* a = malloc(sizeof(int) * N);
  for(int i=0; i<N; i++){
      a[i] = 1;
  }
 
  #pragma omp parallel
  {
      #pragma omp for nowait
      for(int i=0; i<N; i++){
          loop(i);
      }
      print10();
  }
}

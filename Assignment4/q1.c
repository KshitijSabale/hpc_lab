#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
long long int fib(long long int n) {
  int i, j;
  if (n<2)
     return n;
  else {
     #pragma omp task shared(i)
     i=fib(n-1);
     #pragma omp task shared(j)
     j=fib(n-2);
     #pragma omp taskwait
     return i+j;
  }
}
 
int main(int argc, char **argv){
  long long int n, result;
  char *a = argv[1];
  n = atoi(a);
  #pragma omp parallel
  {
     #pragma omp single
     for(long long int i=1;i<=n;i++){
        result = fib(i);
        printf("Result is %d : %d\n",i, result);
     }
  }
  printf("Result is %d\n", result);
}

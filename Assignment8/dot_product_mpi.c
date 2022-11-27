#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 100

int dot_product(int s,int e, int x[], int y[], int n){
  int i,ans=0;
  for (i = s; i < e; i++)
    ans = ans + x[i] * y[i];  
  return ans;
}

void init_lst(int l[],int n){
  int i;
  for (i=0; i<n; i++){
    l[i] = i;
  }
}
void print_lst(int l[],int n){
  int i;

  for (i=0; i<n; i++) {
    printf("%d ", l[i]);
  }
  printf("\n");
}

int main() {
  int i,n,vector_x[MAX_SIZE],vector_y[MAX_SIZE];
  int ans,st,en,size,rank;
  double stime,etime;
  MPI_Status status;
  MPI_Comm world;
  n = 8;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (n > MAX_SIZE || size>n) { printf("n=%d > N=%d\n",n,MAX_SIZE); exit(1); }

  int portion = n / size;
  st = rank * portion;
  en = st + portion;
  init_lst(vector_x, n);
  init_lst(vector_y, n);

  int x=0;

  stime = MPI_Wtime();

  if (rank == 0 ) {
    ans = dot_product(st, en, vector_x, vector_y, n);
    for (i = 1; i < size; i++){
      x=0;
      MPI_Recv(&x, 1, MPI_INT, i, 123, MPI_COMM_WORLD, &status);
      ans +=x;
    }
    etime = MPI_Wtime();
    print_lst(vector_x,n);
    print_lst(vector_y,n);    
    printf("pid=%d: final ans=%d\n",rank,ans);
    printf("pid=%d: elapsed=%f\n",rank,etime-stime);
  }
  else {
    ans = dot_product(st, en, vector_x, vector_y, n);
    MPI_Send(&ans, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
  }  
  MPI_Finalize();
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv){
  int a[5] = {2,4,1,4,2};
  int b[4] = {2,4,4,2};
  int c[4] = {2,1,3,2};
  int n = 4,flag=0;
  #pragma omp parallel for
    for(int i=0;i<n/2;i++)
    {
        if(c[i]!=c[n-1-i])
        {
            flag =1 ;
        }
    }
  if(!flag)printf("Yes\n");
  else printf("No\n");
}

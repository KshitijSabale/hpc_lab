#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

void main()
{   
    long long sum=0;
    clock_t t;
    t = clock();
    for(int i=1;i<=10000000;i++){
        sum+=(i*i);
        long long s = i*i;
        // printf("Square of %d = %lld\n",i,s);
    }
    t = clock()-t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("\nTime taken is %f\n",time_taken);
    printf("Sum : %lld\n",sum);
}
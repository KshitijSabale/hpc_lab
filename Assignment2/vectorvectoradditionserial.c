#include <omp.h>
#include <stdio.h>
#include <pthread.h>

void main()
{
    int n = 100000;
    int a[100000];
    for(int i=0;i<n;i++)a[i] = i + 1;

    int b[100000];
    for(int i=0;i<n;i++)b[i] = n - i;

    int c[100000] = {0};
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
        // printf("Thread: %d Index: %d\n", omp_get_thread_num(),i);
    }

    for(int i=0;i<n;i++){
        printf("%d ", c[i]);
    }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("\nTime taken is %f\n", exec_time);
    printf("\n");
}
// gcc -fopenmp vectorvectoradditionserial.c
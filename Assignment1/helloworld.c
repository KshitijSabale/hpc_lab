#include <omp.h>
#include <stdio.h>
#include <pthread.h>

void main()
{   
    printf("Hello World\n");
    // omp_set_num_threads(5);
    #pragma omp parallel for ordered
    for(int i=0;i<5;i++)
    {   
        #pragma omp ordered
        printf("Hello from thread number %d \n",omp_get_thread_num());
    }
}


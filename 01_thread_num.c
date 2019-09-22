/*Prints each thead's number*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
    int nthreads, tid;
    #pragma omp parallel private(nthreads, tid)
    {
        tid = omp_get_thread_num();
        printf("Hello world from thread: %d\n", tid);
        /*Only master thread does this*/
        if(tid == 0){
            nthreads = omp_get_num_threads();
            printf("The number of threads: %d\n", nthreads);
        }
    }
}
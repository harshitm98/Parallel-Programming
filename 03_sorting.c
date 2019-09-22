#include <stdio.h>
#include <omp.h>
# define N 5

int main(int argc, char *argv[]){
    float a[N] = {1.25, -2.00, 3.16, 3.15, 5.11};
    float b[N];
    int ind[N];
    int i, j;
    #pragma omp parallel
    {
        #pragma omp for
        for(i=0; i<N; i++) ind[i] = 0;
        #pragma omp for collapse(2) private(i, j)
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                if(a[i]>a[j] || a[i]==a[j] && i>j)
                    #pragma omp critical
                    ind[i]++;
        #pragma omp for
        for(i=0;i<N;i++) b[ind[i]] = a[i];
    }
    printf("a: \n"); // Before sorting
    for(i=0;i<N;i++)printf("%6.2f", a[i]);
    printf("\nb: \n"); // After sorting
    for(i=0;i<N;i++)printf("%6.2f", b[i]);
    printf("\n");
}
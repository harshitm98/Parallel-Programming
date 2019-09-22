#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#define N 1000000
#define S (int)sqrt(N)
#define M N/10

int main(int argc, char** argv[]){
    long int a[S+1];
    long int prime[M];
    long int i, k, num, remainder;
    long int no_of_div;
    long int no_of_prime = 0;
    double time;

    time = omp_get_wtime();
    #pragma omp parallel for shared(a)
    for(i=2;i<=S;i++)a[i]=1;
    for(i=2;i<=S;i++)
        if(a[i]==1){
            prime[no_of_prime++] = i;
            for(k=i+1;k<=S;k+=i) a[k] = 0;
        }
        no_of_div = no_of_prime;
        #pragma omp parallel for default(none) private(k,remainder) \
        shared(no_of_prime, no_of_div, prime)
        for(num=S+1;num<=N;num++){
            for(k=0;k<no_of_div;k++){
                remainder = (num%prime[k]);
                if(remainder == 0) break;
            }
            if(remainder!=0){
                #pragma omp critical
                prime[no_of_prime++]=num;
            }
        }
        time = omp_get_wtime() - time;
        printf("Time: %f sec\n", time);
        return 0;
}
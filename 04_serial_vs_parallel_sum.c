#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

main(){
	float *array, *check, serial_sum, sum, partialsum;
	int array_size, i;
	printf("Enter the size of array: ");
	scanf("%d", &array_size);
	if(array_size == 0){
		printf("Invalid output");
		//exit(1);
	}
	array = (float*) malloc(sizeof(float)*array_size);
	check = (float*) malloc(sizeof(float)*array_size);
	for(i=0;i<array_size;i++){
		array[i] = i*5;
		check[i] = array[i];
	}
	printf("Array elements are: \n");
	for(i=0;i<array_size;i++){
		printf("%f ", array[i]);
	}
	sum = 0.0;
	partialsum = 0.0;
	#pragma omp parallel for shared(sum)
	for(i=0;i<array_size;i++){
		#pragma omp critical
		sum+=array[i];
	}
	serial_sum = 0.0;
	for(i=0;i<array_size;i++){
		serial_sum += check[i];
	}
	if (serial_sum == sum){
		printf("\n The serial and parallel sum are equal...\n");
	}
	else{
		printf("\n The serial and parallel sum are not equal...\n");
	}
	free(check);
	free(array);
}
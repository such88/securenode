//#define _POSIX_C_SOURCE 200809L // Required for POSIX functions
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <inttypes.h>
#include <stdint.h>
#include "types.h"

#define ROW_1	(10U)
#define ROW_2	(10U)
#define COL_1	(10U)
#define COL_2	(10U)

volatile double matrix_1[ROW_1][COL_1];
volatile double matrix_2[ROW_2][COL_2];

long long get_current_time_milliseconds() {
    struct timespec spec;
    // Use CLOCK_REALTIME for time since the Epoch (Jan 1, 1970, 00:00 UTC)
    // For measuring elapsed time within a process, consider CLOCK_MONOTONIC
    if (clock_gettime(CLOCK_REALTIME, &spec) == -1) {
        perror("clock_gettime");
        return -1; // Or handle error as appropriate
    }
    // Convert seconds to milliseconds and add milliseconds from the nanosecond field
    return (long long)spec.tv_sec * 1000000LL  + spec.tv_nsec / 1000;
}

int main() {
	long long before_mul = 0;
	long long after_mul =0;
	uint32_t i;
	uint32_t res_matrix[ROW_1][COL_2];
	uint32_t rows = sizeof(matrix_1)/sizeof(matrix_1[0]);
	uint32_t col = sizeof(matrix_2[0])/sizeof(matrix_2[0][0]);
	uint32_t val=0;
	if(rows != col){
		printf("Not possible to do the matrix mul \n");
		return 0;
	}
	double start_val = 1.0;
	for(i=0; i< rows; i++){
		for(uint32_t j=0; j<col; j++){
			matrix_1[i][j] = start_val;
			matrix_2[i][j] = start_val+100;
			start_val++;
		}
	}
	/* Print matrix_1 and matrix_2 
	for(i=0; i<rows; i++){
		for(uint32_t j=0; j<col; j++){
			printf("%u,", matrix_1[i][j]);
		}
		printf("\n");
	}
	
	printf("\n\n");
	for(i=0; i<rows; i++){
		for(uint32_t j=0; j<col; j++){
			printf("%u,", matrix_2[i][j]);
		}
		printf("\n");
	}*/
	
	printf("\n\n");
	before_mul = get_current_time_milliseconds();
	for(i=0; i< rows; i++){
		for(uint32_t j=0; j<col; j++){
			res_matrix[i][j] = 0;
			for(uint32_t k=0; k<col; k++){
				res_matrix[i][j] +=(matrix_1[i][k] * matrix_2[k][j]);
			}
		}
	}
	after_mul = get_current_time_milliseconds();
	/* Print result matrix
	for(i=0; i<rows; i++){
		for(uint32_t j=0; j<col; j++){
			//printf("i:%u\tj:%u\n", i, j);
			printf("%u \t", res_matrix[i][j]);
		}
		printf("\n");
	}*/
	printf("Before %llu and after %llu\n", before_mul, after_mul);
	printf("Time lapsed: %llu us\n", after_mul - before_mul);
	
	return 0;
}

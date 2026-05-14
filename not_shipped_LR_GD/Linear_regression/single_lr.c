#include <stdio.h>
#include <time.h> 
#include <inttypes.h>
#include <stdint.h>
#include "gen_cgpa_pkg_data.h"

double m = 0.0;
double b = 0.0;
double mean_cgpa = 0.0;
double mean_pkg = 0.0;


void calculate_mean() {
	for(int i=0; i<ROW_COUNT; i++){
		mean_cgpa += data[i][0];
		mean_pkg += data[i][1];
	}
	mean_cgpa /= ROW_COUNT;
	mean_pkg /= ROW_COUNT;
	printf("mean_cgpa: %.1f, mean_pkg: %.1f \n", mean_cgpa, mean_pkg);
}

void calculate_m_and_b(){
	double prod_cgpa_pkg =0.0;
	double prod_cgpa = 0.0;
	for(int i=0; i< ROW_COUNT; i++){
		prod_cgpa_pkg += ( (data[i][1] - mean_pkg) * (data[i][0] - mean_cgpa) );
	}
	for(int i=0; i<ROW_COUNT; i++){
		prod_cgpa += ((data[i][0] - mean_cgpa) * (data[i][0] - mean_cgpa));
	}
	m = prod_cgpa_pkg/prod_cgpa;
	b = mean_pkg - ( m * mean_cgpa);
}

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

int main(){
	long long before_lr = 0;
	long long after_lr =0;	
	printf("Hello world\n");
	generate_cgpa_vs_package();
	for(int i =0; i< 100; i++){
		printf("%.1f, %.1f \n", data[i][0], data[i][1]);
	}
	printf("\n\n");
	
	before_lr = get_current_time_milliseconds();
	calculate_mean();
	calculate_m_and_b();
	after_lr = get_current_time_milliseconds();
	
	//printf("m: %.8f\tb: %.1f \n", m, b);
	//printf("Before %llu and after %llu\n", before_lr, after_lr);
	printf("Time lapsed: %llu us\n", after_lr - before_lr);
	
	double cgpa = 7.04;
	double package = 0.0;
	while(1){
		printf("Enter cgpa: ");
		scanf(" %lf", &cgpa);
		package = m*cgpa + b;
		printf("package: %.3f\t\n", package);
	}
	return 0;

}

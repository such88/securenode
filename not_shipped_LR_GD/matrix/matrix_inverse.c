#include <stdio.h>
#include <stdlib.h>

double arr[][3]={{5,7,9},{4,3,8}, {7,5,6}};
double aug_arr[][3]={{1,0,0}, {0,1,0}, {0,0,1}};

#define ROW (3U)
#define COL (3U)

void do_matrix_inverse(){
	double row_div = 0.0;
	double col_zero_div = 0.0;
	for(int i=0; i<ROW; i++){
		row_div = arr[i][i];
		for(int j=0; j<COL; j++){
			arr[i][j] /= row_div;
			aug_arr[i][j] /= row_div;
		}
	
		for(int k=i+1; k<ROW; k++){
			col_zero_div = arr[k][i];
			for(int l=0; l<COL; l++){
				arr[k][l] -= col_zero_div * arr[i][l];
				aug_arr[k][l] -= col_zero_div * aug_arr[i][l];
			}
		}
	}
}

int main(){
	printf("Matrix Inversion\n");
	
	do_matrix_inverse();

	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++){
			printf("%lf\t", aug_arr[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
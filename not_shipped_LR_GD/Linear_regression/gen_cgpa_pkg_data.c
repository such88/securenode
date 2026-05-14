#include "gen_cgpa_pkg_data.h"


double data[ROW_COUNT][COL_COUNT] = {{0.0, 0.0}};

void generate_cgpa_vs_package() {
    // Seed the random number generator
    srand(time(NULL));

    double min_cgpa = 6.0;
    double max_cgpa = 10.0;
	double min_package = 2.5;
	double max_package = 12.5;
	double random_cgpa;
	double random_package;
	
    for (int i = 0; i < ROW_COUNT; i++) {
        // Generate random number: 
        // 1. (max-min)*10 = 400 (range of 0.1 steps)
        // 2. rand() % 401 gives integer 0-400
        // 3. Divide by 10.0 to get 0.0, 0.1, ..., 40.0
        // 4. Add min (6.0)
		unsigned int random = rand();

        random_cgpa = min_cgpa + (random % ((int)((max_cgpa - min_cgpa) * 10) + 1)) / 10.0;
		if(random_cgpa < 7.0){
			random_package = min_package + (random % 3 + 1)/10.0;	// keep the package within 4
		}
		else if(random_cgpa < 8.0){
			random_package = min_package + (random % 8 + 1)/10.0; //keep the package within 9
		}
		else{
			random_package = min_package + (random % 12 +1)/10.0; // keep  the package within 12
		}
       
        data[i][0] = random_cgpa;
		data[i][1] = random_package;
    }
}




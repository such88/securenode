#ifndef GEN_CGPA_PKG_H
#define GEN_CGPA_PKG_H

#include <stdlib.h>
#include <time.h>

#define ROW_COUNT (100)
#define COL_COUNT (2) // 1 for CGPA,2 for Package

extern double data[ROW_COUNT][COL_COUNT];
void generate_cgpa_vs_package();

#endif

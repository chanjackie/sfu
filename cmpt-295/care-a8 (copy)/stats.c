
#include <stdio.h>
#include <math.h>


void min_max_avg(float **grid, int N, int M, 
                 float *min, float *max, float *avg, 
                 float *col_min, float *col_max, float *col_avg, 
                 float *row_min, float *row_max, float *row_avg) {


    int i, j;


    // compute overall min
    *min = INFINITY;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (grid[i][j] < *min) {
                *min = grid[i][j];
            }
        }
    }


    // compute overall max
    *max = -INFINITY;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (grid[i][j] > *max) {
                *max = grid[i][j];
            }
        }
    }


    // compute overall average
    *avg = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            *avg += grid[i][j];
        }
    }
    if (N * M > 0) {
        *avg /= (float)(M * N);
    } else {
        *avg = NAN;
    }


    // compute stats by row
    for (i = 0; i < N; i++) {
        row_min[i] = +INFINITY;
        row_max[i] = -INFINITY;
        row_avg[i] = 0;
        for (j = 0; j < M; j++) {
            if (grid[i][j] < row_min[i]) {
                row_min[i] = grid[i][j];
            }
            if (grid[i][j] > row_max[i]) {
                row_max[i] = grid[i][j];
            }
            row_avg[i] += grid[i][j];
        }
        if (M == 0) {
            row_avg[i] = NAN;
        } else {
            row_avg[i] /= (float)M;
        }
    }


    // compute stats by col
    for (j = 0; j < M; j++) {
        col_min[j] = +INFINITY;
        col_max[j] = -INFINITY;
        col_avg[j] = 0;
        for (i = 0; i < N; i++) {
            if (grid[i][j] < col_min[j]) {
                col_min[j] = grid[i][j];
            }
            if (grid[i][j] > col_max[j]) {
                col_max[j] = grid[i][j];
            }
            col_avg[j] += grid[i][j];
        }
        if (N == 0) {
            col_avg[j] = NAN;
        } else {
            col_avg[j] /= (float)N;
        }
    }


} // min_max_avg


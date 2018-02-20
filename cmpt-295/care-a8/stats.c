
#include <stdio.h>
#include <math.h>


void min_max_avg(float **grid, int N, int M, 
                 float *min, float *max, float *avg, 
                 float *col_min, float *col_max, float *col_avg, 
                 float *row_min, float *row_max, float *row_avg) {


    int i, j;


    // compute overall min, loop unrolling about 10% faster
    *min = INFINITY;
    float minalias = INFINITY; // remove memory aliasing be using a float as a substitute, minimal increase in efficiency
    for (i = 0; i < N-3; i+=3) { // outer loop unrolling: efficiency increase
        for (j = 0; j < M-3; j+=3) { // inner loop unrolling for efficiency increase
            if (grid[i][j] < minalias) {
                minalias = grid[i][j];
            } else if (grid[i][j+1] < minalias) {
                minalias = grid[i][j+1];
            } else if (grid[i][j+2] < minalias) {
                minalias = grid[i][j+2];
            }
        }
        for ( ; j<M; j++) {
            if (grid[i][j] < minalias) {
                minalias = grid[i][j];
            }
        }
        for (j = 0; j < M-3; j+=3) { // inner loop unrolling for efficiency increase
            if (grid[i+1][j] < minalias) {
                minalias = grid[i+1][j];
            } else if (grid[i+1][j+1] < minalias) {
                minalias = grid[i+1][j+1];
            } else if (grid[i+1][j+2] < minalias) {
                minalias = grid[i+1][j+2];
            }
        }
        for ( ; j<M; j++) {
            if (grid[i+1][j] < minalias) {
                minalias = grid[i+1][j];
            }
        }
        for (j = 0; j < M-3; j+=3) { // inner loop unrolling for efficiency increase
            if (grid[i+2][j] < minalias) {
                minalias = grid[i+2][j];
            } else if (grid[i+2][j+1] < minalias) {
                minalias = grid[i+2][j+1];
            } else if (grid[i+2][j+2] < minalias) {
                minalias = grid[i+2][j+2];
            }
        }
        for ( ; j<M; j++) {
            if (grid[i+2][j] < minalias) {
                minalias = grid[i+2][j];
            }
        }
    }
    for (; i<N;i++) {
        for (j = 0; j < M-3; j+=3) { // inner loop unrolling for efficiency increase
            if (grid[i][j] < minalias) {
                minalias = grid[i][j];
            } else if (grid[i][j+1] < minalias) {
                minalias = grid[i][j+1];
            } else if (grid[i][j+2] < minalias) {
                minalias = grid[i][j+2];
            }
        }
        for ( ; j<M; j++) {
            if (grid[i][j] < minalias) {
                minalias = grid[i][j];
            }
        }
    }
    *min = minalias;


    // compute overall max, loop unrolling, about 10% faster
    *max = -INFINITY;
    float maxalias = -INFINITY; // substitute to remove memory aliasing, minimal efficiency increase
    for (i = 0; i < N-3; i+=3) { // outer loop unrolling for efficiency
        for (j = 0; j < M-3; j+=3) { // inner loop unrolling
            if (grid[i][j] > maxalias) {
                maxalias = grid[i][j];
            } else if (grid[i][j+1] > maxalias) {
                maxalias = grid[i][j+1];
            } else if (grid[i][j+2] > maxalias) {
                maxalias = grid[i][j+2];
            }
        }
        for (; j<M; j++) {
            if (grid[i][j] > maxalias) {
                maxalias = grid[i][j];
            }
        }
        for (j = 0; j < M-3; j+=3) {
            if (grid[i+1][j] > maxalias) {
                maxalias = grid[i+1][j];
            } else if (grid[i+1][j+1] > maxalias) {
                maxalias = grid[i+1][j+1];
            } else if (grid[i+1][j+2] > maxalias) {
                maxalias = grid[i+1][j+2];
            }
        }
        for (; j<M; j++) {
            if (grid[i+1][j] > maxalias) {
                maxalias = grid[i+1][j];
            }
        }
        for (j = 0; j < M-3; j+=3) {
            if (grid[i+2][j] > maxalias) {
                maxalias = grid[i+2][j];
            } else if (grid[i+2][j+1] > maxalias) {
                maxalias = grid[i+2][j+1];
            } else if (grid[i+2][j+2] > maxalias) {
                maxalias = grid[i+2][j+2];
            }
        }
        for (; j<M; j++) {
            if (grid[i+2][j] > maxalias) {
                maxalias = grid[i+2][j];
            }
        }
    }
    for (; i<N;i++) {
        for (j = 0; j < M-3; j+=3) {
            if (grid[i][j] > maxalias) {
                maxalias = grid[i][j];
            } else if (grid[i][j+1] > maxalias) {
                maxalias = grid[i][j+1];
            } else if (grid[i][j+2] > maxalias) {
                maxalias = grid[i][j+2];
            }
        }
        for (; j<M; j++) {
            if (grid[i][j] > maxalias) {
                maxalias = grid[i][j];
            }
        }
    }
    *max = maxalias;


    // compute overall average, loop unrolling about 5% faster
    *avg = 0;
    float avgalias = 0; // substitute to remove memory aliasing, minimal efficiency increase
    for (i = 0; i < N-2; i+=2) { // outer loop unrolling for slight cycle efficiency increase
        for (j = 0; j < M-3; j+=3) { // inner loop unrolling for slight cycle efficiency increase
            avgalias += grid[i][j] + grid[i][j+1] + grid[i][j+2];
        }
        for ( ; j < M; j++) {
            avgalias += grid[i][j];
        }
        for (j = 0; j < M-3; j+=3) {
            avgalias += grid[i+1][j] + grid[i+1][j+1] + grid[i+1][j+2];
        }
        for ( ; j < M; j++) {
            avgalias += grid[i+1][j];
        }
    }
    for ( ; i < N; i++) {
        for (j = 0; j < M-3; j+=3) {
            avgalias += grid[i][j] + grid[i][j+1] + grid[i][j+2];
        }
        for ( ; j < M; j++) {
            avgalias += grid[i][j];
        }
    }
    if (N * M > 0) {
        avgalias /= (float)(M * N);
    } else {
        avgalias = NAN;
    }
    *avg = avgalias;

    // compute stats by row
    for (i = 0; i < N; i++) {
        row_min[i] = +INFINITY;
        row_max[i] = -INFINITY;
        row_avg[i] = 0;
        for (j = 0; j < M-3; j+=3) { // loop unrolling, about 10% faster
            if (grid[i][j] < row_min[i]) {
                row_min[i] = grid[i][j];
            } else if (grid[i][j+1] < row_min[i]) {
                row_min[i] = grid[i][j+1];
            } else if (grid[i][j+2] < row_min[i]) {
                row_min[i] = grid[i][j+2];
            }
            if (grid[i][j] > row_max[i]) {
                row_max[i] = grid[i][j];
            } else if (grid[i][j+1] > row_max[i]) {
                row_max[i] = grid[i][j+1];
            } else if (grid[i][j+2] > row_max[i]) {
                row_max[i] = grid[i][j+2];
            }
            row_avg[i] += grid[i][j] + grid[i][j+1] + grid[i][j+2];
        }
        for (;j<M;j++) {
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
        for (i = 0; i < N-3; i+=3) { // loop unrolling, about 10% faster
            if (grid[i][j] < col_min[j]) {
                col_min[j] = grid[i][j];
            } else if (grid[i+1][j] < col_min[j]) {
                col_min[j] = grid[i+1][j];
            } else if (grid[i+2][j] < col_min[j]) {
                col_min[j] = grid[i+2][j];
            }
            if (grid[i][j] > col_max[j]) {
                col_max[j] = grid[i][j];
            } else if (grid[i+1][j] > col_max[j]) {
                col_max[j] = grid[i+1][j];
            } else if (grid[i+2][j] > col_max[j]) {
                col_max[j] = grid[i+2][j];
            }
            col_avg[j] += grid[i][j] + grid[i+1][j] + grid[i+2][j];
        }
        for (;i<N;i++) {
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


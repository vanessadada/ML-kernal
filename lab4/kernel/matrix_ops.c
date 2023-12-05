#include "matrix_ops.h"
#include <pthread.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX_THREADS 8

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    /**** YOUR CODE HERE ****/
    for (int i = 0; i < A_rows; i++){
    	for (int j = 0; j < B_cols; j++){
            float sum = 0.0;
            for (int k = 0; k < B_rows; k++){
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
	    }
    }
    return C;
}

// multi thread matrix multiplication

typedef struct {
    float **A;
    float **B;
    float **C;
    int A_rows, A_cols, B_rows, B_cols;
    int start_row, end_row;
} MatrixData;

void *block_mult(void *args){
    MatrixData *data = (MatrixData *)args;
    int block_size = 64 / sizeof(float); // 64 is the common cache line size for x86_64 architecture
    
    // six loop, block all the three level
    for(int i = data->start_row; i < data->end_row; i+=block_size){
        for(int j = 0; j < data->B_cols; j+=block_size){
            for(int k = 0; k < data->B_rows; k+=block_size){
                for(int ii = i; ii < MIN(i + block_size, data->end_row); ii++){
                    for(int jj = j; jj < MIN(j + block_size, data->B_cols); jj++){
                        for(int kk = k; kk < MIN(k + block_size, data->B_rows); kk++){
                            data->C[ii][jj] += data->A[ii][kk] * data->B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

float **matmul_multithread(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions are not compatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    // initialize C
    for(int i = 0; i< A_rows; i++){
        for(int j = 0; j<B_cols; j++){
            C[i][j] = 0.0;
        }
    }

    pthread_t threads[MAX_THREADS];
    MatrixData thread_data[MAX_THREADS];

    int rows_per_thread = A_rows / MAX_THREADS;

    // Create threads
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].A_rows = A_rows;
        thread_data[i].A_cols = A_cols;
        thread_data[i].B_rows = B_rows;
        thread_data[i].B_cols = B_cols;
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == MAX_THREADS - 1) ? A_rows : (i + 1) * rows_per_thread;
        
        pthread_create(&threads[i], NULL, block_mult, (void *)&thread_data[i]);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return C;
}
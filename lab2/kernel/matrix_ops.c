#include "matrix_ops.h"
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
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

float **matmul_blocking(float **A, float **B, int A_rows, int A_cols,int B_rows, int B_cols){
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

    // int block_size = 64 / sizeof(float); // 64 is the common cache line size for x86_64 architecture
    int block_size = 5;
    
    // six loop, block all the three level
    for(int i = 0; i < A_rows; i+=block_size){
        for(int j = 0; j < B_cols; j+=block_size){
            for(int k = 0; k < B_rows; k+=block_size){
                for(int ii = i; ii < MIN(i + block_size, A_rows); ii++){
                    for(int jj = j; jj < MIN(j + block_size, B_cols); jj++){
                        for(int kk = k; kk < MIN(k + block_size, B_rows); kk++){
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }

    // five loop block two level  
    // for(int i = 0; i < A_rows; i+=block_size){
    //     for(int j = 0; j < B_cols; j+=block_size){
    //             int minI = MIN(i + block_size, A_rows);
    //             int minJ = MIN(j + block_size, B_cols);
            
    //             for(int ii = i; ii < minI; ii++){
    //                 for(int jj = j; jj < minJ; jj++){
    //                     for(int kk = 0; kk < B_rows; kk++){
    //                         C[ii][jj] += A[ii][kk] * B[kk][jj];
    //                     }
    //                 }
    //             }
    //     }
    // }

    return C;
}

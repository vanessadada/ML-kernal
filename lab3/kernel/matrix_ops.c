#include "matrix_ops.h"
#include <time.h>
#define MAX(x, y) (((x) < (y)) ? (y) : (x))

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

typedef struct {
    int sz;         
    float *val;     
    int *cols;     
    int *rows;      
    int colShape;
    int rowShape;
} csrMatrix;

csrMatrix *create_sparse_matrix(float **matrix, int row, int col){
    csrMatrix *csr = (csrMatrix *)malloc(sizeof(csrMatrix));
    if (!csr) {
        fprintf(stderr, "Memory allocation failed in create csr.\n");
        exit(1);
    }

    int sz = 0;
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            if(matrix[i][j] != 0){
                sz++;
            }
        }
    }

    csr->sz = sz;
    csr->val = (float*)malloc(sz* sizeof(float));
    csr->cols = (int*)malloc(sz * sizeof(int));
    csr->rows = (int*)malloc((row + 1) * sizeof(int));
    csr->rowShape = row;
    csr->colShape = col;

    if (!csr->val || !csr->cols || !csr->rows) {
        fprintf(stderr, "Memory allocation failed within csr.\n");
        exit(1);
    }

    int sz_idx = 0;
    csr->rows[0] = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] != 0) {
                csr->val[sz_idx] = matrix[i][j];
                csr->cols[sz_idx] = j;
                sz_idx++;
            }
        }
        csr->rows[i + 1] = sz_idx;
    }

    return csr;
}

void free_csr_matrix(csrMatrix *csr) {
    free(csr->val);
    free(csr->cols);
    free(csr->rows);
    free(csr);
}

csrMatrix *matrix_multiply_csr(const csrMatrix *csrA, const csrMatrix *csrB) {
    int A_rows = csrA->sz;
    int B_cols = csrB->sz;

    csrMatrix *result = (csrMatrix *)malloc(sizeof(csrMatrix));
    result->val = (float *)malloc((csrA->rowShape * csrB->colShape) * sizeof(float));
    result->cols = (int *)malloc((csrA->rowShape * csrB->colShape) * sizeof(int));
    result->rows = (int *)malloc((csrA->rowShape + 1) * sizeof(int));
    result->rowShape = csrA->rowShape;
    result->colShape = csrB->colShape;

    if (!result || !result->val || !result->cols || !result->rows) {
        fprintf(stderr, "Memory allocation failed in multi.\n");
        exit(1);
    }

    int sz_idx = 0;
    result->rows[0] = 0;

    for (int i = 0; i < csrA->rowShape; i++) {
        for (int j = 0; j < csrB->colShape; j++) {
            float dot_product = 0.0;

            for (int k = csrA->rows[i]; k < csrA->rows[i + 1]; k++) {
                int a_col = csrA->cols[k];

                for (int l = csrB->rows[a_col]; l < csrB->rows[a_col + 1]; l++) {
                    if (csrB->cols[l] == j) {
                        dot_product += csrA->val[k] * csrB->val[l];
                    }
                }
            }

            if (dot_product != 0.0) {
                result->val[sz_idx] = dot_product;
                result->cols[sz_idx] = j;
                sz_idx++;
            }
        }
        result->rows[i + 1] = sz_idx;
    }

    result->sz = sz_idx;
    return result;
}

float **csr_to_dense(csrMatrix *csr){
    int rows = csr->rowShape;
    int cols = csr->colShape;
    int sz = csr->sz;

    float **dense_matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        dense_matrix[i] = (float *)malloc(cols * sizeof(float));
        for (int j = 0; j < cols; j++) {
            dense_matrix[i][j] = 0.0;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = csr->rows[i]; j < csr->rows[i + 1]; j++) {
            int col = csr->cols[j];
            dense_matrix[i][col] = csr->val[j];
        }
    }
   
    return dense_matrix;
}

float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    /**** 1. Create CSR format of input matrix ****/
    csrMatrix *csrA = create_sparse_matrix(A, A_rows, A_cols);
    csrMatrix *csrB = create_sparse_matrix(B, B_rows, B_cols);

    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;

    /**** 2. Perform matrix multiplication on CSR format of input matrix ****/
    csrMatrix *result = matrix_multiply_csr(csrA, csrB);

    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of sparse matrix: %f \n", time_diff);

    /**** 3. Convert sparse matrix to dense matrix ****/
    float **ans = csr_to_dense(result);

    free_csr_matrix(csrA);
    free_csr_matrix(csrB);
    free_csr_matrix(result);

    // When profiling, only loop over part 2.
    return ans;
}

void printCSR(csrMatrix *matrix){
    printf("************* sparse matrix: ************** \n");
    printf("values: \n");
    int sz = matrix->sz;
    for(int i = 0; i<sz; i++){
        printf("%f ", matrix->val[i]);
    }
    printf("\ncols: \n");
    for(int i = 0; i<sz; i++){
        printf("%d ", matrix->cols[i]);
    }
    printf("\nrows: \n");
    for(int i = 0; i<sz; i++){
        printf("%d ", matrix->rows[i]);
    }
    printf("\n");
}

void printMatrix(float **matrix, csrMatrix *result){
    printf("multiplication matrix result: \n");
    for(int i = 0; i<result->rowShape; i++){
        for(int j = 0; j<result->colShape; j++){
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}


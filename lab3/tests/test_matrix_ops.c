#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"
#include <time.h>

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

// for profile
// Function to generate a high sparsity matrix
float** generate_sparse_matrix(int rows, int cols, float sparsity) {
    float** matrix = (float**)malloc(rows * sizeof(float*));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (float*)malloc(cols * sizeof(float));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }
    }

    srand(time(NULL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float random_value = (float)rand() / RAND_MAX;
            if (random_value > sparsity) {
                matrix[i][j] = 0.0;
            } else {
                matrix[i][j] = (float)rand() / RAND_MAX;
            }
        }
    }

    return matrix;
}

float **helper_matrix(int n, int m){
    float **A = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
    {
        A[i] = (float *)malloc(m * sizeof(float));
    }

    for(int i =0; i<n; i++){
        for (int j = 0; j<m; j++){
            A[i][j] = 0.0;
        }
    }
    A[0][1] = 2.0;
    return A;
}

void cleanup(float **A, float **B, int n, int m){
    for (int i = 0; i < n; i++)
    {
        free(A[i]);
    }

    for (int i = 0; i < m; i++)
    {
    	free(B[i]);
    }
    free(A);
    free(B);
}

void test_matmul_square_matrices_10(void){
    int len = 300;
    float sparsity = 0.1;
    float **A = generate_sparse_matrix(len, len, sparsity);
    float **B = generate_sparse_matrix(len, len, sparsity);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;

    float **C = matmul(A, B, len, len, len, len);

    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of matrix: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_matmul_square_matrices_100(void){
    int len = 100;
    float sparsity = 0.8;
    float **A = generate_sparse_matrix(len, len, sparsity);
    float **B = generate_sparse_matrix(len, len, sparsity);
    float **C = matmul(A, B, len, len, len, len);

    cleanup(A, B, len, len);
}

void test_matmul_square_matrices_500(void){
    int len = 1000;
    float sparsity = 0.8;
    float **A = generate_sparse_matrix(len, len, sparsity);
    float **B = generate_sparse_matrix(len, len, sparsity);
    float **C = matmul(A, B, len, len, len, len);

    cleanup(A, B, len, len);
}

// test for correctness
void test_matmul_square_matrices(void)
{
    /**** YOUR CODE HERE ****/

    float **A = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        A[i] = (float *)malloc(3 * sizeof(float));
    }
    float **B = (float **)malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++)
    {
        B[i] = (float *)malloc(1 * sizeof(float));
    }

    A[0][0] = 1;
    A[0][1] = 2;
    A[0][2] = 3;
    A[1][0] = 0;
    A[1][1] = 4;
    A[1][2] = 5;

    B[0][0] = 2;
    B[1][0] = 1;
    B[2][0] = 4;

    float **C = matmul(A, B, 2, 3, 3, 1);
    TEST_ASSERT_EQUAL_FLOAT(C[0][0], 16.0);
    TEST_ASSERT_EQUAL_FLOAT(C[1][0], 24.0);

    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
    }

    for (int i = 0; i < 3; i++)
    {
    	free(B[i]);
    }
    free(A);
    free(B);
}

void test_matmul_incompatible_dimensions(void)
{
    // Setup
    float **A = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        A[i] = (float *)malloc(3 * sizeof(float));
    }

    float **B = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        B[i] = (float *)malloc(2 * sizeof(float));
    }

    // Run function under test
    float **C = matmul(A, B, 2, 3, 2, 2);

    // Check expectations
    UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
}

// test for correctness
void test_matmul_sparse(void){
    float **A = (float **)malloc(4 * sizeof(float *));
    for (int i = 0; i < 4; i++)
    {
        A[i] = (float *)malloc(4 * sizeof(float));
    }
    float **B = (float **)malloc(4 * sizeof(float *));
    for (int i = 0; i < 4; i++)
    {
        B[i] = (float *)malloc(4 * sizeof(float));
    }

    A[0][0] = 0;
    A[0][1] = 10;
    A[0][2] = 0;
    A[0][3] = 12;


    A[1][0] = 0;
    A[1][1] = 0;
    A[1][2] = 0;
    A[1][3] = 0;


    A[2][0] = 0;
    A[2][1] = 0;
    A[2][2] = 5;
    A[2][3] = 0;
 

    A[3][0] = 15;
    A[3][1] = 12;
    A[3][2] = 0;
    A[3][3] = 0;

    B[0][0] = 0;
    B[0][1] = 0;
    B[0][2] = 8;
    B[0][3] = 0;


    B[1][0] = 0;
    B[1][1] = 0;
    B[1][2] = 0;
    B[1][3] = 23;


    B[2][0] = 0;
    B[2][1] = 0;
    B[2][2] = 9;
    B[2][3] = 0;
 

    B[3][0] = 20;
    B[3][1] = 25;
    B[3][2] = 0;
    B[3][3] = 0;


    float **res = matmul_sparse(A, B, 4, 4, 4, 4);
    float **C = matmul(A, B, 4, 4, 4, 4);
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            TEST_ASSERT_EQUAL_FLOAT(res[i][j], C[i][j]);
        }
    }
}

// for profiling

void test_matmul_sparse_10(void){
    // high sparsity
    float sparsity = 0.04;
    int len = 10;
    float **A = generate_sparse_matrix(len, len, sparsity);
    float **B = generate_sparse_matrix(len, len, sparsity);
    // float **A = helper_matrix(len, len);
    // float **B = helper_matrix(len, len);
    float **C = matmul_sparse(A, B, len, len, len, len);

    // float **base = matmul(A, B, len, len, len, len);
    // for(int i = 0; i<len; i++){
    //     for(int j = 0; j<len; j++){
    //         TEST_ASSERT_EQUAL_FLOAT(base[i][j], C[i][j]);
    //     }
    // }

    cleanup(A, B, len, len);
}

void test_matmul_sparse_500(void){
    // high sparsity
    float sparsity = 0.8;
    int len = 500;
    float **A = generate_sparse_matrix(len, len, sparsity);
    float **B = generate_sparse_matrix(len, len, sparsity);
    float **C = matmul_sparse(A, B, len, len, len, len);

    cleanup(A, B, len, len);
}

void test_matmul_sparse_1000(void){
    // high sparsity
    float sparsity = 0.8;
    int len = 1000;
    float **A = generate_sparse_matrix(len, len, sparsity);
    float **B = generate_sparse_matrix(len, len, sparsity);
    float **C = matmul_sparse(A, B, len, len, len, len);

    cleanup(A, B, len, len);
}
#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"
#include <time.h>

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

// for profile
float **helper_matrix(int n, int m){
    float **A = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
    {
        A[i] = (float *)malloc(m * sizeof(float));
    }

    for(int i =0; i<n; i++){
        for (int j = 0; j<m; j++){
            A[i][j] = 1.0;
        }
    }
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
    int len = 10;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of mat 10: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_matmul_square_matrices_100(void){
    int len = 100;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of mat 100: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_matmul_square_matrices_500(void){
    int len = 500;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);

    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of mat 500: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_matmul_square_matrices_1000(void){
    int len = 2000;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of mat 1000: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_optimal_matmul_square_matrices_10(void){
    int len = 10;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul_blocking(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of opt_mat 10: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_optimal_matmul_square_matrices_100(void){
    int len = 100;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul_blocking(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of opt_mat 100: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_optimal_matmul_square_matrices_500(void){
    int len = 500;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul_blocking(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of opt_mat 500: %f \n", time_diff);

    cleanup(A, B, len, len);
}

void test_optimal_matmul_square_matrices_1000(void){
    int len = 2000;
    float **A = helper_matrix(len, len);
    float **B = helper_matrix(len, len);
    double time1, time_diff;
    time1 = (double) clock();
    time1 = time1 / CLOCKS_PER_SEC;
    float **C = matmul_blocking(A, B, len, len, len, len);
    time_diff = ((double) clock()) / CLOCKS_PER_SEC - time1;
    printf("runtime of opt_mat 1000: %f \n", time_diff);

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

    // test for Lab1 matrix
    float **C = matmul(A, B, 2, 3, 3, 1);
    TEST_ASSERT_EQUAL_FLOAT(C[0][0], 16.0);
    TEST_ASSERT_EQUAL_FLOAT(C[1][0], 24.0);

    // test for Lab2 matrix
    float **C_2 = matmul_blocking(A, B, 2, 3, 3, 1);
    TEST_ASSERT_EQUAL_FLOAT(C_2[0][0], 16.0);
    TEST_ASSERT_EQUAL_FLOAT(C_2[1][0], 24.0);

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

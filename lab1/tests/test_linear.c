#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_linear.h"

// for profiling
float **helper_weights(int n, int m){
    float **weights = (float **)malloc(n* sizeof(float *));
    for (int i = 0; i < n; i++)
    {
        weights[i] = (float *)malloc(m * sizeof(float));
    }
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            weights[i][j] = 1.0;
        }
    }
    return weights;
}

float *helper_array(int n){
    float *arr = (float *)malloc(n * sizeof(float));
    for(int i =0; i<n; i++){
        arr[i] = 1.0;
    }
    return arr;
}

void helper_cleanup_linear(float **weights, float *bias, float *inputs, int n){
    for (int i = 0; i<n; i++){
        free(weights[i]);
    }
    free(weights);
    free(bias);
    free(inputs);
}

void test_linear_10(void){
    int n = 10;
    int m = 10;

    float **weights = helper_weights(n, m);
    float *inputs = helper_array(n);
    float *bias = helper_array(m);
    float *output = linear(inputs, weights, bias, n, m);

    helper_cleanup_linear(weights, bias, inputs, n);
}

void test_linear_1000(void){
    int n = 1000;
    int m = 1000;

    float **weights = helper_weights(n, m);
    float *inputs = helper_array(n);
    float *bias = helper_array(m);
    float *output = linear(inputs, weights, bias, n, m);

    helper_cleanup_linear(weights, bias, inputs, n);
}

void test_linear_5000(void){
    int n = 5000;
    int m = 5000;

    float **weights = helper_weights(n, m);
    float *inputs = helper_array(n);
    float *bias = helper_array(m);
    float *output = linear(inputs, weights, bias, n, m);

    helper_cleanup_linear(weights, bias, inputs, n);
}


// for correctness
void test_linear(void){

    /**** YOUR CODE HERE ****/
    float **weights = helper_weights(3, 2);
    float *inputs = helper_array(3);
    float *bias = helper_array(2);

    // load data 
    weights[0][0] = 2;
    weights[0][1] = 1;
    weights[1][0] = 5;
    weights[1][1] = 3;
    weights[2][0] = 1;
    weights[2][1] = 0;

    inputs[0] = 2;
    inputs[1] = 4;
    inputs[2] = 1;

    bias[0] = 5;
    bias[1] = 6;

    float *output = linear(inputs, weights, bias, 3, 2);
    float expected_output[] = {30,20};
    for (int i = 0; i<2; i++){
        TEST_ASSERT_EQUAL_FLOAT(expected_output[i], output[i]);
    }

    helper_cleanup_linear(weights, bias, inputs, 3);
}

void test_linear_null(void){
    float **weights = helper_weights(3, 2);
    float *inputs = helper_array(0);
    float *bias = helper_array(2);

    float *output = linear(inputs, weights, bias, 0,2);
    UNITY_TEST_ASSERT_NULL(output, __LINE__, "Expected NULL!");
}
// Add more test cases as needed
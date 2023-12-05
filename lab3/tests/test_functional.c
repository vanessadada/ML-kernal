#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_functional.h"
#include <float.h>

// profile softmax
void helper_softmax_test_equal(float *input, float *output, int len){
    int maxInputIndex = 0;
    int maxOutputIndex = 0;

    for (int i = 1; i < len; i++) {
        if (input[i] > input[maxInputIndex]) {
            maxInputIndex = i;
        }
        if (output[i] > output[maxOutputIndex]) {
            maxOutputIndex = i;
        }
    }

    TEST_ASSERT_EQUAL_INT(maxInputIndex, maxOutputIndex);
}

float helper_softmax_sum(float *output, int len){
    float sum = 0.0;

    // Check that the sum of the output is 1 (because the output is softmax)
    for (int i = 0; i < len; i++) {
        sum += output[i];
    }
    return sum;
}

void helper_softmax_profile(int len){
    float input[len];
    for (int i = 0; i < len; i++){
        input[i] = 3.0;
    }
    float *output = softmax(input, len);
    float sum = helper_softmax_sum(output,len);
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 1.0, sum);
    helper_softmax_test_equal(input, output, len);

    // Cleanup
    free(output);
}

void test_softmax_10(void){
    helper_softmax_profile(10);
}

void test_softmax_100(void){
    helper_softmax_profile(100);
}

void test_softmax_400(void){
    helper_softmax_profile(400);
}

// test for correctness
void test_softmax(void) {
    float input[] = {1.0, 2.0, 3.0};
    float *output = softmax(input, 3);
    float sum = helper_softmax_sum(output,3);
    TEST_ASSERT_FLOAT_WITHIN(1e-6, 1.0, sum);
    helper_softmax_test_equal(input, output, 3);

    // Cleanup
    free(output);
}

// Test relu
// profile relu
void helper_test_relu(int len){
    float inputs[len];
    float expected_outputs[len];
    float num = 4.0;
    for(int i = 0; i< len; i++){
        inputs[i] = num;
        expected_outputs[i] = fmax(num, 0.0);
        num = -num;
    }
    int test_cases = sizeof(inputs)/sizeof(inputs[0]);

    for(int i = 0; i < test_cases; i++) {
        float output = relu(inputs[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expected_outputs[i], output);
    }
}

void test_relu_100(void) {
    helper_test_relu(100);
}

void test_relu_500(void) {
    helper_test_relu(500);
}

void test_relu_1000(void) {
    helper_test_relu(1000);
}

// test for correctness
void test_relu(void) {
    float inputs[] = {3.0f, 0.0f, -3.0f};
    float expected_outputs[] = {3.0f, 0.0f, 0.0f};
    int test_cases = sizeof(inputs)/sizeof(inputs[0]);

    for(int i = 0; i < test_cases; i++) {
        float output = relu(inputs[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-6, expected_outputs[i], output);
    }
}

// Add more test cases as needed

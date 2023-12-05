#include "unity/unity.h"
#include "test_conv.h"
#include "test_functional.h"
#include "test_linear.h"
#include "test_matrix_ops.h"

void setUp(void) {
    /* Code here will run before each test */
}

void tearDown(void) {
    /* Code here will run after each test */
}

int main(void) {
    UNITY_BEGIN();

    // Test conv
    // Test for correctness 
    RUN_TEST(test_conv);

    // for profile (no compare with expected)
    RUN_TEST(test_conv_10);
    RUN_TEST(test_conv_100);
    RUN_TEST(test_conv_500);

    // Test softmax
    // Test for correctness
    RUN_TEST(test_softmax);

    // for profile
    RUN_TEST(test_softmax_10);
    RUN_TEST(test_softmax_100);
    RUN_TEST(test_softmax_400);


    // Test relu
    // Test for correctness
    RUN_TEST(test_relu);

    // for profile
    RUN_TEST(test_relu_100);
    RUN_TEST(test_relu_500);
    RUN_TEST(test_relu_1000);

    // Test linear
    // test for correctness
    RUN_TEST(test_linear);
    RUN_TEST(test_linear_null);

    // for profile
    RUN_TEST(test_linear_10);
    RUN_TEST(test_linear_1000);
    RUN_TEST(test_linear_5000);

    // Test matrix_ops
    // test for correctness 
    RUN_TEST(test_matmul_square_matrices);
    RUN_TEST(test_matmul_incompatible_dimensions);

    // for profile
    RUN_TEST(test_matmul_square_matrices_10);
    RUN_TEST(test_matmul_square_matrices_100);
    RUN_TEST(test_matmul_square_matrices_500);


    return UNITY_END();
}

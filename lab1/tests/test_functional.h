#ifndef TEST_FUNCTIONAL_H
#define TEST_FUNCTIONAL_H

// correctness
void test_softmax(void);
// profile
void test_softmax_10(void);
void test_softmax_100(void);
void test_softmax_400(void);

// correctness
void test_relu(void);
// profile
void test_relu_100(void);
void test_relu_500(void);
void test_relu_1000(void);

#endif /* TEST_FUNCTIONAL_H */

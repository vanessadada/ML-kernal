#include "functional.h"

float relu(float x)
{
    /**** YOUR CODE HERE ****/
    if (x > 0.0) {
        return x;
    }
    return 0.0;
}


void applyRelu(float *input, int inputSize)
{
    for (int i = 0; i < inputSize; i++)
    {
        input[i] = relu(input[i]);
    }
}

float *softmax(float *input, int inputSize)
{
    float *softmaxOutput = malloc(inputSize * sizeof(*softmaxOutput));

    /**** YOUR CODE HERE ****/
    float exp_sum = 0.0;
    for (int i =0; i < inputSize; i++){
    	exp_sum += exp(input[i]);
    }
    
    for (int i = 0; i < inputSize; i++){
    	softmaxOutput[i] = exp(input[i])/exp_sum;
    }
    return softmaxOutput;
}

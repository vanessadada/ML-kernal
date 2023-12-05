#include "linear.h"

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
    // Check for empty input
    if (input == NULL || inputSize == 0 || outputSize == 0)
    {
    return NULL;
    }

    float *output = malloc(outputSize * sizeof(*output));

    /**** YOUR CODE HERE ****/
    for (int i = 0; i < outputSize; i++){
        output[i] = 0.0;
    }
    
    for (int j = 0; j < outputSize; j++)
    {
        for (int k = 0; k < inputSize; k++)
        {
            output[j] += input[k] * weights[k][j];
        }
        output[j] += biases[j];
    }
    return output;
}

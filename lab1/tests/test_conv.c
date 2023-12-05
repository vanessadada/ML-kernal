#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

// profiling
float ***helper_image(int numChannels, int inputSize){
    // memory 
    float ***image = (float ***)malloc(numChannels * sizeof(float **));
    for (int i = 0; i < numChannels; i++)
    {
        image[i] = (float **)malloc(inputSize * sizeof(float*));
        for (int j = 0; j < inputSize; j++){
            image[i][j] = (float*) malloc(inputSize * sizeof(float));
        }
    }

    // load data
    for (int i = 0; i< numChannels; i++){
        for (int j = 0; j <inputSize; j++){
            for (int k = 0; k <inputSize; k++){
                image[i][j][k] = 1.0;
            }
        }
    }
    return image;
}

float ****helper_kernel(int numFilters, int numChannels, int kernelSize){
    // memory
    float ****kernel = (float ****)malloc(numFilters * sizeof(float ***));
    for (int i = 0; i < numFilters; i++)
    {
        kernel[i] = (float ***)malloc(numChannels * sizeof(float **));
        for (int j = 0; j< numChannels; j++){
            kernel[i][j] = (float **)malloc(kernelSize * sizeof(float *));
            for (int k = 0; k < kernelSize; k++){
                kernel[i][j][k] = (float*)malloc(kernelSize * sizeof(float));
            }
        }
    }

    // load data
    for (int i = 0; i<numFilters; i++){
        for (int j = 0; j<numChannels; j++){
            for(int k = 0; k<kernelSize; k++){
                for(int l = 0; l < kernelSize; l++){
                    kernel[i][j][k][l] = 1.0;
                }
            }
        }
    }
    return kernel;
}

float *helper_bias(int outputSize){
    float *biasData = (float *)malloc(outputSize * sizeof(float));
    for (int i = 0; i<outputSize; i++){
        biasData[i] = 1.0;
    }
    return biasData;
}

void helper_cleanup(float ***image, float ****kernel, float *biasData, int numChannels, int inputSize, int numFilters, int kernelSize){
    for (int i = 0; i < numChannels; i++)
    {
        for (int j = 0; j< inputSize; j++){
            free(image[i][j]);
        }
        free(image[i]);
    }

    for (int i = 0; i < numFilters; i++){
        for (int j = 0; j<numChannels; j++){
            for(int k = 0; k<kernelSize; k++){
                free(kernel[i][j][k]);
            }
            free(kernel[i][j]);
        }
        free(kernel[i]);
    }
    
    free(image);
    free(kernel);
    free(biasData);
}

void test_conv_10(void){
    int numChannels = 5;
    int numFilters = 10;
    int inputSize = 5;
    int kernelSize = 3;
    int outputSize = inputSize - kernelSize + 1;

    float ***image = helper_image(numChannels, inputSize);
    float ****kernel = helper_kernel(numFilters, numChannels, kernelSize);
    float *biasData = helper_bias(outputSize);

    float ***conv = convolution(image, numChannels, kernel, biasData, numFilters, inputSize, kernelSize);
    helper_cleanup(image, kernel, biasData, numChannels, inputSize, numFilters, kernelSize);
}

void test_conv_100(void){
    int numChannels = 20;
    int numFilters = 100;
    int inputSize = 10;
    int kernelSize = 3;
    int outputSize = inputSize - kernelSize + 1;

    float ***image = helper_image(numChannels, inputSize);
    float ****kernel = helper_kernel(numFilters, numChannels, kernelSize);
    float *biasData = helper_bias(outputSize);

    float ***conv = convolution(image, numChannels, kernel, biasData, numFilters, inputSize, kernelSize);
    helper_cleanup(image, kernel, biasData, numChannels, inputSize, numFilters, kernelSize);
}

void test_conv_500(void){
    int numChannels = 100;
    int numFilters = 500;
    int inputSize = 25;
    int kernelSize = 5;
    int outputSize = inputSize - kernelSize + 1;

    float ***image = helper_image(numChannels, inputSize);
    float ****kernel = helper_kernel(numFilters, numChannels, kernelSize);
    float *biasData = helper_bias(outputSize);

    float ***conv = convolution(image, numChannels, kernel, biasData, numFilters, inputSize, kernelSize);
    helper_cleanup(image, kernel, biasData, numChannels, inputSize, numFilters, kernelSize);
}

// test correctness
void test_conv(void)
{
    // Setup memory
    int numChannels = 2;
    int numFilters = 1;
    int inputSize = 4;
    int kernelSize = 2;
    int outputSize = inputSize - kernelSize + 1;

    float ***image = helper_image(numChannels, inputSize);
    float ****kernel = helper_kernel(numFilters, numChannels, kernelSize);
    float *biasData = helper_bias(outputSize);
    
    // replace data (test data given in the lab 1)
    float num = 0.0;
    for(int j = 0; j<4; j++){
        for(int k = 0; k<4; k++){
            image[0][j][k] = num;
            num += 1.0;
        }
    }

    num = 1.0;
    for(int i = 0; i<4; i++){
        for(int j = 0; j<3; j+=2){
            image[1][i][j] = num;
            image[1][i][j+1] = num;
            num += 2.0;
        }
    }

    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            kernel[0][0][i][j] = 1.0;
        }
    }

    for(int i = 0; i<2; i++){
        for(int j = 0; j<2; j++){
            kernel[0][1][i][j] = 2.0;
        }
    }

    biasData[0] = 2.0;
    float expected_conv[3][3] = {{36,48,60}, {84,96, 108}, {132,144,156}};
    float ***conv = convolution(image, numChannels, kernel, biasData, numFilters, inputSize, kernelSize);
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            TEST_ASSERT_EQUAL_FLOAT(expected_conv[i][j], conv[0][i][j]);
        }
    }

    helper_cleanup(image, kernel, biasData, numChannels, inputSize, numFilters, kernelSize);
}



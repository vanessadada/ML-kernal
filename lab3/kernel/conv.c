#include "conv.h"

// Basic convolution operation
float ***convolution(float ***image, int numChannels, float ****kernel, float *biasData, int numFilters, int inputSize, int kernelSize)
{
    int outputSize = inputSize - kernelSize + 1;

    // Allocate memory for the convolution output
    float ***convOutput = malloc(numFilters * sizeof(*convOutput));
    for (int i = 0; i < numFilters; i++)
    {
        convOutput[i] = malloc(outputSize * sizeof(*convOutput[i]));
        for (int j = 0; j < outputSize; j++)
        {
            convOutput[i][j] = malloc(outputSize * sizeof(*convOutput[i][j]));
        }
    }

    // Perform the convolution operation
    /**** YOUR CODE HERE ****/

	// initialize
	for (int i = 0; i < numFilters; i++){
		for (int j = 0; j < outputSize; j++){
			for (int k = 0; k < outputSize; k++){
				convOutput[i][j][k] = 0.0;
			}
		}
	}

    for (int i = 0; i < numFilters; i++){
    	for (int j = 0; j < numChannels; j++){
			float **cur_img = image[j];
			float **cur_filter = kernel[i][j];
			// cal one image channel with one filter
			for (int k = 0; k < outputSize; k++)
			{
				for(int l = 0; l < outputSize; l++)
				{
					float sum = 0.0;
					for (int a = 0; a < kernelSize; a++)
					{
						for (int b = 0; b < kernelSize; b++)
						{	
							sum += cur_filter[a][b] * cur_img[k+a][l+b];
						}
					}
				convOutput[i][k][l] += sum;
				}	
			}
		}

		for (int k = 0; k < outputSize; k++)
		{
			for (int l = 0; l < outputSize; l++)
			{
				convOutput[i][k][l] += biasData[i];
			}
			applyRelu(convOutput[i][k], outputSize);
		}
    }

    return convOutput;
}

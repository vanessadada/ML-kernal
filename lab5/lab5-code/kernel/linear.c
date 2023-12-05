#include "linear.h"
#include <immintrin.h>

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize)
{
  // Check for empty input
  if (input == NULL || inputSize == 0 || outputSize == 0)
  {
    return NULL;
  }

  float *output = malloc(outputSize * sizeof(*output));

  for (int i = 0; i < outputSize; i++)
  {
    output[i] = biases[i];
    for (int j = 0; j < inputSize; j++)
    {
      output[i] += weights[i][j] * input[j];
    }
  }

  return output;
}

float reduce_avx(__m256 vec) {
    __m128 lo = _mm256_extractf128_ps(vec, 0);
    __m128 hi = _mm256_extractf128_ps(vec, 1);

    __m128 sum1 = _mm_add_ps(lo, hi);
    __m128 sum2 = _mm_add_ps(sum1, _mm_shuffle_ps(sum1, sum1, 0x0E));
    __m128 sum3 = _mm_add_ps(sum2, _mm_shuffle_ps(sum2, sum2, 0x01));

    float result;
    _mm_store_ss(&result, sum3);
    return result;
}

float *simd_linear(float *input, float **weights, float *biases, int inputSize, int outputSize){
  // Check for empty input
  if (input == NULL || inputSize == 0 || outputSize == 0)
  {
    return NULL;
  }

  float *output = malloc(outputSize * sizeof(*output));

    for (int i = 0; i < outputSize; i++) {
        __m256 sum = _mm256_setzero_ps();

        for (int j = 0; j < inputSize; j += 8) {
            __m256 inputVector = _mm256_loadu_ps(&input[j]);
            __m256 weightVector = _mm256_loadu_ps(&weights[i][j]);
            __m256 product = _mm256_mul_ps(weightVector, inputVector);
            sum = _mm256_add_ps(sum, product);
        }

        float reducedSum = reduce_avx(sum);

        output[i] = biases[i] + reducedSum;
    }
    return output;
}

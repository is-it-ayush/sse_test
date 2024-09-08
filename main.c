#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <xmmintrin.h>

#ifndef ITERATION_COUNT
#define ITERATION_COUNT 100000000;
#endif

/// @brief Calculate the average cycle taken by the operation
/// over ITERATION_COUNT (default 100000000) iterations.
uint64_t average_cycle_taken(void operation()) {
  int iteration = ITERATION_COUNT;
  uint64_t start = __rdtsc();
  for (int i = 0; i <= iteration; ++i) {
    operation();
  }
  uint64_t end = __rdtsc();
  return ((end - start) / iteration);
}

// data to be used in the sse operation
// it'll be aligned to 16 bytes before
// running the sse operations. i'm doing
// it in global scope to prevent overhead.
float *data;

// SSE Add vs Scaler Add
void sse_add() { __m128 s = _mm_add_ps(_mm_load_ps(data), _mm_load_ps(data)); }
void scaler_add() {
  float data[4] = {1.0, 2.0, 3.0, 4.0};
  for (int i = 0; i < 4; ++i) {
    data[i] + data[i];
  }
}

// SSE Multiply vs Scaler Multiply
void sse_multiply() {
  __m128 s = _mm_mul_ps(_mm_load_ps(data), _mm_load_ps(data));
}
void scaler_multiply() {
  float data[4] = {1.0, 2.0, 3.0, 4.0};
  for (int i = 0; i < 4; ++i) {
    data[i] * data[i];
  }
}

int main() {
  // setup sse registers
  data = aligned_alloc(16, 4 * sizeof(float));
  data[0] = 1.0;
  data[1] = 2.0;
  data[2] = 3.0;
  data[3] = 4.0;

  // add operations
  uint64_t sse_add_cycles = average_cycle_taken(&sse_add);
  uint64_t normal_add_cycles = average_cycle_taken(&scaler_add);
  printf("[Add] Scaler Cycles: %ld  | SSE Cycles: %ld \n", normal_add_cycles,
         sse_add_cycles);

  // mult operations
  uint64_t sse_mul_cycles = average_cycle_taken(&sse_multiply);
  uint64_t normal_mul_cycles = average_cycle_taken(&scaler_multiply);
  printf("[Multiply] Scaler Cycles: %ld  | SSE Cycles: %ld \n",
         normal_mul_cycles, sse_mul_cycles);

  return 0;
}

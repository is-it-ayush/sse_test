#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <xmmintrin.h>

#ifndef ITERATION_COUNT
#define ITERATION_COUNT 100000000;
#endif

uint64_t average_cycle_taken(void operation()) {
  int iteration = ITERATION_COUNT;
  uint64_t start = __rdtsc();
  for (int i = 0; i <= iteration; ++i) {
    operation();
  }
  uint64_t end = __rdtsc();
  return ((end - start) / iteration);
}

void packed_add() {
  float *data = aligned_alloc(16, 16);
  data[0] = 1.0;
  data[1] = 2.0;
  data[2] = 3.0;
  data[3] = 4.0;

  __m128 s = _mm_add_ps(_mm_load_ps(data), _mm_load_ps(data));

  float r[4];
  _mm_store_ps(r, s);

  free(data);
}

int main() {
  uint64_t cycles = average_cycle_taken(&packed_add);

  printf("Clock Cycles: %ld \n", cycles);
  return 0;
}

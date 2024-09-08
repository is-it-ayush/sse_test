#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <x86intrin.h>

int main() {
  float *data = aligned_alloc(16, 16);
  data[0] = 1.0;
  data[1] = 2.0;
  data[2] = 3.0;
  data[3] = 4.0;

  int iteration = 100000000;
  uint64_t start = __rdtsc();
  for (int i = 0; i <= iteration; ++i) {
    __m128 a = _mm_load_ps(data);
    __m128 b = _mm_load_ps(data);
    __m128 s = _mm_add_ps(a, b);
  }
  uint64_t end = __rdtsc();

  // float r[4];
  // _mm_store_ps(r, s);
  //
  printf("Clock Cycles: %lu \n", ((end - start) / iteration));
  // printf("%f %f %f %f", r[0], r[1], r[2], r[3]);

  free(data);
  return 0;
}

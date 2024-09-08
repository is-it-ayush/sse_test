#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmmintrin.h>


int main() {
  float *data = aligned_alloc(16, 16);
  data[0] = 1.0;
  data[1] = 2.0;
  data[2] = 3.0;
  data[3] = 4.0;

  struct timespec start, end;
  int iteration = 100000000;
  clock_gettime(1, &start);
  for (int i = 0; i <= iteration; ++i) {
    __m128 a = _mm_load_ps(data);
    __m128 b = _mm_load_ps(data);
    __m128 s = _mm_add_ps(a, b);
  }
  clock_gettime(1, &end);

  // float r[4];
  // _mm_store_ps(r, s);
  //
  double et = ((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec);

  printf("Clock Cycles: %f | Elapsed Time: %f \n", ((et / iteration) * 3.5), et);
  // printf("%f %f %f %f", r[0], r[1], r[2], r[3]);

  free(data);
  return 0;
}

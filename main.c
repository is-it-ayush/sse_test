#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <x86intrin.h>
#include <xmmintrin.h>

const long ITERATION_COUNT = 1000000000;

// SSE Add vs Scaler Add
__m128 sse_add(float *data) {
  __m128 s = _mm_add_ps(_mm_load_ps(data), _mm_load_ps(data));
  return s;
}
void scaler_add(float *data) {
  for (int i = 0; i < 4; ++i) {
    data[i] = data[i] + data[i];
  }
}

// Function to measure time using clock_gettime()
struct timespec diff(struct timespec start, struct timespec end) {
  struct timespec temp;
  if ((end.tv_nsec - start.tv_nsec) < 0) {
    temp.tv_sec = end.tv_sec - start.tv_sec - 1;
    temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;
  }
  return temp;
}

int main() {
  struct timespec start, end;
  double scaler_add_time, sse_add_time;

  // Measure scaler add
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < ITERATION_COUNT; ++i) {
    float scaler_data[4] = {1.0, 2.0, 3.0, 4.0};
    scaler_add(scaler_data);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  struct timespec diff_scaler = diff(start, end);
  scaler_add_time = diff_scaler.tv_sec + (diff_scaler.tv_nsec / 1e9);

  // Measure SSE add
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < ITERATION_COUNT; ++i) {
    float *sse_data = (float *)aligned_alloc(16, 4 * sizeof(float));
    sse_data[0] = 1.0;
    sse_data[1] = 2.0;
    sse_data[2] = 3.0;
    sse_data[3] = 4.0;
    sse_add(sse_data);
    free(sse_data);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  struct timespec diff_sse = diff(start, end);
  sse_add_time = diff_sse.tv_sec + (diff_sse.tv_nsec / 1e9);

  printf("[Add] Scaler: %.12f seconds  | SSE: %.12f seconds\n", scaler_add_time, sse_add_time);

  return 0;
}

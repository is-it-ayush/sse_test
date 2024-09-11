a small playground for testing streaming SIMD extension operations.
run via `make clean && make && ./main`.

# benchmarks

```bash
# Iterations
The seconds are avearaged over 100_000_000 test runs.

------------------------------------------------------------------
# Operations
__m128 sse_add(float *data) {
  __m128 s = _mm_add_ps(_mm_load_ps(data), _mm_load_ps(data));
  return s;
}
void scaler_add(float *data) {
  for (int i = 0; i < 4; ++i) {
    data[i] = data[i] + data[i];
  }
}

------------------------------------------------------------------
# Results

# Optimization Size [-Os; similar to -O2]
[Add] Scaler: 3.875673527000 seconds  | SSE: 0.000000032000 seconds
# Optimization Speed [-Ofast; similar to -O3]
[Add] Scaler: 0.000000058000 seconds  | SSE: 0.000000028000 seconds
# Optimization Level 3 [-O3]
[Add] Scaler: 0.000000060000 seconds  | SSE: 0.000000030000 seconds
```

# license.

MIT! [You can read here](./LICENSE.md).

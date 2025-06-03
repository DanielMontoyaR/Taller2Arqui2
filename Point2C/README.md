# `__m128i _mm_cmpequal_epi8(__m128i vector_x, __m128i vector_y)`

## Synopsis

```c
__m128i _mm_cmpequal_epi8(__m128i vector_x, __m128i vector_y)
```

## Description
This intrinsic compares two 128-bit vectors (vector_x and vector_y) element by element, interpreting each of its 16 elements as 8-bit integers.
Each position in the result will have 0xFF if the values ​​at that position are equal in both vectors, or 0x00 if they are different.

## Operation
```
FOR i := 0 to 15:
    i := j*8
	result[i+7:i] := (vector_x[i+7:i] == vector_y[i+7:i]) ? 0xFF : 0x00
ENDFOR
```
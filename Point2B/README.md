# `__m128i _mm_replicate_epi8 (char char_x)`

## Synopsis

```c
__m128i _mm_replicate_epi8 (char char_x)
```

## Description
Replicates an 8-bit integer char_x to all elements of the destination vector (vector_x).

## Operation
```
FOR j := 0 to 15
    i := j*8
    vector_x[i+7:i] := char_x[7:0]
ENDFOR
```
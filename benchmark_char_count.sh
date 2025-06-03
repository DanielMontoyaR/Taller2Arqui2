#!/bin/bash
# Grant execution permissions: chmod +x benchmark_char_count.sh
# Run: ./benchmark_char_count.sh

# Compilation parameters
SERIAL_SRC="char_count_serial.cpp"
SIMD_SRC="char_count_simd.cpp"
SERIAL_BIN="char_count_serial"
SIMD_BIN="char_count_simd"

# Compilation
g++ -std=c++17 "$SERIAL_SRC" -o "$SERIAL_BIN"
g++ -std=c++17 -O3 -mavx2 "$SIMD_SRC" -o "$SIMD_BIN"

# Output CSV files
SERIAL_CSV="results_serial.csv"
SIMD_CSV="results_simd.csv"

# CSV headers
echo "size_bytes,alignment,exec_time_us,memory_kb,char_count" > "$SERIAL_CSV"
echo "size_bytes,alignment,exec_time_us,memory_kb,char_count" > "$SIMD_CSV"

# Test ranges
ALIGNMENTS=(16 64)
SIZES=$(python3 -c 'import numpy as np; print(" ".join(map(str, np.linspace(1024, 100 * 1024, num=50, dtype=int))))')

# Target character and fixed seed
TARGET_CHAR=";"
SEED=42

echo "Running benchmarks..."
for ALIGN in "${ALIGNMENTS[@]}"; do
  for SIZE in $SIZES; do
    echo "Testing size=$SIZE, alignment=$ALIGN"

    # Run serial version
    SERIAL_OUT=$("./$SERIAL_BIN" "$SIZE" "$ALIGN" "$TARGET_CHAR" "$SEED")
    SERIAL_TIME=$(echo "$SERIAL_OUT" | grep "Execution time" | awk '{print $3}')
    SERIAL_MEM=$(echo "$SERIAL_OUT" | grep "Memory used" | awk '{print $4}')
    SERIAL_COUNT=$(echo "$SERIAL_OUT" | grep "Character" | awk '{print $4}')
    echo "$SIZE,$ALIGN,$SERIAL_TIME,$SERIAL_MEM,$SERIAL_COUNT" >> "$SERIAL_CSV"

    # Run SIMD version
    SIMD_OUT=$("./$SIMD_BIN" "$SIZE" "$ALIGN" "$TARGET_CHAR" "$SEED")
    SIMD_TIME=$(echo "$SIMD_OUT" | grep "Execution time" | awk '{print $3}')
    SIMD_MEM=$(echo "$SIMD_OUT" | grep "Memory used" | awk '{print $4}')
    SIMD_COUNT=$(echo "$SIMD_OUT" | grep "Character" | awk '{print $4}')
    echo "$SIZE,$ALIGN,$SIMD_TIME,$SIMD_MEM,$SIMD_COUNT" >> "$SIMD_CSV"
  done
done

echo "Benchmark completed. Results saved to:"
echo "- $SERIAL_CSV"
echo "- $SIMD_CSV"

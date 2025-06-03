# Workshop 2: SIMD Extensions and Intrinsics

This project corresponds to the second workshop for the course **CE4302 – Computer Architecture II** at the Instituto Tecnológico de Costa Rica. The main goal is to implement and compare a character counting algorithm in C++ using two approaches: a **serial version** and an optimized one using **SIMD intrinsics** (SSE2).

## Main Files

- `char_count_serial.cpp`: Serial implementation of the character counting algorithm.
- `char_count_simd.cpp`: SIMD-optimized version using intrinsics (SSE2).
- `benchmark_char_count.sh`: Script to compile, run benchmarks with multiple configurations, and export results to CSV.
- `plot_benchmark_results.py`: Python script to visualize execution time based on collected data.

## Requirements

- A C++ compiler with C++17 support (`g++`)
- A CPU with SSE2 SIMD instruction support
- Python 3 with `matplotlib` and `pandas`:

  ```bash
  pip install matplotlib pandas
  ```

## Usage

### 1. Run Benchmarks

Grant permissions and execute the benchmarking script:

```bash
chmod +x benchmark_char_count.sh
./benchmark_char_count.sh
```

This will generate two CSV files with execution time, memory usage, and character count:
- `results_serial.csv`
- `results_simd.csv`

### 2. Generate Plots

```bash
python3 plot_benchmark_results.py
```

The script will display and save performance graphs for both implementations under different data alignment values (16B and 64B).

## SIMD Code Validation

The SIMD code was validated using **Compiler Explorer**, comparing the generated assembly from the manually written intrinsics and the version translated using an LLM.

🔗 [View SIMD Code in Compiler Explorer](https://godbolt.org/z/7T6aos7PE)

## Authors

- Emanuel Marín Gutiérrez
- Daniel Montoya Rivera

Group 2 – I Semester 2025
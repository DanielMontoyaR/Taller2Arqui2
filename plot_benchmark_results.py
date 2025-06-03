# Install the necessary libraries: pip install matplotlib pandas
# Run: python3 plot_benchmark_results.py

import pandas as pd
import matplotlib.pyplot as plt

# Read data
serial_df = pd.read_csv("results_serial.csv")
simd_df = pd.read_csv("results_simd.csv")

# Convert units
serial_df['size_KB'] = serial_df['size_bytes'] / 1024.0  # KB
simd_df['size_KB'] = simd_df['size_bytes'] / 1024.0  # KB

for alignment in serial_df['alignment'].unique():
    s_data = serial_df[serial_df['alignment'] == alignment]
    v_data = simd_df[simd_df['alignment'] == alignment]

    fig, ax = plt.subplots(figsize=(10, 6))
    ax.plot(s_data['size_KB'], s_data['exec_time_us'], label=f"Serial ({alignment}B)", marker='o')
    ax.plot(v_data['size_KB'], v_data['exec_time_us'], label=f"SIMD ({alignment}B)", marker='x')
    ax.set_xlabel("Input Size (KB)")
    ax.set_ylabel('Execution Time (us)')
    ax.set_title(f'Execution Time vs Input Size (Alignment {alignment} bytes)')
    ax.legend()
    ax.grid(True, which="both", ls="--", linewidth=0.5)
    fig.tight_layout()
    fig.savefig(f"exec_time_alignment_{alignment}.png")

# Display the plots
plt.show()

print("Plots generated and displayed.")
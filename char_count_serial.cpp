// Compile: g++ -std=c++17 char_count_serial.cpp -o char_count_serial
// Run:     ./char_count_serial <str_length> <alignment> <char_x> <seed>
// OR:      ./char_count_serial --string "<input_string>" <char_x>

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <random>
#include <fstream>
#include <string>

// Global pseudo-random number generator (Mersenne Twister) for reproducible results
std::mt19937 generator;

// Generates a random character from a fixed ASCII set
// Includes letters, digits, and punctuation for more realistic workloads
char random_char() {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%&*;:'\",.?/\\|";
    static const size_t charset_size = sizeof(charset) - 1;
    static thread_local std::uniform_int_distribution<> dist(0, charset_size - 1);
    return charset[dist(generator)];
}

// Allocates and fills an aligned buffer with random characters
// Pads memory with zeros if total size is not a multiple of the alignment
char* generate_aligned_random_string(size_t length, size_t alignment) {
    size_t total_size = length;
    if (total_size % alignment != 0)
        total_size += alignment - (total_size % alignment);

    char* buffer = reinterpret_cast<char*>(std::aligned_alloc(alignment, total_size));
    if (!buffer) {
        std::cerr << "Memory allocation failed.\n";
        return nullptr;
    }

    // Fill the actual data portion with random characters
    for (size_t i = 0; i < length; ++i) {
        buffer[i] = random_char();
    }

    // Optional: zero out any padding beyond actual data
    std::memset(buffer + length, 0, total_size - length);
    return buffer;
}

// Counts occurrences of a character in a raw buffer of known length
size_t count_char_serial(const char* str, size_t length, char char_x) {
    size_t count = 0;
    for (size_t i = 0; i < length; ++i) {
        if (str[i] == char_x)
            ++count;
    }
    return count;
}

// Counts occurrences of a character in a null-terminated string
size_t count_char_serial(const char* str, char char_x) {
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == char_x)
            ++count;
    }
    return count;
}

// Reads the resident set size (RAM usage) in kilobytes from /proc/self/status (Linux-only)
size_t get_memory_usage_kb() {
    std::ifstream status_file("/proc/self/status");
    std::string line;
    while (std::getline(status_file, line)) {
        if (line.rfind("VmRSS:", 0) == 0) {
            size_t value_kb;
            sscanf(line.c_str(), "VmRSS: %zu kB", &value_kb);
            return value_kb;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    // Support two modes:
    // 1) Generate aligned random string (length, alignment, target char, seed)
    // 2) Use user-provided string (--string "<str>" char_x)
    if (argc != 5 && !(argc == 4 && std::string(argv[1]) == "--string")) {
        std::cerr << "Usage modes:\n";
        std::cerr << "1. " << argv[0] << " <str_length> <alignment> <char_x> <seed>\n";
        std::cerr << "2. " << argv[0] << " --string \"<input_string>\" <char_x>\n";
        return 1;
    }

    char char_x;
    size_t count_total = 0;

    // Record memory usage before processing
    size_t mem_before = get_memory_usage_kb();

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    if (argc == 5) {
        // Mode 1: random string generation path
        size_t length     = std::stoul(argv[1]);
        size_t alignment  = std::stoul(argv[2]);
        char_x            = argv[3][0];
        unsigned int seed = static_cast<unsigned int>(std::stoul(argv[4]));

        generator.seed(seed); // Ensure reproducibility

        char* str = generate_aligned_random_string(length, alignment);
        if (!str) return 1;

        // Truncate output preview to 100 characters
        std::cout << "Generated string (first 100 chars):\n";
        for (size_t i = 0; i < std::min(length, size_t(100)); ++i) {
            std::cout << str[i];
        }
        if (length > 100) std::cout << "...";
        std::cout << std::endl;

        // Count occurrences using raw buffer version
        count_total = count_char_serial(str, length, char_x);

        std::free(str); // Free allocated memory
    } else {
        // Mode 2: user-supplied string
        const char* str = argv[2];
        char_x = argv[3][0];

        std::cout << "Input string (first 100 chars):\n";
        for (size_t i = 0; i < std::min(strlen(str), size_t(100)); ++i) {
            std::cout << str[i];
        }
        if (strlen(str) > 100) std::cout << "...";
        std::cout << std::endl;

        // Count occurrences using null-terminated version
        count_total = count_char_serial(str, char_x);
    }

    // Measure end time and memory after execution
    auto end = std::chrono::high_resolution_clock::now();
    size_t mem_after = get_memory_usage_kb();

    std::chrono::duration<double, std::micro> exec_time = end - start;

    // Final report
    std::cout << "\nCharacter '" << char_x << "' found " << count_total << " times.\n";
    std::cout << "Execution time: " << exec_time.count() << " microseconds\n";
    std::cout << "Memory used (VmRSS): " << (mem_after - mem_before) << " KB\n";

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

// Include optimized functions (simplified versions for benchmarking)
inline long long fastModularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Naive modular exponentiation (original implementation)
long long naiveModularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    for (long long i = 0; i < exp; i++) {
        result = (result * base) % mod;
    }
    return result;
}

// Optimized string operations
string optimizedStringConcat(const vector<string>& strings) {
    size_t total_size = 0;
    for (const auto& s : strings) {
        total_size += s.size();
    }
    
    string result;
    result.reserve(total_size);
    
    for (const auto& s : strings) {
        result += s;
    }
    return result;
}

// Naive string concatenation
string naiveStringConcat(const vector<string>& strings) {
    string result = "";
    for (const auto& s : strings) {
        result += s;
    }
    return result;
}

// Optimized vector operations
vector<int> optimizedVectorOperations(int size) {
    vector<int> vec;
    vec.reserve(size);
    
    for (int i = 0; i < size; ++i) {
        vec.push_back(i);
    }
    return vec;
}

// Naive vector operations
vector<int> naiveVectorOperations(int size) {
    vector<int> vec;
    for (int i = 0; i < size; ++i) {
        vec.push_back(i);
    }
    return vec;
}

// Performance measurement utility
class BenchmarkTimer {
private:
    high_resolution_clock::time_point start_time;
    vector<double> measurements;
    
public:
    void start() {
        start_time = high_resolution_clock::now();
    }
    
    double stop() {
        auto end_time = high_resolution_clock::now();
        double elapsed = duration_cast<microseconds>(end_time - start_time).count() / 1000.0;
        measurements.push_back(elapsed);
        return elapsed;
    }
    
    double getAverage() const {
        if (measurements.empty()) return 0;
        double sum = 0;
        for (double m : measurements) sum += m;
        return sum / measurements.size();
    }
    
    double getMin() const {
        if (measurements.empty()) return 0;
        return *min_element(measurements.begin(), measurements.end());
    }
    
    double getMax() const {
        if (measurements.empty()) return 0;
        return *max_element(measurements.begin(), measurements.end());
    }
    
    void clear() {
        measurements.clear();
    }
};

// Test data generator
class TestDataGenerator {
private:
    mt19937 gen;
    
public:
    TestDataGenerator() : gen(random_device{}()) {}
    
    string generateRandomString(size_t length) {
        uniform_int_distribution<int> dist(32, 126); // Printable ASCII
        string result;
        result.reserve(length);
        
        for (size_t i = 0; i < length; ++i) {
            result.push_back(static_cast<char>(dist(gen)));
        }
        return result;
    }
    
    vector<string> generateStringVector(size_t count, size_t string_length) {
        vector<string> result;
        result.reserve(count);
        
        for (size_t i = 0; i < count; ++i) {
            result.push_back(generateRandomString(string_length));
        }
        return result;
    }
    
    long long generateRandomNumber(long long min_val, long long max_val) {
        uniform_int_distribution<long long> dist(min_val, max_val);
        return dist(gen);
    }
};

// Benchmark result struct
struct BenchmarkResult {
    string test_name;
    double original_time;
    double optimized_time;
    double improvement_factor;
    double improvement_percent;
    
    BenchmarkResult(const string& name, double orig, double opt) 
        : test_name(name), original_time(orig), optimized_time(opt) {
        improvement_factor = (opt > 0) ? orig / opt : 0;
        improvement_percent = (opt > 0) ? ((orig - opt) / orig) * 100 : 0;
    }
};

// Main benchmark class
class CryptographyBenchmark {
private:
    TestDataGenerator generator;
    vector<BenchmarkResult> results;
    
    void printHeader() {
        cout << "\n" << string(80, '=') << endl;
        cout << "         CRYPTOGRAPHY SYSTEM PERFORMANCE BENCHMARK" << endl;
        cout << string(80, '=') << endl;
    }
    
    void printResult(const BenchmarkResult& result) {
        cout << left << setw(30) << result.test_name;
        cout << right << setw(12) << fixed << setprecision(3) << result.original_time << " ms";
        cout << right << setw(12) << fixed << setprecision(3) << result.optimized_time << " ms";
        cout << right << setw(10) << fixed << setprecision(2) << result.improvement_factor << "x";
        cout << right << setw(10) << fixed << setprecision(1) << result.improvement_percent << "%";
        cout << endl;
    }
    
    void printSummary() {
        cout << "\n" << string(80, '-') << endl;
        cout << "PERFORMANCE SUMMARY:" << endl;
        cout << string(80, '-') << endl;
        
        double total_original = 0, total_optimized = 0;
        double max_improvement = 0;
        string best_test;
        
        for (const auto& result : results) {
            total_original += result.original_time;
            total_optimized += result.optimized_time;
            
            if (result.improvement_factor > max_improvement) {
                max_improvement = result.improvement_factor;
                best_test = result.test_name;
            }
        }
        
        double overall_improvement = (total_optimized > 0) ? total_original / total_optimized : 0;
        double overall_percent = (total_optimized > 0) ? ((total_original - total_optimized) / total_original) * 100 : 0;
        
        cout << "Total execution time (original): " << fixed << setprecision(3) << total_original << " ms" << endl;
        cout << "Total execution time (optimized): " << fixed << setprecision(3) << total_optimized << " ms" << endl;
        cout << "Overall performance improvement: " << fixed << setprecision(2) << overall_improvement << "x (" 
             << setprecision(1) << overall_percent << "%)" << endl;
        cout << "Best single improvement: " << fixed << setprecision(2) << max_improvement << "x in " << best_test << endl;
        
        cout << "\nTime saved: " << fixed << setprecision(3) << (total_original - total_optimized) << " ms" << endl;
    }
    
public:
    void runModularExponentiationBenchmark() {
        cout << "\n1. Testing Modular Exponentiation..." << endl;
        
        BenchmarkTimer timer;
        const int iterations = 1000;
        
        // Test with various exponent sizes
        vector<pair<long long, long long>> test_cases = {
            {123, 456},      // Small exponent
            {789, 1000},     // Medium exponent  
            {555, 2000},     // Large exponent
            {333, 5000}      // Very large exponent
        };
        
        for (const auto& test_case : test_cases) {
            long long base = test_case.first;
            long long exp = test_case.second;
            long long mod = 1000000007;
            
            // Benchmark original (naive) implementation
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                naiveModularExponentiation(base, exp, mod);
                timer.stop();
            }
            double naive_time = timer.getAverage();
            
            // Benchmark optimized implementation
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                fastModularExponentiation(base, exp, mod);
                timer.stop();
            }
            double optimized_time = timer.getAverage();
            
            string test_name = "ModExp (exp=" + to_string(exp) + ")";
            results.emplace_back(test_name, naive_time, optimized_time);
        }
    }
    
    void runStringBenchmark() {
        cout << "2. Testing String Operations..." << endl;
        
        BenchmarkTimer timer;
        const int iterations = 100;
        
        // Test with various string sizes
        vector<int> sizes = {100, 500, 1000, 5000};
        
        for (int size : sizes) {
            auto test_strings = generator.generateStringVector(size, 10);
            
            // Benchmark naive string concatenation
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                naiveStringConcat(test_strings);
                timer.stop();
            }
            double naive_time = timer.getAverage();
            
            // Benchmark optimized string concatenation
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                optimizedStringConcat(test_strings);
                timer.stop();
            }
            double optimized_time = timer.getAverage();
            
            string test_name = "String Concat (n=" + to_string(size) + ")";
            results.emplace_back(test_name, naive_time, optimized_time);
        }
    }
    
    void runVectorBenchmark() {
        cout << "3. Testing Vector Operations..." << endl;
        
        BenchmarkTimer timer;
        const int iterations = 100;
        
        // Test with various vector sizes
        vector<int> sizes = {1000, 5000, 10000, 50000};
        
        for (int size : sizes) {
            // Benchmark naive vector operations
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                auto vec = naiveVectorOperations(size);
                timer.stop();
            }
            double naive_time = timer.getAverage();
            
            // Benchmark optimized vector operations
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                auto vec = optimizedVectorOperations(size);
                timer.stop();
            }
            double optimized_time = timer.getAverage();
            
            string test_name = "Vector Ops (n=" + to_string(size) + ")";
            results.emplace_back(test_name, naive_time, optimized_time);
        }
    }
    
    void runMemoryUsageBenchmark() {
        cout << "4. Testing Memory Usage..." << endl;
        
        // Simulate memory-intensive operations
        BenchmarkTimer timer;
        const int iterations = 50;
        
        // Test memory allocation patterns
        vector<int> sizes = {1000, 10000, 100000};
        
        for (int size : sizes) {
            // Test without reserve
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                vector<string> vec;
                for (int j = 0; j < size; ++j) {
                    vec.push_back(to_string(j));
                }
                timer.stop();
            }
            double naive_time = timer.getAverage();
            
            // Test with reserve
            timer.clear();
            for (int i = 0; i < iterations; ++i) {
                timer.start();
                vector<string> vec;
                vec.reserve(size);
                for (int j = 0; j < size; ++j) {
                    vec.push_back(to_string(j));
                }
                timer.stop();
            }
            double optimized_time = timer.getAverage();
            
            string test_name = "Memory Alloc (n=" + to_string(size) + ")";
            results.emplace_back(test_name, naive_time, optimized_time);
        }
    }
    
    void runCipherBenchmark() {
        cout << "5. Testing Cipher Operations..." << endl;
        
        BenchmarkTimer timer;
        const int iterations = 1000;
        
        // Generate test data
        string test_data = generator.generateRandomString(1000);
        
        // Caesar cipher benchmark
        timer.clear();
        for (int i = 0; i < iterations; ++i) {
            timer.start();
            string result = "";
            for (char c : test_data) {
                if (isalpha(c)) {
                    char base = islower(c) ? 'a' : 'A';
                    result += (c - base + 13) % 26 + base;
                } else {
                    result += c;
                }
            }
            timer.stop();
        }
        double naive_time = timer.getAverage();
        
        // Optimized Caesar cipher
        timer.clear();
        for (int i = 0; i < iterations; ++i) {
            timer.start();
            string result;
            result.reserve(test_data.size());
            for (char c : test_data) {
                if (isalpha(c)) {
                    char base = islower(c) ? 'a' : 'A';
                    result.push_back((c - base + 13) % 26 + base);
                } else {
                    result.push_back(c);
                }
            }
            timer.stop();
        }
        double optimized_time = timer.getAverage();
        
        results.emplace_back("Caesar Cipher (1KB)", naive_time, optimized_time);
    }
    
    void saveResultsToFile() {
        ofstream file("benchmark_results.txt");
        if (file.is_open()) {
            file << "Cryptography System Performance Benchmark Results\n";
            file << "Generated: " << __DATE__ << " " << __TIME__ << "\n\n";
            
            file << left << setw(30) << "Test Name";
            file << right << setw(15) << "Original (ms)";
            file << right << setw(15) << "Optimized (ms)";
            file << right << setw(15) << "Improvement";
            file << right << setw(15) << "Percent" << endl;
            file << string(90, '-') << endl;
            
            for (const auto& result : results) {
                file << left << setw(30) << result.test_name;
                file << right << setw(15) << fixed << setprecision(3) << result.original_time;
                file << right << setw(15) << fixed << setprecision(3) << result.optimized_time;
                file << right << setw(15) << fixed << setprecision(2) << result.improvement_factor << "x";
                file << right << setw(15) << fixed << setprecision(1) << result.improvement_percent << "%";
                file << endl;
            }
            
            file.close();
            cout << "\nResults saved to benchmark_results.txt" << endl;
        }
    }
    
    void runAllBenchmarks() {
        printHeader();
        
        cout << "Running comprehensive performance benchmarks..." << endl;
        cout << "This may take a few minutes..." << endl;
        
        runModularExponentiationBenchmark();
        runStringBenchmark();
        runVectorBenchmark();
        runMemoryUsageBenchmark();
        runCipherBenchmark();
        
        cout << "\n" << string(80, '=') << endl;
        cout << "BENCHMARK RESULTS:" << endl;
        cout << string(80, '=') << endl;
        
        cout << left << setw(30) << "Test Name";
        cout << right << setw(12) << "Original";
        cout << right << setw(12) << "Optimized";
        cout << right << setw(10) << "Factor";
        cout << right << setw(10) << "Percent";
        cout << endl;
        cout << string(80, '-') << endl;
        
        for (const auto& result : results) {
            printResult(result);
        }
        
        printSummary();
        saveResultsToFile();
    }
};

int main() {
    cout << "Cryptography System Performance Benchmark Tool" << endl;
    cout << "===============================================" << endl;
    
    CryptographyBenchmark benchmark;
    benchmark.runAllBenchmarks();
    
    return 0;
}
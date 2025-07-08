# Optimized Makefile for Cryptography System Performance Analysis

# Compiler settings
CXX = g++
CXXFLAGS_BASE = -std=c++17 -Wall -Wextra
CXXFLAGS_DEBUG = $(CXXFLAGS_BASE) -g -O0 -DDEBUG
CXXFLAGS_RELEASE = $(CXXFLAGS_BASE) -O3 -DNDEBUG -march=native -mtune=native -flto
CXXFLAGS_PROFILE = $(CXXFLAGS_RELEASE) -pg -fprofile-arcs -ftest-coverage

# Source files
ORIGINAL_SRC = CYS-PROJECT.cpp
OPTIMIZED_SRC = CYS-PROJECT-OPTIMIZED.cpp
BENCHMARK_SRC = performance_benchmark.cpp

# Executables
ORIGINAL_EXE = original_crypto
OPTIMIZED_EXE = optimized_crypto
BENCHMARK_EXE = benchmark_crypto

# Default target
all: $(ORIGINAL_EXE) $(OPTIMIZED_EXE) $(BENCHMARK_EXE)

# Build original version (debug)
$(ORIGINAL_EXE): $(ORIGINAL_SRC)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $<

# Build optimized version (release with aggressive optimizations)
$(OPTIMIZED_EXE): $(OPTIMIZED_SRC)
	$(CXX) $(CXXFLAGS_RELEASE) -o $@ $<

# Build benchmark tool
$(BENCHMARK_EXE): $(BENCHMARK_SRC)
	$(CXX) $(CXXFLAGS_RELEASE) -o $@ $<

# Profile build for detailed analysis
profile: $(OPTIMIZED_SRC)
	$(CXX) $(CXXFLAGS_PROFILE) -o $(OPTIMIZED_EXE)_profile $<

# Memory optimization build
memory_optimized: $(OPTIMIZED_SRC)
	$(CXX) $(CXXFLAGS_RELEASE) -Os -ffunction-sections -fdata-sections -Wl,--gc-sections -o $(OPTIMIZED_EXE)_memory $<

# Performance test target
test_performance: $(ORIGINAL_EXE) $(OPTIMIZED_EXE) $(BENCHMARK_EXE)
	@echo "Running performance comparison..."
	./$(BENCHMARK_EXE)

# Size comparison
size_comparison: $(ORIGINAL_EXE) $(OPTIMIZED_EXE)
	@echo "=== BINARY SIZE COMPARISON ==="
	@echo "Original executable:"
	@ls -lh $(ORIGINAL_EXE) | awk '{print $$5 "\t" $$9}'
	@echo "Optimized executable:"
	@ls -lh $(OPTIMIZED_EXE) | awk '{print $$5 "\t" $$9}'
	@echo ""
	@echo "Size reduction:"
	@stat --format="%s" $(ORIGINAL_EXE) $(OPTIMIZED_EXE) | awk 'NR==1{orig=$$1} NR==2{opt=$$1; reduction=((orig-opt)/orig)*100; printf "%.1f%% reduction (%.0f bytes saved)\n", reduction, orig-opt}'

# Clean build artifacts
clean:
	rm -f $(ORIGINAL_EXE) $(OPTIMIZED_EXE) $(BENCHMARK_EXE)
	rm -f $(OPTIMIZED_EXE)_profile $(OPTIMIZED_EXE)_memory
	rm -f *.o *.gcda *.gcno gmon.out perf.data*

# Install performance tools (Linux)
install_perf_tools:
	@echo "Installing performance analysis tools..."
	sudo apt-get update
	sudo apt-get install -y valgrind perf linux-tools-generic

# Memory profiling with Valgrind
memory_profile: $(OPTIMIZED_EXE)
	@echo "Running memory profiling with Valgrind..."
	valgrind --tool=massif --stacks=yes ./$(OPTIMIZED_EXE)

# CPU profiling with perf
cpu_profile: $(OPTIMIZED_EXE)
	@echo "Running CPU profiling with perf..."
	perf record -g ./$(OPTIMIZED_EXE)
	perf report

# Help target
help:
	@echo "Available targets:"
	@echo "  all                 - Build all executables"
	@echo "  $(ORIGINAL_EXE)     - Build original version (debug)"
	@echo "  $(OPTIMIZED_EXE)    - Build optimized version (release)"
	@echo "  $(BENCHMARK_EXE)    - Build benchmark tool"
	@echo "  profile             - Build with profiling enabled"
	@echo "  memory_optimized    - Build optimized for size"
	@echo "  test_performance    - Run performance comparison"
	@echo "  size_comparison     - Compare binary sizes"
	@echo "  memory_profile      - Profile memory usage with Valgrind"
	@echo "  cpu_profile         - Profile CPU usage with perf"
	@echo "  clean               - Clean build artifacts"
	@echo "  install_perf_tools  - Install performance analysis tools"
	@echo "  help                - Show this help message"

.PHONY: all profile memory_optimized test_performance size_comparison clean memory_profile cpu_profile install_perf_tools help
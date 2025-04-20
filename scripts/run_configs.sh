#!/bin/bash

# Create results directory
rm -rf ../results
mkdir -p ../results

# Configurations for comparison:
# 1. Cache Size Impact (256 vs 512 vs 1024)
# 2. Associativity Impact (4-way vs 8-way)
# 3. Replacement Policy Impact (FIFO vs LRU)
# 4. Write Policy Impact (write-back vs write-through)
# 5. Write Allocation Impact (write-allocate vs no-write-allocate)

CONFIGS=(
    # Cache Size Comparison (keeping other parameters constant)
    # "256 4 16 write-allocate write-back fifo"  # Baseline small cache
    # "512 4 16 write-allocate write-back fifo"  # Double cache size
    # "1024 4 16 write-allocate write-back fifo" # Quadruple cache size
    
    # # Associativity Comparison
    # "256 4 16 write-allocate write-back fifo"  # 4-way associative
    # "256 8 16 write-allocate write-back fifo"  # 8-way associative
    
    # Replacement Policy Comparison
    "128 4 4 write-allocate write-back fifo"  # FIFO replacement
    "128 4 4 write-allocate write-back lru"   # LRU replacement
    
    # # Write Policy Comparison
    # "256 4 16 write-allocate write-back fifo"    # Write-back
    # "256 4 16 write-allocate write-through fifo" # Write-through
    
    # # Write Allocation Comparison
    # "256 4 16 write-allocate write-through fifo"     # Write-allocate
    # "256 4 16 no-write-allocate write-through fifo"  # No-write-allocate
)

for config in "${CONFIGS[@]}"; do
    config_name=$(echo "$config" | tr ' ' '_')
    echo "Running configuration: $config_name"
    
    for trace_file in ../traceinput/*.trace; do
        if [ -f "$trace_file" ]; then
            filename=$(basename "$trace_file" .trace)
            echo "Processing $filename..."
            ../build/cache_simulator $config < "$trace_file" > "../results/${config_name}_${filename}.txt"
        fi
    done
done

echo "All configurations completed. Results saved in results directory."
echo ""
echo "What to observe in the graphs:"
echo "1. Cache Size Impact:"
echo "   - Larger caches should show higher hit rates"
echo "   - But may have slightly higher latency due to more complex lookup"
echo ""
echo "2. Associativity Impact:"
echo "   - Higher associativity should reduce conflict misses"
echo "   - 8-way should show better hit rates than 4-way"
echo ""
echo "3. Replacement Policy Impact:"
echo "   - LRU should generally outperform FIFO"
echo "   - Difference more noticeable in smaller caches"
echo ""
echo "4. Write Policy Impact:"
echo "   - Write-back should show lower latency than write-through"
echo "   - Write-through may have better hit rates for write-intensive traces"
echo ""
echo "5. Write Allocation Impact:"
echo "   - Write-allocate should show better hit rates for subsequent reads"
echo "   - No-write-allocate may be better for write-once data" 
#!/bin/bash
cd .. ; rm -rf build ; mkdir build; cd build ; cmake .. ; make -j128 ; cd ../scripts 

CACHE_SIZE=256
ASSOCIATIVITY=4
BLOCK_SIZE=16
WRITE_POLICY="write-allocate"
WRITE_BACK="write-back"
REPLACEMENT="fifo"

echo "Running cache simulator with parameters:"
echo "Cache Size: $CACHE_SIZE"
echo "Associativity: $ASSOCIATIVITY"
echo "Block Size: $BLOCK_SIZE"
echo "Write Policy: $WRITE_POLICY"
echo "Write Back: $WRITE_BACK"
echo "Replacement: $REPLACEMENT"
echo "----------------------------------------"

for trace_file in ../traceinput/*.trace; do
    if [ -f "$trace_file" ]; then
        filename=$(basename "$trace_file")
        echo "Running simulation on $filename..."
        echo "----------------------------------------"
        ../build/cache_simulator $CACHE_SIZE $ASSOCIATIVITY $BLOCK_SIZE $WRITE_POLICY $WRITE_BACK $REPLACEMENT < "$trace_file"
        echo "----------------------------------------"
    fi
done

echo "All simulations completed"

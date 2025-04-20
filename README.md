# Cache Simulator

This repository is an attempt to model a cache with different policies for replacement and writing.

This is a CMake Supported project for generation of build files.

## Features

- Configurable cache parameters:
  - Cache size
  - Block size
  - Associativity
- Multiple replacement policies:
  - LRU (Least Recently Used)
  - FIFO (First In First Out)
- Flexible write policies:
  - Write-allocate / No-write-allocate
  - Write-back / Write-through
- Detailed statistics tracking:
  - Load/Store hits and misses
  - Total cycles
  - Memory access patterns

## Assumptions

- Memory addresses are 32-bit
- Cache size, block size, and associativity must be powers of 2
- Minimum block size is 4 bytes
- Memory access latency is 100 cycles per 4 bytes
- Cache access latency is 1 cycle
- Write-back requires write-allocate policy
- Trace files follow the format: `[operation] [address] [size]`
  - operation: 'l' for load, 's' for store
  - address: hexadecimal memory address
  - size: size of access in bytes

## For generation of trace files, navigate to scripts directory and run:

```bash
chmod +x download_traces.sh
./download_traces.sh
```

## Running the Simulator

To run the simulator against the traces, navigate to scripts directory and run:

```bash
chmod +x run_sim.sh
./run_sim.sh
```
## Running the Simulator with various configs

To run the simulator against several combinations of traces and cache configs, navigate to scripts directory and run:

```bash
chmod +x run_configs.sh
./run_configs.sh
```

To generate the corresponding plots after running it, run:

```bash
python3 plot_results.py
```

#include "cache/simulator/cache_simulator.hpp"
#include "cache/config/cache_config.hpp"
#include "cache/config/cache_policies.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace cache_simulator;

int main(int argc, char* argv[]) {
    
        if (argc != 7) {
            std::cerr << "Usage: " << argv[0] << " <sets> <blocks per set> <block size> <write policy> <write strategy> <replacement policy>" << std::endl;
            return 1;
        }

        auto numSets = std::stoi(argv[1]);
        auto blocksPerSet = std::stoi(argv[2]);
        auto blockSize = std::stoi(argv[3]);
        CacheConfig config(numSets, blocksPerSet, blockSize);
        
        WriteAllocatePolicy writeAllocate;
        if (std::string(argv[4]) == "write-allocate") {
            writeAllocate = WriteAllocatePolicy::WRITE_ALLOCATE;
        } else if (std::string(argv[4]) == "no-write-allocate") {
            writeAllocate = WriteAllocatePolicy::NO_WRITE_ALLOCATE;
        } else {
            std::cerr << "Invalid write allocate policy. Use 'write-allocate' or 'no-write-allocate'." << std::endl;
            return 1;
        }
         // Parse write back policy
        WriteBackPolicy writeBack;
        if (std::string(argv[5]) == "write-through") {
            writeBack = WriteBackPolicy::WRITE_THROUGH;
        } else if (std::string(argv[5]) == "write-back") {
            writeBack = WriteBackPolicy::WRITE_BACK;
        } else {
            std::cerr << "Invalid write back policy. Use 'write-through' or 'write-back'." << std::endl;
            return 1;
        }
        
        // Parse replacement policy
        ReplacementPolicy replacementPolicy;
        if (std::string(argv[6]) == "lru") {
            replacementPolicy = ReplacementPolicy::LRU;
        } else if (std::string(argv[6]) == "fifo") {
            replacementPolicy = ReplacementPolicy::FIFO;
        } else {
            std::cerr << "Invalid replacement type. Use 'lru' or 'fifo'." << std::endl;
            return 1;
        }
        
        // Create cache simulator
        CacheSimulator simulator(config, writeAllocate, writeBack, replacementPolicy);
        simulator.processTrace();
        simulator.printStatistics();      
        return 0;
    
} 
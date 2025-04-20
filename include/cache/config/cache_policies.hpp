#ifndef CACHE_POLICIES_HPP
#define CACHE_POLICIES_HPP

namespace cache_simulator {

enum class ReplacementPolicy {
    LRU,
    FIFO
};
enum class WriteAllocatePolicy {
    WRITE_ALLOCATE,
    NO_WRITE_ALLOCATE
};
enum class WriteBackPolicy {
    WRITE_THROUGH,
    WRITE_BACK
};

} // namespace cache_simulator 

#endif // CACHE_POLICIES_HPP 
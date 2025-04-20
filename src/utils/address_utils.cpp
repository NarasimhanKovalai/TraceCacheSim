#include "utils/address_utils.hpp"

namespace cache_simulator {

uint32_t AddressUtils::getSetIndex(uint32_t address, uint32_t offsetBits, uint32_t indexMask) {
    return (address >> offsetBits) & indexMask;
}

uint32_t AddressUtils::getTag(uint32_t address, uint32_t offsetBits, uint32_t indexBits) {
    return address >> (offsetBits + indexBits);
}

} // namespace cache_simulator 
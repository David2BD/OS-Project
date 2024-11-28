#include "MemorySegment.h"
#include <stdexcept>

// Constructeur
    MemorySegment::MemorySegment(size_t startAddress, size_t size, AccessType accessType)
        : startAddress(startAddress), size(size), accessType(accessType), memory(size) {
        if (size == 0) {
            throw std::invalid_argument("Segment size cannot be zero.");
        }
    }

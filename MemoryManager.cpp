#include "MemoryManager.h"
#include "Program.h"
#include <unordered_map>
#include <iostream>
#include <limits>

MemoryManager::MemoryManager(size_t ramSize, size_t virtualMemorySize)
    : ramSize(ramSize), virtualMemorySize(virtualMemorySize), currentRamAddress(0) {
    if (ramSize == 0 || virtualMemorySize == 0)
    {
        throw std::invalid_argument("La RAM et la mémoire virtuelle doivent avoir une taille plus grande que zéro.");
    }
}

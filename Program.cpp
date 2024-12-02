// David Bénard Desjardins: 536 788 905,
// Léo Mercier: 536 972 948,
// Stéphanie Giguère: 536 986 277
#include "Program.h"
#include <stdexcept>
#include "MemorySegment.h"

// Constructeur de la classe Program
Program::Program(const std::string &name, size_t memorySize, const std::vector<std::string> &instructions)
    : name(name), 
      memorySize(memorySize), 
      loaded(false), 
      startAddress(0), 
      instructions(instructions),
      instructionsSegment(0, memorySize * 0.2, MemorySegment::READ_ONLY),
      dataSegment(memorySize * 0.2, memorySize * 0.8, MemorySegment::READ_WRITE) {
    
    if (memorySize == 0 || instructions.empty()) {
        throw std::invalid_argument("Taille mémoire ou instructions invalides.");
    }
}

void Program::setStartAddress(size_t newStartAddress) {
    startAddress = newStartAddress;
    // Mettre à jour les adresses de début des segments
    instructionsSegment = MemorySegment(newStartAddress, memorySize * 0.2, MemorySegment::READ_ONLY);
    dataSegment = MemorySegment(newStartAddress + memorySize * 0.2, memorySize * 0.8, MemorySegment::READ_WRITE);
}

MemorySegment& Program::getInstructionsSegment() {
    return instructionsSegment;
}

MemorySegment& Program::getDataSegment() {
    return dataSegment;
}

size_t Program::getStartAddress() const {
    return startAddress;
}

size_t Program::getMemorySize() const {
    return memorySize;
}

const std::string& Program::getName() const {
    return name;
}

bool Program::isLoaded() const {
    return loaded;
}

void Program::setLoaded(bool state) {
    loaded = state;
}
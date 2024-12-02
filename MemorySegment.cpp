// David Bénard Desjardins: 536 788 905,
// Léo Mercier: 536 972 948,
// Stéphanie Giguère: 536 986 277
#include "MemorySegment.h"
#include <stdexcept>

bool MemorySegment::canAccess(size_t address, AccessType requestType) const
{
    // Vérifier si l'adresse est dans les limites du segment
    if (address < startAddress || address >= startAddress + size) {
        return false;
    }
    
    // Vérifier les permissions d'accès
    if (requestType == READ_WRITE && accessType == READ_ONLY) {
        return false;
    }
    
    return true;
}

char MemorySegment::read(size_t address) const {
    if (!canAccess(address, READ_ONLY)) {
        throw std::out_of_range("Acces memoire non autorise en lecture");
    }
    return memory[address - startAddress];
}

void MemorySegment::write(size_t address, char value) {
    if (!canAccess(address, READ_WRITE)) {
        throw std::out_of_range("Acces memoire non autorise en ecriture");
    }
    memory[address - startAddress] = value;
}

MemorySegment::MemorySegment(size_t startAddress, size_t size, AccessType accessType)
    : startAddress(startAddress), 
      size(size), 
      accessType(accessType),
      memory(size, '\0')  // Initialise le vecteur avec la taille donnée et des caractères nuls
{
}

size_t MemorySegment::getStartAddress() const {
    return startAddress;
}

size_t MemorySegment::getEndAddress() const {
    return startAddress + size;
}



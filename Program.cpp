#include "Program.h"
#include <stdexcept>
#include "MemorySegment.h"

// Constructeur de la classe Program
Program::Program(const std::string &name, size_t memorySize, const std::vector<std::string> &instructions)
        : name(name), memorySize(memorySize), loaded(false), startAddress(0), instructions(instructions), instructionsSegment(0, memorySize * 0.2, MemorySegment::READ_ONLY), dataSegment(0, memorySize * 0.8, MemorySegment::READ_WRITE) {
    if (memorySize == 0 || instructions.empty())
    {
        throw std::invalid_argument("Taille mémoire ou instructions invalides.");
    }
}

// Méthode pour définir le début de l'adresse: à refaire plus tard, je l'ai mis comme ça pour pas que ça plante. ****
void Program::setStartAddress(size_t startAddress) {
    this->startAddress = startAddress;
}

// Getters et Setters
// Retourne le segment d'instructions.
const MemorySegment& Program::getInstructionsSegment() {
    return instructionsSegment;
}

// Retourne le segment de données.
MemorySegment & Program::getDataSegment() {
    return dataSegment;
}

// Retourne l'adresse de départ.
size_t Program::getStartAddress() const {
    return startAddress;
}

// Retourne la taille de la mémoire.
size_t Program::getMemorySize() const {
    return memorySize;
}

// Retourne le nom du programme.
const std::string& Program::getName() {
    return name;
}

// Retourne si le programme est chargé ou non.
bool Program::isLoaded() const {
    return loaded;
}

// Définir l'état de «loaded».
void Program::setLoaded(bool state) {
    loaded = state;
}
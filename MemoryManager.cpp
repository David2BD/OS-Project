// David Bénard Desjardins: 536 788 905,
// Léo Mercier: 536 972 948,
// Stéphanie Giguère: 536 986 277
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

bool MemoryManager::loadProgram(Program &program) {
    if (program.isLoaded()) {
        return false;
    }

    size_t programSize = program.getMemorySize();

    // Vérifier si l'espace est suffisant
    if (currentRamAddress + programSize <= ramSize) {
        // Assez d'espace, charger directement
        program.setStartAddress(currentRamAddress);
        currentRamAddress += programSize;
        program.setLoaded(true);
        ram.insert(std::make_pair(program.getName(), program));
        return true;
    }

    // Libérer de l'espace en suivant FIFO
    size_t freeSpace = ramSize - currentRamAddress;
    while (!ram.empty() && freeSpace < programSize) {
        auto firstIn = ram.begin();
        freeSpace += firstIn->second.getMemorySize();
        swapOutProgram();
        
        // Si on a assez d'espace, arrêter le swapping
        if (freeSpace >= programSize) {
            break;
        }
    }

    if (currentRamAddress + programSize > ramSize) {
        return false;
    }

    program.setStartAddress(currentRamAddress);
    currentRamAddress += programSize;
    program.setLoaded(true);
    ram.insert(std::make_pair(program.getName(), program));
    return true;
}

void MemoryManager::swapOutProgram() {
    if (ram.empty()) {
        return;
    }

    // Prendre le premier programme de la RAM (politique FIFO)
    auto it = ram.begin();
    Program swappedProgram = it->second;
    
    // Déplacer le programme vers la mémoire virtuelle
    virtualMemory.insert(std::make_pair(swappedProgram.getName(), swappedProgram));
    
    // Libérer l'espace en RAM
    currentRamAddress -= swappedProgram.getMemorySize();
    ram.erase(it);
}

void MemoryManager::testMemoryAccess(Program &program, size_t address, bool writeOperation) {
    if (!program.isLoaded()) {
        std::cout << "Test echoue : Programme " << program.getName() << " non charge en memoire." << std::endl;
        return;
    }

    std::cout << "Test d'acces " << (writeOperation ? "en ecriture" : "en lecture") 
              << " pour " << program.getName() << " a l'adresse " << address << " : ";
    
    try {
        // Tester l'accès au segment d'instructions
        if (address >= program.getInstructionsSegment().getStartAddress() && 
            address < program.getInstructionsSegment().getEndAddress()) {
            if (writeOperation) {
                program.getInstructionsSegment().write(address, 'X');
                std::cout << "Ecriture reussie sur le segment d'instructions a l'adresse " << address << std::endl;
            } else {
                program.getInstructionsSegment().read(address);
                std::cout << "Lecture reussie sur le segment d'instructions a l'adresse " << address << std::endl;
            }
        }
        // Tester l'accès au segment de données
        else if (address >= program.getDataSegment().getStartAddress() && 
                 address < program.getDataSegment().getEndAddress()) {
            if (writeOperation) {
                program.getDataSegment().write(address, 'X');
                std::cout << "Ecriture reussie sur le segment de donnees a l'adresse " << address << std::endl;
            } else {
                program.getDataSegment().read(address);
                std::cout << "Lecture reussie sur le segment de donnees a l'adresse " << address << std::endl;
            }
        }
        else {
            std::cout << "Adresse hors limites du programme." << std::endl;
        }
    }
    catch (const std::out_of_range& e) {
        std::cout << "ECHEC - " << e.what() << std::endl;
    }
}

void MemoryManager::displayMemoryState() const {
    std::cout << "--- Etat de la RAM (" << currentRamAddress << "/" << ramSize << " octets utilises) ---" << std::endl;
    if (ram.empty()) {
        std::cout << "RAM vide" << std::endl;
    } else {
        for (const auto& pair : ram) {
            const Program& prog = pair.second;
            std::cout << "Programme : " << prog.getName() 
                      << " | Adresse : " << prog.getStartAddress() 
                      << " | Taille : " << prog.getMemorySize() << " octets"
                      << " | Statut : Actif en RAM" << std::endl;
        }
    }

    std::cout << "\n--- Etat de la Memoire Virtuelle ---" << std::endl;
    if (virtualMemory.empty()) {
        std::cout << "Memoire virtuelle vide" << std::endl;
    } else {
        for (const auto& pair : virtualMemory) {
            const Program& prog = pair.second;
            std::cout << "Programme : " << prog.getName() 
                      << " | Adresse : " << prog.getStartAddress() 
                      << " | Taille : " << prog.getMemorySize() << " octets"
                      << " | Statut : Swapped" << std::endl;
        }
    }
    std::cout << std::endl;
}

void MemoryManager::unloadAllPrograms() {
    ram.clear();
    virtualMemory.clear();
    currentRamAddress = 0;
}

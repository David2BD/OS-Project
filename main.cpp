// SVP indiquer votre nom prenom et IDUL
// David Bénard Desjardins: 536 788 905,
// Léo Mercier: 536 972 948,
// Stéphanie Giguère: 536 986 277

#include <iostream>
#include "MemoryManager.h"
#include "Program.h"

// Création d'instructions plus variées pour les tests
std::vector<std::string> createInstructions(int count) {
    std::vector<std::string> instructions;
    for (int i = 0; i < count; i++) {
        instructions.push_back("INSTRUCTION_" + std::to_string(i));
    }
    return instructions;
}

int main() {
    std::cout << "\n=== Initialisation du gestionnaire de memoire (4 MB RAM, 10 MB Virtual) ===\n" << std::endl;
    MemoryManager memoryManager(4 * 1024 * 1024, 10 * 1024 * 1024);
    
    std::cout << "\n=== Creation et chargement des programmes 1-4 ===\n" << std::endl;
    // Création des programmes avec des instructions variables
    Program prog1("Program1", 1 * 1024 * 1024, createInstructions(5));   // 5 instructions
    Program prog2("Program2", 2 * 1024 * 1024, createInstructions(10));  // 10 instructions
    Program prog3("Program3", 1 * 1024 * 1024, createInstructions(3));   // 3 instructions
    Program prog4("Program4", 2 * 1024 * 1024, createInstructions(8));   // 8 instructions

    // Chargement des programmes et affichage après chaque chargement
    memoryManager.loadProgram(prog1);
    memoryManager.displayMemoryState();
    
    memoryManager.loadProgram(prog2);
    memoryManager.displayMemoryState();
    
    memoryManager.loadProgram(prog3);
    memoryManager.displayMemoryState();
    
    memoryManager.loadProgram(prog4);
    memoryManager.displayMemoryState();

    std::cout << "\n=== Vidage de la memoire ===\n" << std::endl;
    memoryManager.unloadAllPrograms();
    memoryManager.displayMemoryState();

    std::cout << "\n=== Creation et chargement des programmes 5-6 ===\n" << std::endl;
    // Création et chargement des programmes 5 et 6
    Program prog5("Program5", 1 * 1024 * 1024, createInstructions(5));   // 5 instructions
    Program prog6("Program6", 2 * 1024 * 1024, createInstructions(10));  // 10 instructions

    memoryManager.loadProgram(prog5);
    memoryManager.loadProgram(prog6);

    std::cout << "\n=== Tests d'acces memoire pour Programme 5 ===\n" << std::endl;
    // Tests d'accès mémoire pour prog5
    size_t prog5InstrAddr = prog5.getInstructionsSegment().getStartAddress();
    size_t prog5DataAddr = prog5.getDataSegment().getStartAddress();
    
    memoryManager.testMemoryAccess(prog5, prog5InstrAddr, false);  // lecture instructions
    memoryManager.testMemoryAccess(prog5, prog5InstrAddr, true);   // écriture instructions
    memoryManager.testMemoryAccess(prog5, prog5DataAddr, false);   // lecture données
    memoryManager.testMemoryAccess(prog5, prog5DataAddr, true);    // écriture données

    std::cout << "\n=== Tests d'acces memoire pour Programme 6 ===\n" << std::endl;
    // Tests d'accès mémoire pour prog6
    size_t prog6InstrAddr = prog6.getInstructionsSegment().getStartAddress();
    size_t prog6DataAddr = prog6.getDataSegment().getStartAddress();
    
    memoryManager.testMemoryAccess(prog6, prog6InstrAddr, false);  // lecture instructions
    memoryManager.testMemoryAccess(prog6, prog6InstrAddr, true);   // écriture instructions
    memoryManager.testMemoryAccess(prog6, prog6DataAddr, false);   // lecture données
    memoryManager.testMemoryAccess(prog6, prog6DataAddr, true);    // écriture données

    return 0;
}

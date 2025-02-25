//
// Created by Hamza Alaoui on 2024-11-15.
//
// SVP indiquer votre nom prenom et IDUL

// David Bénard Desjardins: 536 788 905,
// Léo Mercier: 536 972 948,
// Stéphanie Giguère: 536 986 277

#ifndef TP3_CODE_PROGRAM_H
#define TP3_CODE_PROGRAM_H

#include <string>
#include <vector>
#include "MemorySegment.h"

class Program {
public:
    //constructeur
    Program(const std::string &name, size_t memorySize, const std::vector<std::string> &instructions);

    //Methode pour définir le debut d'adresse
    void setStartAddress(size_t startAddress);

    //Getters et Setters
    MemorySegment& getInstructionsSegment();
    MemorySegment& getDataSegment();
    size_t getStartAddress() const;
    size_t getMemorySize() const;
    const std::string& getName() const;
    bool isLoaded() const;
    void setLoaded(bool state);

private:
    std::string name;
    size_t memorySize;
    bool loaded;
    size_t startAddress;
    std::vector<std::string> instructions;

    // Memory segments
    MemorySegment instructionsSegment;
    MemorySegment dataSegment;
};
#endif //TP3_CODE_PROGRAM_H

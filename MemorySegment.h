//
// Created by Hamza Alaoui on 2024-11-15.
//
// SVP indiquer votre nom prenom et IDUL
// David Bénard Desjardins: 536 788 905,
// Léo Mercier: 536 972 948,
// Stéphanie Giguère: 536 986 277

#ifndef TP3_CODE_MEMORYSEGMENT_H
#define TP3_CODE_MEMORYSEGMENT_H
#include <vector>
#include <cstddef>

class MemorySegment {
public:
    enum AccessType { READ_ONLY, READ_WRITE };

    //Constructeur
    MemorySegment(size_t startAddress, size_t size, AccessType accessType);

    //Methode pour tester le type d'access
    bool canAccess(size_t address, AccessType requestType) const;

    //Methode pour lire un char dans une adresse
    char read(size_t address) const;
    //Methode pour ecrire la valeur un char dans une adresse
    void write(size_t address, char value);

    //Methode getter avoir le debut d'adresse du segment
    size_t getStartAddress() const;

    //Methode pour avoir l'adresse de fin du segment
    size_t getEndAddress() const;
private:
    size_t startAddress;
    size_t size;
    AccessType accessType;
    std::vector<char> memory;
};
#endif //TP3_CODE_MEMORYSEGMENT_H

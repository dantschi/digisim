#include "XorGate.h"
#include <iostream>

/**
 * Konstruktor des XorGate
 * Der Name wird an die Basisklasse Component weitergegeben
 */
XorGate::XorGate(std::string n) : Component(n) {
    std::cout << "[" << name << "] XOR-Gatter aktiviert" << std::endl;
}

/**
 * Berechnet die XOR-Logik:
 * output = inA XOR inB = (inA && !inB) || (!inA && inB)
 * 
 * Bedeutung: Ausgabe ist 1, wenn die Eingänge unterschiedlich sind
 * A | B | XOR
 * ---------
 * 0 | 0 | 0
 * 0 | 1 | 1
 * 1 | 0 | 1
 * 1 | 1 | 0
 */
bool XorGate::evaluate() {
    output = (inA && !inB) || (!inA && inB);
    return output;
}

/**
 * Gibt den Zustand dieses XOR-Gatters aus
 */
void XorGate::printState() const {
    std::cout << "XorGate [" << name << ": A=" << (inA ? 1 : 0) 
              << ", B=" << (inB ? 1 : 0) 
              << "] => Output=" << (output ? 1 : 0) << std::endl;
}

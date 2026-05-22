#include "NandGate.h"
#include <iostream>

/**
 * Konstruktor des NandGate
 * Erstellt interne AndGate- und NotGate-Instanzen mit aussagekräftigen Namen
 * 
 * Wichtig: Wir rufen auch den Konstruktor der Basisklasse auf
 */
NandGate::NandGate(std::string n) 
    : Component(n), andGate(n + "-AND"), notGate(n + "-NOT") {
    std::cout << "[" << name << "] NAND-Gatter aktiviert (Komposition: AND + NOT)" << std::endl;
}

/**
 * Setzt Eingang A - weitergeleitet an das interne AND-Gatter
 * Überschreibt die Methode der Basisklasse
 */
void NandGate::setInputA(int val) {
    inA = (val != 0);  // Speichere auch im Basisklassen-Attribut
    andGate.setInputA(val);
}

/**
 * Setzt Eingang B - weitergeleitet an das interne AND-Gatter
 * Überschreibt die Methode der Basisklasse
 */
void NandGate::setInputB(int val) {
    inB = (val != 0);  // Speichere auch im Basisklassen-Attribut
    andGate.setInputB(val);
}

/**
 * evaluate(): Der polymorphe Kern
 * 
 * Berechnet NAND = NOT(AND):
 * 1. AND-Gatter mit beiden Eingängen berechnen (evaluate)
 * 2. Ergebnis des AND an das NOT-Gatter weitergeben
 * 3. NOT-Gatter evaluieren
 */
bool NandGate::evaluate() {
    // Evaluiere das interne AND-Gatter
    bool andResult = andGate.evaluate();
    
    // Weitergabe des Ergebnisses an das NOT-Gatter
    notGate.setInputA(andResult ? 1 : 0);
    
    // Evaluiere das NOT-Gatter und speichere das Ergebnis
    output = notGate.evaluate();
    
    return output;
}

/**
 * printState(): Gibt den kompletten Zustand des NAND-Gatters aus
 */
void NandGate::printState() const {
    std::cout << "NandGate [" << name << ": A=" << (inA ? 1 : 0) 
              << ", B=" << (inB ? 1 : 0) 
              << "] => Output=" << (output ? 1 : 0) << std::endl;
}

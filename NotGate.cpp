#include "NotGate.h"
#include <iostream>

/**
 * Konstruktor des NotGate
 * Der Name wird an die Basisklasse Component weitergegeben
 */
NotGate::NotGate(std::string n) : Component(n) {
    std::cout << "[" << name << "] NOT-Gatter aktiviert" << std::endl;
}

/**
 * Setzt Eingang B - aber NOT hat nur einen Eingang!
 * Diese Überschreibung (Override) gibt eine Warnung aus
 */
void NotGate::setInputB(int /* val */) {
    std::cout << "[" << name << " WARNUNG] NOT-Gatter hat keinen Eingang B!" << std::endl;
    std::cout << "           Nutzen Sie setInputA() für den einzigen Eingang." << std::endl;
}

/**
 * Berechnet die NOT-Logik:
 * output = NOT inA
 * 
 * Die Methode speichert das Ergebnis und gibt es zurück.
 */
bool NotGate::evaluate() {
    output = !inA;
    return output;
}

/**
 * Gibt den Zustand dieses NOT-Gatters aus
 */
void NotGate::printState() const {
    std::cout << "NotGate [" << name << ": Input=" << (inA ? 1 : 0) 
              << "] => Output=" << (output ? 1 : 0) << std::endl;
}






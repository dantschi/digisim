#include "Component.h"

/**
 * Konstruktor der Component-Klasse
 * Initialisiert alle Attribute sicher
 */
Component::Component(std::string n) 
    : name(n), inA(false), inB(false), output(false) {
    std::cout << "[" << name << "] Komponente erstellt" << std::endl;
}

/**
 * Setter für Eingang A
 * Prüft, dass nur gültige Werte (0 oder 1) gesetzt werden
 */
void Component::setInputA(int val) {
    if (val == 0) {
        inA = false;
    } else if (val == 1) {
        inA = true;
    } else {
        std::cerr << "[" << name << " FEHLER] Ungültiger Wert für Eingang A: " << val 
                  << " (erwartet 0 oder 1)" << std::endl;
    }
}

/**
 * Setter für Eingang B
 * Prüft, dass nur gültige Werte (0 oder 1) gesetzt werden
 * Kann in abgeleiteten Klassen (z.B. NotGate) überschrieben werden
 */
void Component::setInputB(int val) {
    if (val == 0) {
        inB = false;
    } else if (val == 1) {
        inB = true;
    } else {
        std::cerr << "[" << name << " FEHLER] Ungültiger Wert für Eingang B: " << val 
                  << " (erwartet 0 oder 1)" << std::endl;
    }
}

/**
 * Getter für den Ausgangswert
 */
bool Component::getOutput() const {
    return output;
}

/**
 * Virtueller Destruktor: Wird aufgerufen wenn Objekt zerstört wird
 */
Component::~Component() {
    std::cout << "Zerstöre Bauteil: " << name << std::endl;
}

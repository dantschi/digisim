#pragma once

#include "Component.h"

/**
 * OR-Gatter Klasse (erbt von Component)
 * Ausgabe ist 1, wenn mindestens ein Eingang 1 ist
 * 
 * Durch die Vererbung erhalten wir automatisch:
 * - Attribute: name, inA, inB, output (protected)
 * - Methoden: setInputA(), setInputB(), getOutput()
 */
class OrGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen und leitet ihn an die Basisklasse weiter
     * @param n Der Name dieses OR-Gatters
     */
    OrGate(std::string n);

    /**
     * Berechnet das Ausgangssignal (OR-Logik: mindestens ein Eingang muss 1 sein)
     * @return true wenn mindestens ein Eingang 1 ist, sonst false
     */
    bool evaluate() override;

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    void printState() const override;
};

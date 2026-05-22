#pragma once

#include "Component.h"

/**
 * AND-Gatter Klasse (erbt von Component)
 * Ausgabe ist 1, nur wenn beide Eingänge 1 sind
 * 
 * Durch die Vererbung erhalten wir automatisch:
 * - Attribute: name, inA, inB, output (protected)
 * - Methoden: setInputA(), setInputB(), getOutput()
 */
class AndGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen und leitet ihn an die Basisklasse weiter
     * @param n Der Name dieses AND-Gatters
     */
    AndGate(std::string n);

    /**
     * Berechnet das Ausgangssignal (AND-Logik: beide Eingänge müssen 1 sein)
     * Das Keyword 'final' verhindert, dass Subklassen diese Methode überschreiben
     * @return true wenn beide Eingänge 1 sind, sonst false
     */
    bool evaluate() override final;

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    void printState() const override;
};

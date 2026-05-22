#pragma once

#include "Component.h"

/**
 * XOR-Gatter Klasse (erbt von Component)
 * Ausgabe ist 1, wenn die Eingänge unterschiedlich sind
 * 
 * Logik: XOR(A, B) = (A AND NOT B) OR (NOT A AND B)
 *        Oder auch: (A OR B) AND NOT(A AND B)
 * 
 * Durch die Vererbung erhalten wir automatisch:
 * - Attribute: name, inA, inB, output (protected)
 * - Methoden: setInputA(), setInputB(), getOutput()
 * 
 * Das zeigt die Kraft der Vererbung:
 * Wir brauchen nur noch die spezifische Logik zu implementieren!
 */
class XorGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses XOR-Gatters
     */
    XorGate(std::string n);

    /**
     * Berechnet die XOR-Logik
     * @return true wenn die Eingänge unterschiedlich sind, sonst false
     */
    bool evaluate() override;

    /**
     * Gibt den aktuellen Zustand aus
     */
    void printState() const override;
};

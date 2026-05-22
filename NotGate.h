#pragma once

#include "Component.h"

/**
 * NOT-Gatter Klasse (erbt von Component)
 * Ausgabe ist invertiert - WICHTIG: NOT hat nur einen Eingang!
 * 
 * Durch die Vererbung bekommen wir inA, inB und output, aber:
 * - Wir nutzen nur inA als echten Eingang
 * - setInputB() ist überschrieben, um eine Warnung auszugeben
 */
class NotGate : public Component {
public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses NOT-Gatters
     */
    NotGate(std::string n);

    /**
     * Überschriebene Methode: Warnt vor setInputB()
     * Das NOT-Gatter hat nur einen Eingang!
     */
    void setInputB(int val) override;

    /**
     * Berechnet das invertierte Ausgangssignal
     * output = NOT inA
     * @return true wenn input 0 ist, false wenn input 1 ist
     */
    bool evaluate() override;

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    void printState() const override;
};

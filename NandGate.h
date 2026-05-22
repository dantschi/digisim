#pragma once

#include "Component.h"
#include "AndGate.h"
#include "NotGate.h"

/**
 * NAND-Gatter durch Komposition mit Polymorphismus-Integration
 * Kombiniert ein AndGate mit einem NotGate
 * NAND = NOT(AND)
 * 
 * Erbt von Component um sich polymorphisch verhalten zu können,
 * aber nutzt intern Komposition.
 */
class NandGate : public Component {
private:
    AndGate andGate;
    NotGate notGate;

public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses NAND-Gatters
     */
    NandGate(std::string n);

    /**
     * Setzt Eingang A für das interne AND-Gatter
     */
    void setInputA(int val) override;

    /**
     * Setzt Eingang B für das interne AND-Gatter
     */
    void setInputB(int val) override;

    /**
     * Berechnet: NAND = NOT(AND(inA, inB))
     * @return true wenn NAND-Logik 1 ergibt, sonst false
     */
    bool evaluate() override;

    /**
     * Gibt den Zustand aus
     */
    void printState() const override;
};



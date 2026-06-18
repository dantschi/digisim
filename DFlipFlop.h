#pragma once

#include "Component.h"

/**
 * D-Flip-Flop Klasse (erbt von Gate)
 * Das elementarste Speicherbauteil - Firewall gegen Endlosschleifen (Zyklen)
 * 
 * Merkmale:
 * - Hat genau 1 Eingangs-Pin (m_inputs.size() == 1)
 * - Speichert einen bool-Wert in m_storedState
 * - evaluate() gibt NICHT den Input aus, sondern m_storedState (Firewall!)
 * - onClockTick() wird nach der Lese-Phase aufgerufen und aktualisiert m_storedState
 * 
 * Architektonische Rolle:
 * - Das DFlipFlop unterbricht rekursive Aufrufe
 * - Die Lese-Phase (evaluate()) arbeitet mit alten Werten
 * - Die Schreib-Phase (onClockTick()) aktualisiert die Speicher
 */
class DFlipFlop : public Gate {
private:
    // Der Tresor: Speichert den Zustand zwischen den Taktflanken
    bool m_storedState = false;

public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses D-Flip-Flops
     */
    DFlipFlop(std::string n);

    /**
     * Firewall-Methode: NICHT den Input evaluieren!
     * Gibt einfach den gespeicherten Wert zurück
     * 
     * ACHTUNG: Diese Methode ruft evaluate() auf dem Input NICHT auf!
     * Das ist die Firewall, die Endlosschleifen verhindert.
     */
    void evaluate() override;

    /**
     * Taktflanke-Simulation
     * Wird in der Schreib-Phase aufgerufen
     * Liest den aktuellen Input-Wert und speichert ihn in m_storedState
     */
    void onClockTick();

    /**
     * Gibt den aktuellen Zustand des D-Flip-Flops aus
     */
    void printState() const override;

    std::string getType() const override { return "DFF"; }

    /**
     * Virtueller Destruktor
     */
    virtual ~DFlipFlop();
};

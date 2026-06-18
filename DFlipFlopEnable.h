#pragma once

#include "Component.h"

/**
 * D-Flip-Flop mit Enable-Pin (DFFE) Klasse (erbt von Gate)
 * Erweiterung des D-Flip-Flops um einen Enable-Pin
 * 
 * Merkmale:
 * - Hat genau 2 Eingangs-Pins:
 *   * Pin 0: D (Daten-Eingang)
 *   * Pin 1: EN (Enable-Signal)
 * - Speichert einen bool-Wert in m_storedState
 * - evaluate() gibt den gespeicherten Wert zurück (Firewall)
 * - onClockTick() aktualisiert m_storedState NUR wenn EN=true
 */
class DFlipFlopEnable : public Gate {
private:
    // Der Tresor: Speichert den Zustand zwischen den Taktflanken
    bool m_storedState = false;

public:
    /**
     * Konstruktor: Nimmt einen Namen entgegen
     * @param n Der Name dieses D-Flip-Flops mit Enable
     */
    DFlipFlopEnable(std::string n);

    /**
     * Firewall-Methode: Gibt einfach den gespeicherten Wert zurück
     */
    void evaluate() override;

    /**
     * Taktflanke-Simulation mit Enable
     * Wird in der Schreib-Phase aufgerufen
     * 
     * Liest Pin 1 (Enable-Signal):
     * - Wenn EN=true: Übernimmt Pin 0 (D) in m_storedState
     * - Wenn EN=false: Speichert nichts (Zustand bleibt gleich)
     */
    void onClockTick();

    /**
     * Gibt den aktuellen Zustand des D-Flip-Flops aus
     */
    void printState() const override;

    std::string getType() const override { return "DFFE"; }

    /**
     * Virtueller Destruktor
     */
    virtual ~DFlipFlopEnable();
};

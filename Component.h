#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

/**
 * Gate (Basisklasse) - Abstraktion für alle Logikgatter
 * 
 * Architektur (Labor 11):
 * - LogicEngine besitzt alle Gatter via std::unique_ptr (Ownership)
 * - Gatter referenzieren andere Gatter via Raw Pointers (Non-owning Verweise)
 * - Ein Vektor m_inputs speichert alle Eingänge (Adjazenzliste / DAG)
 * - Jedes Gatter kennt die Anzahl seiner benötigten Eingänge
 * - evaluate() zieht sich Werte aktiv über die Pointer (Pull-Prinzip)
 * 
 * Alle spezifischen Gatter (AndGate, OrGate, NotGate, etc.) erben von dieser Klasse
 * und müssen die reine virtuelle Methode evaluate() implementieren.
 */
class Gate {
protected:
    // Geschützte Attribute
    std::string m_name;
    bool m_output;
    std::vector<Gate*> m_inputs;  // ← Non-owning Raw Pointers zu anderen Gattern
    
    // ===== Labor 9: Memoization & Zyklus-Schutz =====
    bool m_isCalculated = false;  // Cache-Flag: "Wurde ich schon berechnet?"

public:
    /**
     * Konstruktor: Initialisiert ein Gatter mit Namen
     * @param n Der Name des Gatters (z.B. "Haupt-AND", "Carry")
     */
    Gate(std::string n);

    /**
     * Verbindet einen Eingang mit einem anderen Gatter (Kabel-Plugin)
     * WICHTIG: Erwartet Raw Pointers (Non-owning Verweise)!
     * Die LogicEngine behält die Ownership über alle Gatter.
     * @param index Der Pin-Index (0, 1, ...)
     * @param source Das Quell-Gatter (Raw Pointer - kein Ownership Transfer!)
     */
    void connectInput(int index, Gate* source);

    /**
     * Gibt den aktuellen Ausgangswert zurück
     * @return true wenn output=1, false wenn output=0
     */
    bool getOutput() const;

    /**
     * Gibt den Namen des Gatters zurück
     * @return Der Name als std::string
     */
    std::string getName() const;

    /**
     * Rein virtuelle Methode: evaluate()
     * Berechnet den Ausgang basierend auf den verbundenen Eingängen (Pull-Prinzip)
     * Diese Methode MUSS von jeder abgeleiteten Klasse implementieren.
     */
    virtual void evaluate() = 0;

    /**
     * Löscht den Cache (Phase 4: Memoization)
     * Wird vor jedem neuen Testfall aufgerufen, damit nicht alte Werte gecacht werden
     */
    virtual void reset() {
        m_isCalculated = false;
    }

    /**
     * Gibt den aktuellen Zustand des Gatters aus
     */
    virtual void printState() const = 0;

    /**
     * Virtueller Destruktor: Sichert korrekte Cleanup-Reihenfolge bei Polymorphismus
     */
    virtual ~Gate();
};

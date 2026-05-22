#pragma once

#include <string>
#include <iostream>

/**
 * Component (Basisklasse) - Abstraktion für alle Logikgatter
 * 
 * Diese Klasse kapselt die gemeinsamen Eigenschaften und Methoden aller Komponenten:
 * - Name des Bauteils
 * - Zwei Eingänge (inA, inB)
 * - Ein Ausgang (output)
 * 
 * Alle spezifischen Gatter (AndGate, OrGate, NotGate, etc.) erben von dieser Klasse
 * und müssen die reine virtuelle Methode update() implementieren.
 */
class Component {
protected:
    // Geschützte Attribute: Nur diese Klasse und ihre Abkömmlinge können darauf zugreifen
    std::string name;
    bool inA;
    bool inB;
    bool output;

public:
    /**
     * Konstruktor: Initialisiert ein Bauteil mit Namen
     * @param n Der Name des Bauteils (z.B. "Haupt-AND", "Eingang-OR")
     */
    Component(std::string n);

    /**
     * Setzt Eingang A auf 0 oder 1
     * @param val Eingangswert (0 oder 1)
     */
    virtual void setInputA(int val);

    /**
     * Setzt Eingang B auf 0 oder 1
     * @param val Eingangswert (0 oder 1)
     */
    virtual void setInputB(int val);

    /**
     * Gibt den aktuellen Ausgangswert zurück
     * @return true wenn output=1, false wenn output=0
     */
    bool getOutput() const;

    /**
     * Rein virtuelle Methode: evaluate()
     * Berechnet den Ausgang basierend auf den Eingängen.
     * Diese Methode MUSS von jeder abgeleiteten Klasse implementiert werden.
     * @return true wenn output=1, false wenn output=0
     */
    virtual bool evaluate() = 0;

    /**
     * Gibt den aktuellen Zustand des Bauteils aus
     */
    virtual void printState() const = 0;

    /**
     * Virtueller Destruktor: Sichert korrekte Cleanup-Reihenfolge bei Polymorphismus
     */
    virtual ~Component();
};

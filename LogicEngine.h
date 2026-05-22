#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Component.h"

/**
 * Die LogicEngine ist der Kern unseres Simulators.
 * Sie verwaltet eine Liste von Komponenten polymorphisch.
 * 
 * Das Schlüsselkonzept: Wir speichern Zeiger auf die Basisklasse Component,
 * aber die Engine "weiß" nicht, welcher konkrete Typ verborgen ist.
 * Durch polymorphe Aufrufe werden die richtigen Gatter-Logiken ausgeführt!
 */
class LogicEngine {
private:
    std::string circuitName;
    int tickCount;
    std::vector<std::unique_ptr<Component>> circuit;  // Smart Pointers verwalten Speicher

public:
    // Konstruktor: Initialisiert die Engine
    LogicEngine();

    // Destruktor: Räumt die Komponenten auf
    ~LogicEngine();

    // Setzt den Namen der Schaltung
    void setCircuitName(std::string name);

    // Fügt eine Komponente polymorphisch zur Schaltung hinzu (übernimmt Ownership)
    void addComponent(std::unique_ptr<Component> comp);

    // =====================================================================
    // ZUSATZAUFGABE 2: Speichermanagement optimieren
    // =====================================================================
    // Reserviert Speicherplatz für eine bestimmte Anzahl von Komponenten
    // Dies verhindert, dass der Vektor ständig seinen Speicherbereich umzieht
    // (Heap-Reallokationen) wenn neue Komponenten hinzugefügt werden.
    void reserveComponents(int expectedCount);

    // Berechnet einen Taktschritt: Evaluiert alle Komponenten
    void doTick();

    // Gibt die Anzahl der Komponenten zurück
    int getComponentCount() const;
};
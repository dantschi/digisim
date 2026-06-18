#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Component.h"

/**
 * Die LogicEngine ist der Kern unseres Simulators.
 * Sie verwaltet eine Liste von Komponenten polymorphisch.
 * 
 * Das Schlüsselkonzept: Wir speichern Zeiger auf die Basisklasse Gate,
 * aber die Engine "weiß" nicht, welcher konkrete Typ verborgen ist.
 * Durch polymorphe Aufrufe werden die richtigen Gatter-Logiken ausgeführt!
 */
class LogicEngine {
private:
    std::string circuitName;
    int tickCount;
    std::vector<std::unique_ptr<Gate>> circuit;  // Smart Pointers verwalten Speicher
    bool verbose = false;  // Kontrolliert die Ausgabemenge der Konsole

public:
    // Konstruktor: Initialisiert die Engine
    LogicEngine();

    // Destruktor: Räumt die Komponenten auf
    ~LogicEngine();

    // Setzt den Namen der Schaltung
    void setCircuitName(std::string name);

    // Fügt eine Komponente polymorphisch zur Schaltung hinzu (übernimmt Ownership)
    void addComponent(std::unique_ptr<Gate> comp);

    // =====================================================================
    // ZUSATZAUFGABE 2: Speichermanagement optimieren
    // =====================================================================
    // Reserviert Speicherplatz für eine bestimmte Anzahl von Komponenten
    // Dies verhindert, dass der Vektor ständig seinen Speicherbereich umzieht
    // (Heap-Reallokationen) wenn neue Komponenten hinzugefügt werden.
    void reserveComponents(int expectedCount);

    // Setzt den Debug-Modus: true = ausführliche Konsolenausgabe, false = minimal
    void setVerbose(bool v);

    // Berechnet einen Taktschritt: Evaluiert alle Komponenten
    void doTick();

    // Gibt die Anzahl der Komponenten zurück
    int getComponentCount() const;

    // =====================================================================
    // Phase 2: Datei-I/O für .circuit Format
    // =====================================================================
    
    /**
     * Sucht ein Gatter nach seinem Namen
     * @param name Der Name des gesuchten Gatters
     * @return Raw Pointer auf das Gatter, oder nullptr wenn nicht gefunden
     * 
     * WICHTIG: Der zurückgegebene Pointer ist Non-Owning!
     * Die LogicEngine behält die Ownership über das Objekt.
     */
    Gate* getGateByName(const std::string& name);
    
    /**
     * Lädt eine .circuit Datei und baut die Schaltung automatisch auf
     * 
     * Format:
     *   GATE <type> <name>   (z.B. GATE AND myAnd1)
     *   WIRE <target> <pin> <source>  (z.B. WIRE myAnd1 0 swA)
     * 
     * @param filename Der Pfad zur .circuit Datei
     */
    void loadFromFile(const std::string& filename);
    
    /**
     * Speichert die aktuelle Schaltung in eine .circuit Datei
     * @param filename Der Ziel-Pfad
     */
    void saveToFile(const std::string& filename);
};
#include "LogicEngine.h"
#include <iostream>

// ============================================
// LogicEngine Implementation
// ============================================

/**
 * Konstruktor: Initialisiert die Engine
 */
LogicEngine::LogicEngine() 
    : circuitName("Unbenannt"), tickCount(0) {
    std::cout << "[LogicEngine] Engine initialisiert" << std::endl;
}

/**
 * Destruktor: Die unique_ptr's kümmern sich AUTOMATISCH um Cleanup
 * Der Vektor wird zerstört, und alle unique_ptr's geben ihre Ressourcen frei.
 * Dies löst automatisch die Destruktoren aller Komponenten aus!
 */
LogicEngine::~LogicEngine() {
    // circuit.clear() ist hier nicht nötig - wird automatisch aufgeräumt
}

/**
 * Setzt den Namen der Schaltung
 */
void LogicEngine::setCircuitName(std::string name) {
    circuitName = name;
    std::cout << "[LogicEngine] Schaltungsname gesetzt: " << circuitName << std::endl;
}

/**
 * Fügt eine Komponente zur Schaltung hinzu (übernimmt Ownership)
 * Der unique_ptr wird mit std::move übernommen (Ownership-Transfer)
 * Ab diesem Punkt verwaltet die Engine den Speicher!
 */
void LogicEngine::addComponent(std::unique_ptr<Component> comp) {
    if (comp != nullptr) {
        circuit.push_back(std::move(comp));
        std::cout << "[LogicEngine] Komponente hinzugefügt. Gesamt: " << circuit.size() << std::endl;
    }
}

/**
 * doTick(): Der Kern der Simulation!
 * 
 * Dies ist der erste praktische Beispiel für Polymorphismus:
 * Wir wissen nicht, welchen konkreten Typ jede Komponente hat,
 * aber der Compiler generiert automatisch die richtigen virtuellen Aufrufe!
 */
void LogicEngine::doTick() {
    tickCount++;
    std::cout << "\n[Tick " << tickCount << "] Evaluiere " << circuit.size() 
              << " Komponenten:" << std::endl;
    
    for (auto& c : circuit) {
        // Polymorphe Funktion: Der Compiler findet automatisch die richtige evaluate()-Methode!
        bool result = c->evaluate();
        std::cout << "  => Ergebnis: " << (result ? "true" : "false") << std::endl;
    }
}

/**
 * Gibt die Anzahl der Komponenten zurück
 */
int LogicEngine::getComponentCount() const {
    return circuit.size();
}

// =====================================================================
// ZUSATZAUFGABE 2: Speichermanagement optimieren (Advanced)
// =====================================================================

/**
 * Reserviert Speicher für eine bestimmte Anzahl von Komponenten.
 * 
 * WARUM DAS WICHTIG IST:
 * =====================
 * Ein std::vector speichert intern ein Array auf dem Heap.
 * Wenn der Vektor wächst:
 * 
 *   1. Vektor ist leer (Kapazität = 0)
 *   2. Erste Komponente: Allokation für 1 Element
 *   3. Zweite Komponente: Vektor voll! -> REALLOKAION:
 *      - Neuer, größerer Block wird allokiert (z.B. Platz für 2)
 *      - Alte Elemente werden kopiert/verschoben
 *      - Altes Array wird freigegeben
 *   4. Bei jeder Verdopplung der Größe passiert das wieder!
 * 
 * Mit reserve() sagen wir dem Vektor VOR ZEIT:
 * "Reserviere mir Platz für N Elemente auf einmal!"
 * -> Keine Reallokationen während push_back() Aufrufen
 * -> Bessere Performance + weniger Speicher-Fragmentierung
 * 
 * PERFORMANCE-IMPACT:
 * - OHNE reserve(): Bei 100 Komponenten ~7 Reallokationen
 * - MIT reserve(100): Bei 100 Komponenten 1 Allokation
 * 
 * @param expectedCount Wie viele Komponenten werden erwartet?
 */
void LogicEngine::reserveComponents(int expectedCount) {
    if (expectedCount <= 0) {
        std::cerr << "[LogicEngine] Warnung: expectedCount muss > 0 sein!" << std::endl;
        return;
    }
    
    // reserve() allokiert Speicher, aber erhöht size() NICHT!
    // Das ist der Unterschied zu resize()!
    circuit.reserve(expectedCount);
    
    std::cout << "[LogicEngine] Speicher reserviert für " << expectedCount 
              << " Komponenten. Aktuelle Kapazität: " << circuit.capacity() 
              << " (size: " << circuit.size() << ")" << std::endl;
}

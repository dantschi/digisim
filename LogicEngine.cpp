#include "LogicEngine.h"
#include "DFlipFlop.h"
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
void LogicEngine::addComponent(std::unique_ptr<Gate> comp) {
    if (comp != nullptr) {
        circuit.push_back(std::move(comp));
        std::cout << "[LogicEngine] Komponente hinzugefügt. Gesamt: " << circuit.size() << std::endl;
    }
}

/**
 * doTick(): Der Kern der Simulation - 2-Phasen-Zyklus
 * 
 * Dies ist ein praktisches Beispiel für Polymorphismus mit dynamic_cast.
 * Wir durchlaufen den Vektor mit Gate-Pointern und nutzen RTTI (Run-Time Type Info),
 * um herauszufinden, welche Komponenten tatsächlich DFlipFlops sind!
 * 
 * Phasen der Simulation:
 * =====================
 * 1. RESET-Phase: Alle Gates "vergessen" ihre Cachewerte (Amnesie)
 * 2. EVALUATE-Phase: Alle Gates berechnen ihre kombinatorische Logik
 * 3. CLOCK-Phase: Nur DFlipFlops werden aktualisiert (Speicher-Schreib-Phase)
 * 
 * Warum das funktioniert:
 * - evaluate() ist virtuell -> richtige Gatter-Logik wird aufgerufen
 * - dynamic_cast<DFlipFlop*> identifiziert Flip-Flops zur Laufzeit
 * - onClockTick() existiert NUR auf DFlipFlop, nicht auf normalen Gates
 */
void LogicEngine::doTick() {
    tickCount++;
    if (verbose) {
        std::cout << "\n[Tick " << tickCount << "] ========================================" << std::endl;
        std::cout << "[Tick " << tickCount << "] Starte 2-Phasen-Zyklus für " << circuit.size() << " Komponenten" << std::endl;
    }
    
    // ===== PHASE 1: RESET (Löschen des Cache) =====
    if (verbose) {
        std::cout << "\n[Tick " << tickCount << "] PHASE 1: RESET - Lösche Cachewerte..." << std::endl;
    }
    for (auto& comp : circuit) {
        comp->reset();
    }
    if (verbose) {
        std::cout << "[Tick " << tickCount << "] RESET abgeschlossen." << std::endl;
    }
    
    // ===== PHASE 2: EVALUATE (Kombinatorik berechnen) =====
    if (verbose) {
        std::cout << "\n[Tick " << tickCount << "] PHASE 2: EVALUATE - Berechne Logik..." << std::endl;
    }
    for (auto& comp : circuit) {
        comp->evaluate();
        if (verbose) {
            std::cout << "[Tick " << tickCount << "]   ✓ " << comp->getName() 
                      << " => Output: " << (comp->getOutput() ? "1" : "0") << std::endl;
        }
    }
    
    // ===== PHASE 3: CLOCK (Flip-Flops aktualisieren) =====
    if (verbose) {
        std::cout << "\n[Tick " << tickCount << "] PHASE 3: CLOCK - Update Flip-Flops..." << std::endl;
    }
    int flipFlopCount = 0;
    for (auto& comp : circuit) {
        // Versuche zu prüfen, ob diese Komponente ein DFlipFlop ist
        // dynamic_cast<DFlipFlop*>() gibt:
        //   - Ein valider Pointer, wenn comp wirklich ein DFlipFlop ist
        //   - nullptr, wenn comp kein DFlipFlop ist
        DFlipFlop* flipFlop = dynamic_cast<DFlipFlop*>(comp.get());
        
        if (flipFlop != nullptr) {
            // Das IST ein DFlipFlop -> rufe onClockTick() auf
            if (verbose) {
                std::cout << "[Tick " << tickCount << "]   ⏱ " << comp->getName() 
                          << " erhält Taktsignal (onClockTick)" << std::endl;
            }
            flipFlop->onClockTick();
            flipFlopCount++;
        }
    }
    if (verbose) {
        std::cout << "[Tick " << tickCount << "] " << flipFlopCount << " Flip-Flop(s) aktualisiert." << std::endl;
        std::cout << "\n[Tick " << tickCount << "] ========================================" << std::endl;
    }
}

/**
 * Gibt die Anzahl der Komponenten zurück
 */
int LogicEngine::getComponentCount() const {
    return circuit.size();
}

/**
 * Setzt den Verbose-Modus für die Konsolenausgabe
 * true = alle Debug-Ausgaben der doTick()-Methode werden angezeigt
 * false = nur die wichtigsten Meldungen (Default - saubere Konsole für Timing-Diagramme)
 * 
 * Verwendung: engine.setVerbose(true) für vollständiges Debug-Tracking
 */
void LogicEngine::setVerbose(bool v) {
    verbose = v;
    if (verbose) {
        std::cout << "[LogicEngine] Verbose-Modus aktiviert: Alle Takt-Details werden angezeigt" << std::endl;
    } else {
        std::cout << "[LogicEngine] Verbose-Modus deaktiviert: Nur minimale Ausgabe" << std::endl;
    }
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

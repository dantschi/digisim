#include "LogicEngine.h"
#include "DFlipFlop.h"
#include "GateFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

// =====================================================================
// Phase 2: Datei-I/O für .circuit Format
// =====================================================================

/**
 * Sucht ein Gatter nach seinem Namen
 */
Gate* LogicEngine::getGateByName(const std::string& name) {
    for (auto& comp : circuit) {
        if (comp->getName() == name) {
            return comp.get();  // Gib Raw Pointer zurück (Non-Owning!)
        }
    }
    // Nicht gefunden
    std::cerr << "[LogicEngine] FEHLER: Gatter '" << name << "' nicht gefunden!" << std::endl;
    return nullptr;
}

/**
 * Lädt eine .circuit Datei und baut die Schaltung automatisch auf
 * 
 * Format der Datei:
 * - Zeilen mit GATE erstellen neue Komponenten über die Factory
 * - Zeilen mit WIRE verbinden die Gatter
 * 
 * Parsing:
 * - std::stringstream zerlegt jede Zeile an Leerzeichen
 * - Blanke Zeilen und Kommentare werden ignoriert
 */
void LogicEngine::loadFromFile(const std::string& filename) {
    std::cout << "\n[LogicEngine] Lade Schaltung aus Datei: " << filename << std::endl;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[LogicEngine ERROR] Kann Datei nicht öffnen: " << filename << std::endl;
        return;
    }
    
    std::string line;
    int lineNumber = 0;
    int gateCount = 0, wireCount = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        
        // Ignoriere leere Zeilen
        if (line.empty()) continue;
        
        // Ignoriere Kommentare (Zeilen die mit # oder // beginnen)
        if (line[0] == '#' || (line.length() > 1 && line[0] == '/' && line[1] == '/')) {
            continue;
        }
        
        // Parse die Zeile mit stringstream
        std::stringstream ss(line);
        std::string command;
        ss >> command;  // Erstes Wort extrahieren
        
        // ===== GATE Zeilen =====
        if (command == "GATE") {
            std::string type, name;
            ss >> type >> name;
            
            if (type.empty() || name.empty()) {
                std::cerr << "[LogicEngine WARNING] Zeile " << lineNumber 
                          << ": GATE Format ungültig" << std::endl;
                continue;
            }
            
            // Nutze die Factory, um das Gatter zu erstellen
            auto gate = GateFactory::createGate(type, name);
            if (gate == nullptr) {
                std::cerr << "[LogicEngine ERROR] Zeile " << lineNumber 
                          << ": Unbekannter Gatter-Typ '" << type << "'" << std::endl;
                continue;
            }
            
            // Füge das neue Gatter der Engine hinzu
            addComponent(std::move(gate));
            gateCount++;
        }
        
        // ===== WIRE Zeilen =====
        else if (command == "WIRE") {
            std::string targetName, sourceName;
            int pin = -1;
            ss >> targetName >> pin >> sourceName;
            
            if (targetName.empty() || pin < 0 || sourceName.empty()) {
                std::cerr << "[LogicEngine WARNING] Zeile " << lineNumber 
                          << ": WIRE Format ungültig (Syntax: WIRE <target> <pin> <source>)" << std::endl;
                continue;
            }
            
            // Finde beide Gatter
            Gate* target = getGateByName(targetName);
            Gate* source = getGateByName(sourceName);
            
            if (target == nullptr || source == nullptr) {
                std::cerr << "[LogicEngine ERROR] Zeile " << lineNumber 
                          << ": Gatter nicht gefunden" << std::endl;
                continue;
            }
            
            // Verbinde sie
            target->connectInput(pin, source);
            wireCount++;
        }
        
        // Unbekannter Befehl - ignorieren
        else if (!command.empty()) {
            std::cerr << "[LogicEngine WARNING] Zeile " << lineNumber 
                      << ": Unbekannter Befehl '" << command << "'" << std::endl;
        }
    }
    
    file.close();
    
    std::cout << "[LogicEngine] Datei geladen: " << gateCount << " Gatter, " 
              << wireCount << " Verbindungen" << std::endl << std::endl;
}

/**
 * Speichert die aktuelle Schaltung in eine .circuit Datei
 * 
 * Prozess:
 * 1. Schreibe alle GATE-Zeilen (mit Hilfe der virtuellen getType() Methode)
 * 2. Schreibe alle WIRE-Zeilen (indem wir die Inputs durchsuchen)
 */
void LogicEngine::saveToFile(const std::string& filename) {
    std::cout << "\n[LogicEngine] Speichere Schaltung in Datei: " << filename << std::endl;
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[LogicEngine ERROR] Kann Datei nicht zum Schreiben öffnen: " << filename << std::endl;
        return;
    }
    
    // ===== Phase 1: Schreibe alle GATE-Zeilen =====
    file << "# Automatisch generierte .circuit Datei" << std::endl;
    file << "# Format: GATE <type> <name>" << std::endl;
    file << "# Format: WIRE <target> <pin> <source>" << std::endl << std::endl;
    
    file << "# ===== Bauteile =====" << std::endl;
    for (const auto& comp : circuit) {
        file << "GATE " << comp->getType() << " " << comp->getName() << std::endl;
    }
    
    file << std::endl << "# ===== Verbindungen =====" << std::endl;
    
    // ===== Phase 2: Schreibe alle WIRE-Zeilen =====
    for (const auto& target : circuit) {
        const auto& inputs = target->getInputs();
        
        // Durchsuche alle Eingänge des Ziel-Gatters
        for (size_t pinIndex = 0; pinIndex < inputs.size(); pinIndex++) {
            Gate* sourceGate = inputs[pinIndex];
            
            // Ignoriere nullptr-Eingänge (nicht verbundene Pins)
            if (sourceGate != nullptr) {
                file << "WIRE " << target->getName() 
                     << " " << pinIndex 
                     << " " << sourceGate->getName() << std::endl;
            }
        }
    }
    
    file.close();
    std::cout << "[LogicEngine] Schaltung gespeichert!" << std::endl << std::endl;
}

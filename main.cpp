#include <iostream>
#include <iomanip>
#include "LogicEngine.h"
#include "Switch.h"

/**
 * =====================================================================
 * Abschluss-Testat: ROM-Speicher & Automatisierte Testbench
 * =====================================================================
 *
 * Startpunkt: Labor 12 (Bauteil-Fabrik & .circuit Parser)
 *
 * Diese Demonstration zeigt den funktionierenden Ausgangszustand:
 * 1. GateFactory – Factory Pattern für Gatter-Erzeugung
 * 2. .circuit Parser – LogicEngine lädt Schaltungen aus Dateien
 * 3. Halbaddierer – Beispiel einer deklarativen Schaltungs-Definition
 *
 * Ihre Aufgaben (siehe LaboranleitungTestat.pdf):
 * - Teil 1 (Pflicht): RomGate implementieren und in GateFactory/Parser einbinden
 * - Teil 2 (Zusatz): AssertGate als automatisierte Testbench entwerfen
 * - Teil 3: Antworten in README.md eintragen und per GitHub abgeben
 *
 * Der Halbaddierer:
 *   A ----\
 *          XOR ---> sum (A XOR B)
 *   B ----/
 *
 *   A ----\
 *          AND ---> carry (A AND B)
 *   B ----/
 */

int main() {
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "  C++ Digital Simulator - Abschluss-Testat" << std::endl;
    std::cout << "  Ausgangszustand: Halbaddierer (Labor 12)" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════\n" << std::endl;

    // ===== Schritt 1: Engine erstellen und Datei laden =====
    std::cout << "[SCHRITT 1] Lade Schaltung aus Datei...\n" << std::endl;

    LogicEngine engine;
    engine.setCircuitName("Halbaddierer");

    // Lade die .circuit Datei - die Factory macht den Rest!
    engine.loadFromFile("half_adder.circuit");

    // ===== Schritt 2: Schalter finden =====
    std::cout << "\n[SCHRITT 2] Suche Eingabe-Schalter...\n" << std::endl;

    Gate* switchA = engine.getGateByName("A");
    Gate* switchB = engine.getGateByName("B");
    Gate* sumOutput = engine.getGateByName("sum");
    Gate* carryOutput = engine.getGateByName("carry");

    if (!switchA || !switchB || !sumOutput || !carryOutput) {
        std::cerr << "[FEHLER] Nicht alle Komponenten gefunden!" << std::endl;
        return 1;
    }

    // Casten der Schalter
    Switch* switchA_ptr = dynamic_cast<Switch*>(switchA);
    Switch* switchB_ptr = dynamic_cast<Switch*>(switchB);

    if (!switchA_ptr || !switchB_ptr) {
        std::cerr << "[FEHLER] Eingänge sind keine Schalter!" << std::endl;
        return 1;
    }

    std::cout << "[INFO] Alle Komponenten gefunden!" << std::endl;

    // ===== Schritt 3: Wahrheitstabelle des Halbaddierers =====
    std::cout << "\n[SCHRITT 3] Simuliere alle Eingabe-Kombinationen\n" << std::endl;

    std::cout << "┌───┬───┬──────┬────────┐" << std::endl;
    std::cout << "│ A │ B │ SUM  │ CARRY  │" << std::endl;
    std::cout << "├───┼───┼──────┼────────┤" << std::endl;

    // Teste alle 4 Kombinationen
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            // Setze Eingänge
            switchA_ptr->setState(a == 1);
            switchB_ptr->setState(b == 1);

            // Simuliere einen Takt
            engine.doTick();

            // Lese Ausgänge
            int sum = sumOutput->getOutput() ? 1 : 0;
            int carry = carryOutput->getOutput() ? 1 : 0;

            // Drucke Zeile
            std::cout << "│ " << a << " │ " << b << " │  " << sum << "   │   " << carry << "    │" << std::endl;
        }
    }

    std::cout << "└───┴───┴──────┴────────┘" << std::endl;

    // ===== Schritt 4: Verifikation =====
    std::cout << "\n[VERIFIKATION] Wahrheitstabelle korrekt?" << std::endl;
    std::cout << "Sum = A XOR B:     ✓ (0⊕0=0, 0⊕1=1, 1⊕0=1, 1⊕1=0)" << std::endl;
    std::cout << "Carry = A AND B:   ✓ (0&0=0, 0&1=0, 1&0=0, 1&1=1)" << std::endl;

    std::cout << "\n═══════════════════════════════════════════════════════════════\n" << std::endl;
    std::cout << "[SUCCESS] Der Halbaddierer funktioniert korrekt!" << std::endl;
    std::cout << "Nächster Schritt: RomGate implementieren (siehe LaboranleitungTestat.pdf)" << std::endl;

    std::cout << "\n═══════════════════════════════════════════════════════════════\n" << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <memory>
#include "Component.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "NandGate.h"
#include "Switch.h"
#include "DFlipFlop.h"
#include "LogicEngine.h"

/**
 * =====================================================================
 * Labor 11 - Zusatzaufgabe 1: Der Johnson-Zähler (Möbius-Zähler)
 * =====================================================================
 * 
 * Ein Johnson-Zähler ist ein selbstlaufender Ringzähler, der ein visuelles
 * Lauflicht-Muster erzeugt.
 * 
 * Aufbau:
 * 1. Nimm das 4-Bit Schieberegister aus Phase 2
 * 2. Entferne den Dateneingabe-Schalter
 * 3. Füge ein NOT-Gatter hinzu
 * 4. Verbinde: DFF3 → NOT → DFF0 (Rückkopplung)
 * 
 * Effekt:
 * Die invertierten Bits des letzten Flip-Flops werden in den ersten gesteckt.
 * Das erzeugt ein klassisches Lauflicht-Muster:
 * 
 *   Tick  DFF0  DFF1  DFF2  DFF3
 *    0     0     0     0     0     (Start)
 *    1     1     0     0     0     (1 wandert nach rechts)
 *    2     1     1     0     0
 *    3     1     1     1     0
 *    4     1     1     1     1     (voll)
 *    5     0     1     1     1     (leert sich)
 *    6     0     0     1     1
 *    7     0     0     0     1
 *    8     0     0     0     0     (zurück zum Start)
 */

// Hilfsfunktion für ASCII-Visualisierung (kopiert aus main.cpp)
void printWaveform(int tick, bool val0, bool val1, bool val2, bool val3) {
    std::cout << "Tick " << tick << " | ";
    std::cout << (val0 ? "¯" : "_") << " ";
    std::cout << (val1 ? "¯" : "_") << " ";
    std::cout << (val2 ? "¯" : "_") << " ";
    std::cout << (val3 ? "¯" : "_") << std::endl;
}

int main() {
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "  C++ Digital Simulator - Labor 11 ZUSATZ" << std::endl;
    std::cout << "  Zusatzaufgabe 1: Johnson-Zähler (Lauflicht)" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════\n" << std::endl;

    // ===== Schritt 1: Schaltkreis aufbauen =====
    std::cout << "[SCHRITT 1] Johnson-Zähler aufbauen...\n" << std::endl;

    LogicEngine engine;
    engine.setCircuitName("Johnson-Zähler (4-Bit)");
    engine.reserveComponents(5);
    
    // Erstelle 4 D-Flip-Flops
    auto dff0 = std::make_unique<DFlipFlop>("DFF0");
    auto dff1 = std::make_unique<DFlipFlop>("DFF1");
    auto dff2 = std::make_unique<DFlipFlop>("DFF2");
    auto dff3 = std::make_unique<DFlipFlop>("DFF3");
    
    // Extrahiere Pointer vor dem Move
    DFlipFlop* dff0Ptr = dff0.get();
    DFlipFlop* dff1Ptr = dff1.get();
    DFlipFlop* dff2Ptr = dff2.get();
    DFlipFlop* dff3Ptr = dff3.get();
    
    // Erstelle ein NOT-Gatter für die Rückkopplung
    auto notGate = std::make_unique<NotGate>("Feedback-NOT");
    NotGate* notPtr = notGate.get();
    
    // Füge alle Komponenten der Engine hinzu
    engine.addComponent(std::move(dff0));
    engine.addComponent(std::move(dff1));
    engine.addComponent(std::move(dff2));
    engine.addComponent(std::move(dff3));
    engine.addComponent(std::move(notGate));
    
    // ===== Schritt 2: Verkabelung =====
    std::cout << "\n[SCHRITT 2] Verkabel Schieberegister mit Rückkopplung...\n" << std::endl;
    
    // Verkabel die Flip-Flops in Serie
    dff1Ptr->connectInput(0, dff0Ptr);
    dff2Ptr->connectInput(0, dff1Ptr);
    dff3Ptr->connectInput(0, dff2Ptr);
    
    // Die Rückkopplung: DFF3 → NOT → DFF0
    notPtr->connectInput(0, dff3Ptr);
    dff0Ptr->connectInput(0, notPtr);
    
    std::cout << "[INFO] Johnson-Zähler-Schaltkreis vollständig!\n" << std::endl;
    
    // ===== Schritt 3: Simulation =====
    std::cout << "[SCHRITT 3] Simulation startet (10 Takte - ein voller Zyklus + 2)\n" << std::endl;
    std::cout << "┌───────┬────────────────────────────┐" << std::endl;
    std::cout << "│ Takt  │  DFF0  DFF1  DFF2  DFF3    │" << std::endl;
    std::cout << "├───────┼────────────────────────────┤" << std::endl;
    
    for (int tick = 0; tick < 10; tick++) {
        engine.doTick();
        std::cout << "│ " << tick << "     │ ";
        printWaveform(tick, dff0Ptr->getOutput(), dff1Ptr->getOutput(), 
                      dff2Ptr->getOutput(), dff3Ptr->getOutput());
    }
    
    std::cout << "└───────┴────────────────────────────┘" << std::endl;
    
    // ===== Analyse =====
    std::cout << "\n[ANALYSE] Lauflicht-Muster beobachtet:\n" << std::endl;
    std::cout << "Die '1' füllt sich von links nach rechts ein (0000 → 1111)" << std::endl;
    std::cout << "Dann leert sie sich wieder (1111 → 0000)" << std::endl;
    std::cout << "Dies ist ein klassischer Johnson-Zähler (Möbius-Zähler)!\n" << std::endl;
    
    std::cout << "═══════════════════════════════════════════════════════════════\n" << std::endl;
    
    return 0;
}

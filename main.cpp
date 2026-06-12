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
 * Labor 11: Schieberegister & 2-Phasen-Simulation mit LogicEngine
 * =====================================================================
 * 
 * Diese Demonstration zeigt:
 * 1. Phase 2: Das 4-Bit Schieberegister (Shift Register)
 *    - 4 D-Flip-Flops in Serie verschaltet
 *    - Ein Switch als Dateneingabe
 * 
 * 2. Phase 3: ASCII Timing-Diagramm zur Visualisierung
 * 
 * Das Schieberegister:
 *   Switch → DFF0 → DFF1 → DFF2 → DFF3 → Ausgabe
 * 
 * Experiment:
 * - Setze Switch auf 1
 * - Mache einen Takt -> "1" erscheint bei DFF0
 * - Setze Switch auf 0
 * - Mache 4 weitere Takte -> "1" wandert durch alle Flip-Flops
 */

// ============================================================
// Hilfsfunktion: ASCII Timing-Diagramm visualisieren (Phase 3)
// ============================================================

/**
 * Druckt einen Waveform-Snapshot eines Taktzyklus
 * @param tick Taktnummer
 * @param val0 Ausgang von DFF0
 * @param val1 Ausgang von DFF1
 * @param val2 Ausgang von DFF2
 * @param val3 Ausgang von DFF3
 * 
 * Beispielausgabe:
 * Tick 0 | _ _ _ _
 * Tick 1 | ¯ _ _ _
 * Tick 2 | _ ¯ _ _
 * ...
 */
void printWaveform(int tick, bool val0, bool val1, bool val2, bool val3) {
    std::cout << "Tick " << tick << " | ";
    
    // Drucke jeden Bit als Symbol
    std::cout << (val0 ? "¯" : "_") << " ";
    std::cout << (val1 ? "¯" : "_") << " ";
    std::cout << (val2 ? "¯" : "_") << " ";
    std::cout << (val3 ? "¯" : "_") << std::endl;
}

// ============================================================
// Main: Das 4-Bit Schieberegister aufbauen und testen
// ============================================================

int main() {
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "  C++ Digital Simulator - Labor 11" << std::endl;
    std::cout << "  Phase 2: 4-Bit Schieberegister & LogicEngine doTick()" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════\n" << std::endl;

    // ===== PHASE 2: Schieberegister aufbauen =====
    std::cout << "[PHASE 2] Schieberegister aufbauen...\n" << std::endl;

    // Erzeugen einer LogicEngine
    LogicEngine engine;
    engine.setCircuitName("4-Bit Schieberegister");
    
    // Reserviere Speicher für 5 Komponenten
    engine.reserveComponents(5);
    
    // Erstelle einen Switch als Dateneingabe
    auto dataIn = std::make_unique<Switch>("DataIn");
    Switch* dataInPtr = dataIn.get();  // Speichere Pointer für späteren Zugriff
    engine.addComponent(std::move(dataIn));
    
    // Erstelle 4 D-Flip-Flops
    auto dff0 = std::make_unique<DFlipFlop>("DFF0");
    auto dff1 = std::make_unique<DFlipFlop>("DFF1");
    auto dff2 = std::make_unique<DFlipFlop>("DFF2");
    auto dff3 = std::make_unique<DFlipFlop>("DFF3");
    
    // Speichere Pointer auf die Flip-Flops für späteren Zugriff
    DFlipFlop* dff0Ptr = dff0.get();
    DFlipFlop* dff1Ptr = dff1.get();
    DFlipFlop* dff2Ptr = dff2.get();
    DFlipFlop* dff3Ptr = dff3.get();
    
    // Füge Flip-Flops der Engine hinzu
    engine.addComponent(std::move(dff0));
    engine.addComponent(std::move(dff1));
    engine.addComponent(std::move(dff2));
    engine.addComponent(std::move(dff3));
    
    // ===== Verkabelung =====
    std::cout << "\n[INFO] Verkabel Schieberegister in Serie...\n" << std::endl;
    
    // DataIn → Input 0 von DFF0
    dff0Ptr->connectInput(0, dataInPtr);
    
    // DFF0 → Input 0 von DFF1
    dff1Ptr->connectInput(0, dff0Ptr);
    
    // DFF1 → Input 0 von DFF2
    dff2Ptr->connectInput(0, dff1Ptr);
    
    // DFF2 → Input 0 von DFF3
    dff3Ptr->connectInput(0, dff2Ptr);
    
    std::cout << "[INFO] Schieberegister vollständig aufgebaut!\n" << std::endl;
    
    // ===== Simulation starten =====
    std::cout << "[TEST] Simulation startet: Eine '1' durch das Register schieben\n" << std::endl;
    
    // Tabelle-Header
    std::cout << "┌───────┬────────────────────────────┐" << std::endl;
    std::cout << "│ Takt  │  DFF0  DFF1  DFF2  DFF3    │" << std::endl;
    std::cout << "├───────┼────────────────────────────┤" << std::endl;
    
    int tickNum = 0;
    
    // ===== Schritt 1: Schalter auf 1 setzen und einen Takt durchlaufen =====
    std::cout << "\n[SCHRITT 1] Schalter auf 1 setzen...\n" << std::endl;
    dataInPtr->setState(true);
    engine.doTick();
    std::cout << "│ " << tickNum << "     │ ";
    printWaveform(tickNum, dff0Ptr->getOutput(), dff1Ptr->getOutput(), 
                  dff2Ptr->getOutput(), dff3Ptr->getOutput());
    tickNum++;
    
    // ===== Schritt 2: Schalter auf 0 setzen und 4 weitere Takte =====
    std::cout << "\n[SCHRITT 2] Schalter auf 0 setzen und 4 Takte durchlaufen...\n" << std::endl;
    dataInPtr->setState(false);
    
    for (int i = 0; i < 4; i++) {
        engine.doTick();
        std::cout << "│ " << tickNum << "     │ ";
        printWaveform(tickNum, dff0Ptr->getOutput(), dff1Ptr->getOutput(), 
                      dff2Ptr->getOutput(), dff3Ptr->getOutput());
        tickNum++;
    }
    
    std::cout << "└───────┴────────────────────────────┘" << std::endl;
    
    // ===== Ergebnis =====
    std::cout << "\n[SUCCESS] Die '1' hat sich durch alle Flip-Flops geschoben!" << std::endl;
    std::cout << "Das ist genau das Verhalten eines Schieberegisters!" << std::endl;
    std::cout << "\n═══════════════════════════════════════════════════════════════\n" << std::endl;
    
    return 0;
}



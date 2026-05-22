#include <iostream>
#include <vector>
#include <memory>
#include "Component.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "NandGate.h"
#include "LogicEngine.h"

/**
 * =====================================================================
 * ZUSATZAUFGABE 1: Der nackte Zeiger (Observer-Pattern)
 * =====================================================================
 * 
 * Diese Funktion nimmt einen nackten C++-Zeiger und liest den Zustand,
 * OHNE das Objekt zu kopieren oder zu verschieben.
 * Das ist ein "Read-Only Observer" - wie durchs Schlüsselloch schauen!
 */
void printGateInfo(Component* gate) {
    if (gate == nullptr) {
        std::cerr << "[ERROR] Ungültiger Zeiger in printGateInfo()" << std::endl;
        return;
    }
    
    std::cout << "\n[GateInfo] Komponenten-Status:" << std::endl;
    std::cout << "  Input A: " << (gate ? "vorhanden" : "NULL") << std::endl;
    std::cout << "  Output: " << (gate->getOutput() ? "1 (true)" : "0 (false)") << std::endl;
    gate->printState();  // Ruft die spezifische printState() des Gatters auf
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Labor 5: Speichersicherheit & Refactoring" << std::endl;
    std::cout << "Ausgangslage: Rohe Pointer und Memory Leaks" << std::endl;
    std::cout << "========================================\n" << std::endl;

    LogicEngine engine;
    engine.setCircuitName("Leak-Test-Schaltung");

    // =====================================================================
    // ZUSATZAUFGABE 2: Speichermanagement optimieren
    // =====================================================================
    std::cout << "\n[ZUSATZAUFGABE 2] Speicher reservieren, BEVOR Komponenten hinzugefügt werden:" << std::endl;
    engine.reserveComponents(10);  // Sag der Engine: "Ich werde ~10 Komponenten hinzufügen"
    std::cout << "  (Dies verhindert Reallokationen und verbessert die Performance!)" << std::endl;

    std::cout << "Baue Schaltung auf dem Heap mit Smart Pointern (Werden AUTOMATISCH gelöscht!)..." << std::endl;

    // ---------------------------------------------------------
    // MODERNER CODE: Nutzung von std::make_unique<T>()
    // Dies erzeugt einen std::unique_ptr, der den Speicher AUTOMATISCH freigibt!
    // ---------------------------------------------------------
    auto g1 = std::make_unique<AndGate>("Haupt-AND");
    auto g2 = std::make_unique<OrGate>("Haupt-OR");
    auto g3 = std::make_unique<XorGate>("Test-XOR");

    // WICHTIG: Eingänge setzen, BEVOR wir die Ownership übertragen!
    // Nach std::move können wir g1, g2, g3 nicht mehr verwenden!
    std::cout << "\nSetze Signale (VOR dem Ownership-Transfer)..." << std::endl;
    g1->setInputA(1);
    g1->setInputB(1);
    
    g2->setInputA(0);
    g2->setInputB(1);
    
    g3->setInputA(1);
    g3->setInputB(0);

    // Ownership an die Engine übergeben (mit std::move)
    // Nach diesen Aufrufen sind g1, g2, g3 "leere" unique_ptr's (nullptr)
    std::cout << "\nÜbergebe Komponenten an Engine (Ownership-Transfer)..." << std::endl;
    
    // VOR dem move: Wir können g1 noch normal nutzen
    std::cout << "\n[EXTRA] g1 VOR dem move:" << std::endl;
    printGateInfo(g1.get());  // .get() gibt den rohen Zeiger zurück (nur zum Lesen!)
    
    // Jetzt verschieben
    engine.addComponent(std::move(g1));
    engine.addComponent(std::move(g2));
    engine.addComponent(std::move(g3));
    
    std::cout << "\n[EXTRA] g1 NACH dem move: g1.get() = " << (g1.get() == nullptr ? "nullptr" : "???") << std::endl;
    std::cout << "  -> Versuch, g1->getOutput() zu rufen würde abstürzen!" << std::endl;
    std::cout << "  -> Das ist correct! g1 hat den Ownership verloren!" << std::endl;

    // Simulation einmal durchrechnen
    std::cout << "\nStarte Simulation:" << std::endl;
    engine.doTick();

    std::cout << "\nProgramm wird beendet..." << std::endl;
    std::cout << "(Die Destruktoren sollten automatisch aufgerufen werden)" << std::endl;

    // KORREKT: Nichts zu tun! unique_ptr und der Engine-Destruktor kümmern sich darum!
    
    return 0;
}
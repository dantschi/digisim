#include <iostream>
#include <fstream>
#include "LogicEngine.h"
#include "Switch.h"

/**
 * =====================================================================
 * Labor 12: Zusatzaufgabe 1 - saveToFile() Test
 * =====================================================================
 * 
 * Diese Demo zeigt, dass saveToFile() korrekt funktioniert:
 * 1. Lade eine .circuit Datei
 * 2. Speichere sie in eine neue Datei  
 * 3. Vergleiche die Original- und neue Datei
 */

int main() {
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "  C++ Digital Simulator - Labor 12 - Zusatzaufgabe 1" << std::endl;
    std::cout << "  saveToFile() Test" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════\n" << std::endl;

    // ===== Schritt 1: Lade die half_adder.circuit Datei =====
    std::cout << "[SCHRITT 1] Lade half_adder.circuit...\n" << std::endl;
    
    LogicEngine engine;
    engine.setCircuitName("Halbaddierer Export Test");
    engine.loadFromFile("half_adder.circuit");
    
    // ===== Schritt 2: Speichere die Schaltung in neue Datei =====
    std::cout << "\n[SCHRITT 2] Speichere Schaltung in half_adder_exported.circuit...\n" << std::endl;
    
    engine.saveToFile("half_adder_exported.circuit");
    
    // ===== Schritt 3: Vergleiche beide Dateien =====
    std::cout << "\n[SCHRITT 3] Vergleiche Original und Export\n" << std::endl;
    
    std::cout << "\nOriginal-Datei (half_adder.circuit):" << std::endl;
    std::cout << "───────────────────────────────────" << std::endl;
    
    std::ifstream original("half_adder.circuit");
    if (original.is_open()) {
        std::string line;
        int lineCount = 0;
        while (std::getline(original, line)) {
            if (!line.empty() && line[0] != '#') {  // Nur nicht-Kommentar-Zeilen
                std::cout << "  " << line << std::endl;
                lineCount++;
            }
        }
        original.close();
        std::cout << "  (insgesamt " << lineCount << " Befehle)\n" << std::endl;
    }
    
    std::cout << "\nExportierte Datei (half_adder_exported.circuit):" << std::endl;
    std::cout << "──────────────────────────────────────────────" << std::endl;
    
    std::ifstream exported("half_adder_exported.circuit");
    if (exported.is_open()) {
        std::string line;
        int lineCount = 0;
        while (std::getline(exported, line)) {
            if (!line.empty() && line[0] != '#') {  // Nur nicht-Kommentar-Zeilen
                std::cout << "  " << line << std::endl;
                lineCount++;
            }
        }
        exported.close();
        std::cout << "  (insgesamt " << lineCount << " Befehle)\n" << std::endl;
    }
    
    // ===== Schritt 4: Lade die exportierte Datei und teste sie =====
    std::cout << "\n[SCHRITT 4] Lade exportierte Datei und teste sie\n" << std::endl;
    
    LogicEngine engine2;
    engine2.setCircuitName("Halbaddierer aus Export");
    engine2.loadFromFile("half_adder_exported.circuit");
    
    Gate* switchA = engine2.getGateByName("A");
    Gate* switchB = engine2.getGateByName("B");
    Gate* sum = engine2.getGateByName("sum");
    Gate* carry = engine2.getGateByName("carry");
    
    if (switchA && switchB && sum && carry) {
        std::cout << "[SUCCESS] Exportierte Datei lädt korrekt!\n" << std::endl;
        
        // Quick Test: 1 AND 1 = 1, 1 XOR 1 = 0
        Switch* a = dynamic_cast<Switch*>(switchA);
        Switch* b = dynamic_cast<Switch*>(switchB);
        
        a->setState(true);
        b->setState(true);
        engine2.doTick();
        
        int sumResult = sum->getOutput() ? 1 : 0;
        int carryResult = carry->getOutput() ? 1 : 0;
        
        std::cout << "Quick Test: A=1, B=1" << std::endl;
        std::cout << "  XOR (sum): " << sumResult << " (expected 0) " 
                  << (sumResult == 0 ? "✓" : "✗") << std::endl;
        std::cout << "  AND (carry): " << carryResult << " (expected 1) " 
                  << (carryResult == 1 ? "✓" : "✗") << std::endl;
        
        if (sumResult == 0 && carryResult == 1) {
            std::cout << "\n✓ Exportierte Schaltung funktioniert korrekt!" << std::endl;
        } else {
            std::cout << "\n✗ Fehler in exportierter Schaltung!" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "[ERROR] Exportierte Datei lädt nicht richtig!" << std::endl;
        return 1;
    }
    
    std::cout << "\n═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "[SUCCESS] saveToFile() funktioniert perfekt!" << std::endl;
    std::cout << "Die exportierte Datei kann neu geladen und ausgeführt werden!" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════\n" << std::endl;
    
    return 0;
}

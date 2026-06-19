#include "GateFactory.h"
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"
#include "XorGate.h"
#include "NandGate.h"
#include "Switch.h"
#include "DFlipFlop.h"
#include "DFlipFlopEnable.h"
#include <iostream>

/**
 * GateFactory::createGate() - Die zentrale Fabrik-Methode
 * 
 * Dies ist das Herz des Factory Patterns. Wir übersetzen String-Namen
 * zu echten C++ Objekten (Klassenvirtualität zur Laufzeit)!
 * 
 * Architektur:
 * - Input: String wie "AND", "OR", "SWITCH"
 * - Output: std::unique_ptr<Gate> (konkrete Instanz)
 * - Error-Handling: nullptr + Fehlermeldung auf stderr
 */
std::unique_ptr<Gate> GateFactory::createGate(const std::string& type, 
                                             const std::string& name) {
    // ===== Kombinatorische Gatter =====
    if (type == "AND") {
        std::cout << "[GateFactory] Erstelle AND-Gatter: " << name << std::endl;
        return std::make_unique<AndGate>(name);
    }
    
    else if (type == "OR") {
        std::cout << "[GateFactory] Erstelle OR-Gatter: " << name << std::endl;
        return std::make_unique<OrGate>(name);
    }
    
    else if (type == "XOR") {
        std::cout << "[GateFactory] Erstelle XOR-Gatter: " << name << std::endl;
        return std::make_unique<XorGate>(name);
    }
    
    else if (type == "NOT") {
        std::cout << "[GateFactory] Erstelle NOT-Gatter: " << name << std::endl;
        return std::make_unique<NotGate>(name);
    }
    
    else if (type == "NAND") {
        std::cout << "[GateFactory] Erstelle NAND-Gatter: " << name << std::endl;
        return std::make_unique<NandGate>(name);
    }
    
    // ===== Datenquellen & Speicher =====
    else if (type == "SWITCH") {
        std::cout << "[GateFactory] Erstelle Switch: " << name << std::endl;
        return std::make_unique<Switch>(name);
    }
    
    else if (type == "DFF" || type == "DFLIPFLOP") {
        std::cout << "[GateFactory] Erstelle D-Flip-Flop: " << name << std::endl;
        return std::make_unique<DFlipFlop>(name);
    }
    
    else if (type == "DFFE" || type == "DFLIPFLOPENABLE") {
        std::cout << "[GateFactory] Erstelle D-Flip-Flop mit Enable: " << name << std::endl;
        return std::make_unique<DFlipFlopEnable>(name);
    }
    
    // ===== Fehlerbehandlung: Unbekannter Typ =====
    else {
        std::cerr << "[GateFactory ERROR] Unbekannter Gatter-Typ: '" << type << "'" << std::endl;
        std::cerr << "  Bekannte Typen: AND, OR, XOR, NOT, NAND, SWITCH, DFF, DFFE" << std::endl;
        return nullptr;
    }
}

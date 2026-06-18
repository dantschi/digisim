#pragma once

#include <string>
#include <memory>
#include "Component.h"

/**
 * =====================================================================
 * GateFactory - Die Bauteil-Fabrik
 * =====================================================================
 * 
 * Problem: C++ hat zur Laufzeit kein Reflection-System!
 * - Wenn wir eine Textdatei mit "AND" lesen, kennt das Programm
 *   zur Laufzeit den Typ "AndGate" nicht mehr!
 * - Wir können nicht einfach std::string zu Klassenname konvertieren
 * 
 * Lösung: Factory Pattern
 * - Eine statische Fabrik-Methode mappt Strings zu Klassen
 * - Aus Text "AND" wird dann: new AndGate(name)
 * - Dies ist das **Registry Pattern** der C++ Welt
 * 
 * Verwendung:
 *   auto gate = GateFactory::createGate("AND", "myAnd1");
 *   if (gate) { engine.addComponent(std::move(gate)); }
 */
class GateFactory {
public:
    /**
     * Erzeugt ein Gatter-Objekt basierend auf dem Typenamen
     * 
     * @param type Der Gatter-Typ als String (z.B. "AND", "OR", "NOT", "XOR", "SWITCH", "DFF")
     * @param name Der Name des zu erstellenden Gatters
     * @return Ein std::unique_ptr auf das neue Gatter, oder nullptr bei Fehler
     * 
     * Beispiele:
     *   GateFactory::createGate("AND", "myAnd") → AndGate-Objekt
     *   GateFactory::createGate("SWITCH", "inputA") → Switch-Objekt
     *   GateFactory::createGate("UNKNOWN", "fail") → nullptr + Fehlermeldung
     */
    static std::unique_ptr<Gate> createGate(const std::string& type, 
                                           const std::string& name);
};

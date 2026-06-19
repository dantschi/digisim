#include <iostream>
#include <cassert>
#include "AndGate.h"
#include "Switch.h"

/**
 * =====================================================================
 * Labor 12: Zusatzaufgabe 2 - Unit Tests
 * =====================================================================
 * 
 * Aufgabe: Beweisen Sie, dass Ihr AndGate bei fehlenden Kabeln robust reagiert
 * 
 * Robustheit bedeutet:
 * 1. Kein Crash bei nullptr-Eingängen
 * 2. Korrekte Logik (fehlender Kabel = 0/false)
 * 3. Konsistente Behavior über mehrere Takte
 * 
 * AND-Gatter Logik:
 *  Beide Eingänge müssen 1 sein, um 1 zu produzieren.
 *  Wenn ein Eingang nullptr (nicht verbunden), behandeln wir ihn als 0.
 *
 * Truth-Tabelle mit Floating Pins:
 *  Pin0 | Pin1 | Expected
 *  -----+------+----------
 *   1   |  1   |    1     (beide verbunden: 1 AND 1 = 1)
 *   1   |  0   |    0     (Pin0=1, Pin1 floating=0: 1 AND 0 = 0)
 *   0   |  1   |    0     (Pin0 floating=0, Pin1=1: 0 AND 1 = 0)
 *   0   |  0   |    0     (beide floating: 0 AND 0 = 0)
 *  null |  1   |    0     (Pin0 nicht verbunden: 0 AND 1 = 0)
 */

// Test 1: Beide Pins offen (nicht verbunden)
void testAndGate_BothPinsOpen() {
    std::cout << "\n[TEST 1] AndGate mit beiden Pins offen...\n" << std::endl;
    
    AndGate gate("AND_test1");
    
    // Beide Pins sind nullptr (nicht verbunden)
    // Das Gatter sollte:
    // - Nicht abstürzen
    // - evaluate() should treat nullptr as false (0)
    // - Output sollte 0 sein (0 AND 0 = 0)
    
    gate.evaluate();  // Sollte nicht abstürzen!
    bool result = gate.getOutput();
    
    std::cout << "  Result: " << (result ? "1" : "0") << std::endl;
    std::cout << "  Expected: 0 (because 0 AND 0 = 0 when pins are floating)" << std::endl;
    
    assert(result == false && "[TEST 1 FAILED] AndGate mit beiden Pins offen sollte 0 sein!");
    std::cout << "  ✓ PASS\n" << std::endl;
}

// Test 2: Ein Pin verbunden (1), anderer Pin offen
void testAndGate_OnePinConnected() {
    std::cout << "[TEST 2] AndGate mit einem Pin verbunden (1) und einem offen...\n" << std::endl;
    
    AndGate andGate("AND_test2");
    Switch input1("Input1");
    
    // Verbinde Input1 mit Pin 0
    andGate.connectInput(0, &input1);
    // Pin 1 bleibt offen (nullptr)
    
    // Setze Input1 auf 1
    input1.setState(true);
    
    andGate.evaluate();  // Sollte nicht abstürzen!
    bool result = andGate.getOutput();
    
    std::cout << "  Input1 (Pin0): 1" << std::endl;
    std::cout << "  Pin1 (offen): 0 (floating)" << std::endl;
    std::cout << "  Result: " << (result ? "1" : "0") << std::endl;
    std::cout << "  Expected: 0 (because 1 AND 0 = 0)" << std::endl;
    
    assert(result == false && "[TEST 2 FAILED] 1 AND (floating=0) sollte 0 sein!");
    std::cout << "  ✓ PASS\n" << std::endl;
}

// Test 3: Beide Pins verbunden mit echten Inputs
void testAndGate_BothPinsConnected() {
    std::cout << "[TEST 3] AndGate mit beiden Pins verbunden...\n" << std::endl;
    
    AndGate andGate("AND_test3");
    Switch input1("Input1");
    Switch input2("Input2");
    
    andGate.connectInput(0, &input1);
    andGate.connectInput(1, &input2);
    
    // Test: 1 AND 1 = 1
    input1.setState(true);
    input2.setState(true);
    andGate.reset();  // Leere den Cache!
    input1.reset();
    input2.reset();
    andGate.evaluate();
    bool result = andGate.getOutput();
    
    std::cout << "  Test 1: Input1=1, Input2=1" << std::endl;
    std::cout << "  Result: " << (result ? "1" : "0") << std::endl;
    std::cout << "  Expected: 1" << std::endl;
    
    assert(result == true && "[TEST 3 Sub1 FAILED] 1 AND 1 sollte 1 sein!");
    std::cout << "  ✓ PASS\n" << std::endl;
    
    // Test: 1 AND 0 = 0
    input1.setState(true);
    input2.setState(false);
    andGate.reset();  // Leere den Cache!
    input1.reset();
    input2.reset();
    andGate.evaluate();
    result = andGate.getOutput();
    
    std::cout << "  Test 2: Input1=1, Input2=0" << std::endl;
    std::cout << "  Result: " << (result ? "1" : "0") << std::endl;
    std::cout << "  Expected: 0" << std::endl;
    
    assert(result == false && "[TEST 3 Sub2 FAILED] 1 AND 0 sollte 0 sein!");
    std::cout << "  ✓ PASS\n" << std::endl;
    
    // Test: 0 AND 1 = 0
    input1.setState(false);
    input2.setState(true);
    andGate.reset();  // Leere den Cache!
    input1.reset();
    input2.reset();
    andGate.evaluate();
    result = andGate.getOutput();
    
    std::cout << "  Test 3: Input1=0, Input2=1" << std::endl;
    std::cout << "  Result: " << (result ? "1" : "0") << std::endl;
    std::cout << "  Expected: 0" << std::endl;
    
    assert(result == false && "[TEST 3 Sub3 FAILED] 0 AND 1 sollte 0 sein!");
    std::cout << "  ✓ PASS\n" << std::endl;
}

// Test 4: Ein Pin verbunden mit 0, anderer offen
void testAndGate_OnePinZeroOneOpen() {
    std::cout << "[TEST 4] AndGate mit Pin0=0 und Pin1 offen...\n" << std::endl;
    
    AndGate andGate("AND_test4");
    Switch input1("Input1");
    
    andGate.connectInput(0, &input1);
    // Pin 1 bleibt offen
    
    input1.setState(false);  // 0
    
    andGate.evaluate();  // Sollte nicht abstürzen!
    bool result = andGate.getOutput();
    
    std::cout << "  Pin0: 0" << std::endl;
    std::cout << "  Pin1 (offen): 0 (floating)" << std::endl;
    std::cout << "  Result: " << (result ? "1" : "0") << std::endl;
    std::cout << "  Expected: 0 (because 0 AND 0 = 0)" << std::endl;
    
    assert(result == false && "[TEST 4 FAILED] 0 AND (floating=0) sollte 0 sein!");
    std::cout << "  ✓ PASS\n" << std::endl;
}

// Test 5: Robustheit - mehrfaches evaluate() mit fehlenden Kabeln
void testAndGate_MultipleEvaluations() {
    std::cout << "[TEST 5] Robustheit - mehrfaches evaluate() mit fehlenden Kabeln...\n" << std::endl;
    
    AndGate andGate("AND_test5");
    Switch input1("Input1");
    
    andGate.connectInput(0, &input1);
    // Pin 1 bleibt offen
    
    // Führe mehrfache evaluate() Aufrufe durch
    std::cout << "  Führe 100 evaluate() Aufrufe durch..." << std::endl;
    
    for (int i = 0; i < 100; i++) {
        input1.setState((i % 2) == 0);  // Abwechselnd 0 und 1
        andGate.evaluate();
        
        bool result = andGate.getOutput();
        bool expected = false;  // Mit Pin1 offen (0) ist result immer 0
        
        if (result != expected) {
            std::cerr << "[TEST 5 FAILED] Iteration " << i << ": Ergebnis=" << result 
                      << " aber expected=" << expected << std::endl;
            assert(false);
        }
    }
    
    std::cout << "  ✓ 100 Aufrufe erfolgreich! Kein Crash!" << std::endl;
    std::cout << "  ✓ PASS\n" << std::endl;
}

int main() {
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    std::cout << "  C++ Digital Simulator - Labor 12 - Zusatzaufgabe 2" << std::endl;
    std::cout << "  Unit Tests: AndGate Robustheit bei fehlenden Kabeln" << std::endl;
    std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
    
    try {
        testAndGate_BothPinsOpen();
        testAndGate_OnePinConnected();
        testAndGate_BothPinsConnected();
        testAndGate_OnePinZeroOneOpen();
        testAndGate_MultipleEvaluations();
        
        std::cout << "\n═══════════════════════════════════════════════════════════════" << std::endl;
        std::cout << "[SUCCESS] ✓ Alle 5 Tests bestanden!" << std::endl;
        std::cout << "Der AndGate ist robust gegen fehlende Kabel!" << std::endl;
        std::cout << "═══════════════════════════════════════════════════════════════" << std::endl;
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[EXCEPTION] " << e.what() << std::endl;
        return 1;
    }
}

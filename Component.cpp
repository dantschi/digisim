#include "Component.h"

/**
 * Konstruktor der Gate-Klasse
 * Initialisiert alle Attribute sicher
 */
Gate::Gate(std::string n) 
    : m_name(n), m_output(false) {
    std::cout << "[" << m_name << "] Gate erstellt" << std::endl;
}

/**
 * Verbindet einen Eingang mit einem anderen Gatter (Kabel-Plugin)
 * Hardware-Schutzschaltung (Out-of-Bounds Check)
 */
void Gate::connectInput(int index, std::shared_ptr<Gate> source) {
    // Prüfen, ob der Pin physisch am Gatter existiert
    if (index >= 0 && index < static_cast<int>(m_inputs.size())) {
        m_inputs[index] = source;
        std::cout << "[VERKABELUNG] " << m_name << " Pin " << index 
                  << " verbunden mit " << source->m_name << std::endl;
    } else {
        std::cerr << "[FEHLER] " << m_name << ": Pin " << index << " existiert nicht! "
                  << "(Verfügbar: 0-" << (m_inputs.size() - 1) << ")" << std::endl;
    }
}

/**
 * Getter für den Ausgangswert
 */
bool Gate::getOutput() const {
    return m_output;
}

/**
 * Getter für den Namen des Gatters
 */
std::string Gate::getName() const {
    return m_name;
}

/**
 * Virtueller Destruktor: Wird aufgerufen wenn Objekt zerstört wird
 */
Gate::~Gate() {
    std::cout << "[DESTRUKTOR] Zerstöre Gate: " << m_name << std::endl;
}

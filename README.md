# C++ Digital Simulator

[![C++ Automated Tests](https://github.com/dantschi/digisim/actions/workflows/ci.yml/badge.svg)](https://github.com/dantschi/digisim/actions/workflows/ci.yml)

Ein **C++-basierter Simulator für digitale Logikgatter** – Ausgangspunkt aus **Labor 12** (GateFactory & `.circuit`-Parser).

> **Hinweis:** Dieses Repository richten Sie **eine Woche vor der Veranstaltung** ein. Die Aufgabenstellung erhalten Sie vor Ort bzw. zur Veranstaltung.

---

## Repository-Setup

Bitte führen Sie diese Schritte **jetzt** aus, damit Sie am Veranstaltungstag direkt mit der Entwicklung beginnen können:

1. **Privates Repository** aus dem Template erstellen: [github.com/dantschi/digisim](https://github.com/dantschi/digisim) → „Use this template“ → **Private**
2. **Dozent einladen:** Settings → Collaborators → `dantschi` hinzufügen
3. **Klonen und öffnen:**
   ```bash
   git clone https://github.com/IHR-USERNAME/IHR-REPO-NAME.git
   cd IHR-REPO-NAME
   code .
   ```
4. **Kompilieren und testen** (siehe unten) – stellen Sie sicher, dass alles auf Ihrem Rechner läuft

---

## Ausgangszustand

Das Projekt ist sofort lauffähig und demonstriert den Halbaddierer aus `half_adder.circuit`:

- `main.cpp` – lädt die Schaltung und gibt die Wahrheitstabelle aus
- `GateFactory` – erzeugt Gatter aus Textdateien
- `LogicEngine` – lädt `.circuit`-Dateien und simuliert Takte

```bash
g++ -std=c++17 *.cpp -o simulator
./simulator        # Linux/macOS
.\simulator.exe    # Windows
```

Erwartete Ausgabe: Wahrheitstabelle des Halbaddierers (Sum & Carry für alle Eingabekombinationen).

---

## Projektstruktur

```
├── main.cpp                 # Einstiegspunkt (Halbaddierer-Demo)
├── LogicEngine.h/cpp        # Simulations-Engine & .circuit-Parser
├── GateFactory.h/cpp        # Factory Pattern
├── Component.h/cpp          # Basisklasse Gate
├── half_adder.circuit       # Beispiel-Schaltung
├── data/                    # Ordner für Dateien
└── .github/workflows/ci.yml # CI-Pipeline
```

---

## .circuit-Format (Referenz aus Labor 12)

```
# Kommentare mit # oder //
GATE SWITCH A
GATE XOR sum
WIRE sum 0 A
WIRE sum 1 B
```

---

## Kompilierung

```bash
g++ -std=c++17 *.cpp -o simulator
```

---

## Setup-Checkliste

- [ ] Privates GitHub-Repository aus Template erstellt
- [ ] Dozent (`dantschi`) als Collaborator eingeladen
- [ ] Repository lokal geklont
- [ ] Projekt kompiliert ohne Fehler
- [ ] `simulator` startet und zeigt Halbaddierer-Wahrheitstabelle

---

**Bis zur Veranstaltung!**

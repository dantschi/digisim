# C++ Digital Simulator – Abschluss-Testat

[![C++ Automated Tests](https://github.com/dantschi/digisim/actions/workflows/ci.yml/badge.svg)](https://github.com/dantschi/digisim/actions/workflows/ci.yml)

Ein **C++-basierter Simulator für digitale Logikgatter** – Ausgangspunkt für das Abschluss-Testat *ROM-Speicher & Automatisierte Testbench*.

Die vollständige Aufgabenstellung finden Sie in **`LaboranleitungTestat.pdf`**.

---

## Angaben zur Abgabe

**Name:** _[Ihr Name]_  
**Matrikelnummer:** _[Ihre Matrikelnummer]_  
**GitHub-Repository:** _[URL zu Ihrem privaten Repo]_

---

## Repository-Setup (zu Beginn des Testats)

1. **Privates Repository** aus dem Template erstellen: [github.com/dantschi/digisim](https://github.com/dantschi/digisim) → „Use this template“ → **Private**
2. **Dozent einladen:** Settings → Collaborators → `dantschi` hinzufügen
3. **Klonen und öffnen:**
   ```bash
   git clone https://github.com/IHR-USERNAME/IHR-REPO-NAME.git
   cd IHR-REPO-NAME
   code .
   ```
4. **Abgabe:** Code pushen, **diese README.md** ausfüllen, Repository-URL in Moodle einreichen

---

## Ausgangszustand

Das Projekt basiert auf **Labor 12** (GateFactory & `.circuit`-Parser) und ist sofort lauffähig:

- `main.cpp` – demonstriert den Halbaddierer aus `half_adder.circuit`
- `GateFactory` – erzeugt Gatter aus Textdateien
- `LogicEngine` – lädt `.circuit`-Dateien und simuliert Takte

```bash
g++ -std=c++17 *.cpp -o simulator
./simulator        # Linux/macOS
.\simulator.exe    # Windows
```

Erwartete Ausgabe: Wahrheitstabelle des Halbaddierers (Sum & Carry für alle Eingabekombinationen).

---

## Ihre Aufgaben

### Teil 1: RomGate (Pflicht – zum Bestehen)

| Schritt | Was zu tun ist |
|--------|----------------|
| 1 | Klasse `RomGate` neu anlegen (`RomGate.h` / `RomGate.cpp`) |
| 2 | `.rom`-Datei **im Konstruktor** einlesen → `std::vector<bool> m_truthTable` |
| 3 | `evaluate()`: Pull-Prinzip, Eingänge als Binär-Index, Ausgabe aus Tabelle |
| 4 | `GateFactory` und `LogicEngine::loadFromFile()` für optionalen Dateipfad erweitern |
| 5 | Parser-Zeile: `GATE ROM meinDecoder data/decoder.rom` |
| 6 | Eigene `.rom`- und `.circuit`-Datei anlegen und Funktion nachweisen |

**Wichtig:** Dateizugriff nur im Konstruktor, niemals in `evaluate()`!

### Teil 2: AssertGate (Zusatzaufgabe)

| Schritt | Was zu tun ist |
|--------|----------------|
| 1 | Klasse `AssertGate` eigenständig entwerfen (`AssertGate.h` / `AssertGate.cpp`) |
| 2 | 2 Eingänge: Ist-Wert und Soll-Wert |
| 3 | Bei Abweichung: Simulation per Exception abbrechen |
| 4 | `.circuit`-Datei mit absichtlichem Fehlerfall erstellen |

### Teil 3: Abgabe-Dokumentation (in dieser README.md)

Tragen Sie Ihre Antworten **direkt in die Abschnitte unten** ein (Block A–C). Geben Sie ausführliche und spezifische Antworten zu **Ihrem** geschriebenen Code.

---

## Projektstruktur

```
├── main.cpp                 # Einstiegspunkt (Halbaddierer-Demo)
├── LogicEngine.h/cpp        # Simulations-Engine & .circuit-Parser
├── GateFactory.h/cpp        # Factory Pattern – hier ROM/ASSERT einbinden
├── Component.h/cpp          # Basisklasse Gate
├── half_adder.circuit       # Beispiel-Schaltung (Referenz)
├── data/                    # Hier .rom-Dateien ablegen
├── README.md                # Aufgaben, Abgabe & Antworten (diese Datei)
├── LaboranleitungTestat.pdf # Aufgabenstellung
├── archive/                 # Alte Labor-Dateien (nicht kompilieren)
└── .github/workflows/ci.yml # CI-Pipeline
```

---

## .circuit-Format (Referenz)

```
# Kommentare mit # oder //
GATE SWITCH A
GATE XOR sum
WIRE sum 0 A
WIRE sum 1 B
```

Nach Ihrer Erweiterung (Teil 1):

```
GATE ROM meinDecoder data/decoder.rom
```

---

## .rom-Format

Pro Zeile genau ein Zeichen – `0` oder `1`:

```
0
1
1
0
```

Die Zeilennummer entspricht dem Binär-Index der Eingänge (Input 0 = Bit 0 = 2⁰, Input 1 = Bit 1 = 2¹, …).

---

## Kompilierung

```bash
# Standard (alle .cpp im Hauptverzeichnis)
g++ -std=c++17 *.cpp -o simulator
```

> **Hinweis:** Dateien in `archive/` werden nicht mitkompiliert (`g++ *.cpp` nur im Root). Nach dem Anlegen von `RomGate.cpp` (und ggf. `AssertGate.cpp`) werden diese automatisch mitkompiliert.

---

## Abgabe-Checkliste

- [ ] Privates GitHub-Repository erstellt, Dozent eingeladen
- [ ] `RomGate` implementiert und in Factory/Parser integriert
- [ ] `.rom`- und `.circuit`-Demo-Dateien erstellt
- [ ] (Optional) `AssertGate` mit Fehlerfall-Demo
- [ ] README.md vollständig ausgefüllt (Angaben + Block A–C)
- [ ] `git push` – finale Abgabe
- [ ] Repository-URL in Moodle eingereicht

---

## Block A: KI-Protokoll (AI Transparency Log)

Der Einsatz von KI-Tools (GitHub Copilot, ChatGPT, Cursor, etc.) wird begrüßt, soll aber nicht unreflektiert geschehen.

### 1. Welche Werkzeuge haben Sie für diese Aufgabe genutzt?

_[Antwort hier]_

### 2. Fassen Sie Ihren KI-Arbeitsprozess zusammen

**Wie haben Sie Ihre Prompts formuliert?**

_[Antwort hier]_

**Kurze Beschreibung der Anpassungen:** Was mussten Sie am KI-Code oder am Prompt ändern, damit er funktioniert?

_[Antwort hier – z. B. „KI hat Header vergessen“, „Variable umbenannt“, „Modulo-Logik korrigiert“]_

---

## Block B: Architektur-Verständnis

### 1. Warum ist es ein schwerwiegender Fehler, die `std::ifstream`-Logik in `evaluate()` statt im Konstruktor zu platzieren?

_[Antwort hier]_

### 2. Sie haben das RomGate zur LogicEngine hinzugefügt, ohne `LogicEngine::doTick()` umschreiben zu müssen. Welches OOP-Prinzip macht das möglich und wie funktioniert der Mechanismus intern?

_[Antwort hier]_

### 3. Erklären Sie das Ownership-Konzept: `std::unique_ptr` in der Engine vs. `Gate*`-Raw-Pointer für Kabel. Wer löscht den Speicher und warum verhindert das Memory Leaks?

_[Antwort hier]_

---

## Block C: Edge-Cases (Fehlerbehandlung)

### 1. Wie reagiert Ihr Code, wenn in der `.circuit`-Datei ein RomGate angelegt wird, aber der Pfad zur `.rom`-Datei falsch ist (Datei existiert nicht)? Auf welche Code-Zeile verlassen Sie sich in diesem Moment?

_[Antwort hier – mit Dateiname und Zeilennummer]_

### 2. Was passiert in Ihrem `evaluate()`, wenn 3 Kabel am RomGate hängen (max. Index = 7), die Wahrheitstabelle aber nur 4 Zeilen hat? Wie schützt Ihr Code vor einem Segmentation Fault?

_[Antwort hier]_

---

**Viel Erfolg beim Testat!**

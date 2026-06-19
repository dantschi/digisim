# Archiv – frühere Labor-Dateien

Diese Dateien stammen aus früheren Laborterminen und enthalten eigene `main()`-Funktionen.
Sie werden **nicht** mit `g++ *.cpp` kompiliert (liegen außerhalb des Root-Verzeichnisses).

| Datei | Herkunft |
|-------|----------|
| `main_labor12.cpp` | Labor 12 – Inhalt jetzt in `main.cpp` |
| `main_zusatz.cpp` | Labor 10/11 – 2-Bit-Zähler Demo |
| `test_andgate.cpp` | Labor 12 – Unit Tests für AndGate |
| `test_savetofile.cpp` | Labor 12 – saveToFile() Test |

Zum Kompilieren einzelner Demos manuell ausführen, z. B.:

```bash
g++ -std=c++17 -o test_andgate archive/test_andgate.cpp Component.cpp AndGate.cpp Switch.cpp
```

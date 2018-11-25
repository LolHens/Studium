// =============================================================================
//
//       Filename:  aufgabe3.cpp
//
//    Description:  Zufallszahlen
//
//        Version:  1.0
//        Created:  13.10.2018
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Pierre Kisters
//
// =============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cfloat>
#include <Windows.h>

using namespace std;

/**
 * Aufgabe 3.1
 * Feld mit Zufallszahlen belegen
 */
void aufgabe_3_1() {
    double zufallswerte[100];

    // Seed für Zufallsgeneator aus aktueller Zeit festlegen
    srand(time(NULL));

    for (int i = 0; i < sizeof(zufallswerte) / sizeof(zufallswerte[0]); i++) {
        zufallswerte[i] = rand() % 51;
    }

    double min = DBL_MAX;
    double max = 0;
    double sum = 0;

    for (int i = 0; i < sizeof(zufallswerte) / sizeof(zufallswerte[0]); i++) {
        cout << setw(6) << fixed << setprecision(2) << zufallswerte[i];

        if (i % 10 == 9) {
            cout << endl;
        } else {
            cout << " ";
        }

        if (zufallswerte[i] < min) {
            min = zufallswerte[i];
        }

        if (zufallswerte[i] > max) {
            max = zufallswerte[i];
        }

        sum += zufallswerte[i];
    }

    double mittel = sum / (double) (sizeof(zufallswerte) / sizeof(zufallswerte[0])); // Arithmetisches Mittel berechnen

    // Ausgaben
    cout << "Das arithmetische Mittel ist " << fixed << setprecision(2) << mittel << endl;
    cout << "Der kleinste Wert ist " << fixed << setprecision(2) << min << " und der größte " << max << endl;
}

/**
 * Aufgabe 3.2
 * Datei einlesen
 */
void aufgabe_3_2() {
    string dateiname = "../daten-3-2.txt"; // Dateiname
    ifstream ifs; // Dateistream initialisieren
    ifs.open(dateiname); // Datei öffnen
    if (!ifs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(1);
    }

    double wert;
    int anzahl = 0;
    double min = DBL_MAX;
    double max = 0;
    double sum = 0;

    // Solange ein nächster Wert vorhanden ist werden Berechnungen ausgeführt
    while (ifs >> wert) {
        //cout << wert << endl;

        anzahl++;

        if (wert < min) {
            min = wert;
        }

        if (wert > max) {
            max = wert;
        }

        sum += wert;
    }

    ifs.close();

    double mittel = sum / anzahl; // Arithmetisches Mittel berechnen

    // Ausgaben
    cout << "Die Datei enthält " << anzahl << " Elemente" << endl;
    cout << "Das arithmetische Mittel ist " << fixed << setprecision(2) << mittel << endl;
    cout << "Der kleinste Wert ist " << fixed << setprecision(2) << min << " und der größte " << max << endl;
}

/**
 * Aufgabe 3.3
 * Zufallsgenerator
 */
void aufgabe_3_3() {
    // Konstanten initialisieren
    const int A = 16333;
    const int B = 25887;
    const int M = 1 << 15;

    const int X0 = 0;
    int x = X0;

    cout << "10 Zufallszahlen:" << endl;
    for (int i = 0; i < 10; i++) {
        // Neue Zufallszahl aus vorheriger berechnen
        x = (A * x + B) % M;

        // Zufallszahl ausgeben
        cout << setw(6) << x << endl;
    }
}

/**
 * Aufgabe 3.4
 * Zufallsgenerator Periodenlänge
 */
void aufgabe_3_4() {
    // Konstanten initialisieren
    const int A = 16333;
    const int B = 25887;
    const int M = 1 << 15;
    const int X0 = 0;

    int x = X0;
    int periodenlaenge = 0;

    cout << "10 Zufallszahlen:" << endl;
    do {
        // Neue Zufallszahl aus vorheriger berechnen
        x = (A * x + B) % M;

        periodenlaenge++;
    } while (x != X0); // Bis x wieder X0 ist

    cout << "Die Periodenlänge beträgt " << periodenlaenge << endl;
}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    std::cout << "Hello, World!" << std::endl;

    aufgabe_3_1();
    std::cout << std::endl;
    aufgabe_3_2();
    std::cout << std::endl;
    aufgabe_3_3();
    std::cout << std::endl;
    aufgabe_3_4();
    std::cout << std::endl;

    return 0;
}

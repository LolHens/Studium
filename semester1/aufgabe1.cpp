// =============================================================================
//
//       Filename:  aufgabe1.cpp
//
//    Description:  Berechnung der harmonischen, alternierend harmonischen,
//                  Leibnizschen und geometrischen Reihe
//
//        Version:  1.0
//        Created:  28.09.2018
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Pierre Kisters
//
// =============================================================================

#include <iostream>
#include <iomanip>
#include <windows.h>

/**
 * harmonische Reihe
 */
void aufgabe_1_1_reihe_1_1() {
    // Summe aller Summanden
    double summe = 0;
    // berechneter Summand
    double summand;

    // Zähle von 1 bis inklusive 1000
    for (int i = 1; i <= 1000; i++) {
        // Summanden errechnen
        summand = 1.0 / (double) i;
        // Summand zu Summe addieren
        summe += summand;
    }

    // Ausgabe
    std::cout << "Die Summe der ersten 1000 Elemente aus Reihe 1.1 beträgt "
              << std::fixed << std::setprecision(5) << summe
              << std::endl;
}

/**
 * alternierende harmonische Reihe
 */
void aufgabe_1_1_reihe_1_2() {
    // Summe aller Summanden
    double summe = 0;
    // Vorzeichen, welches jede Iteration wechselt
    int v = 1;
    // berechneter Summand
    double summand;

    // Zähle von 1 bis inklusive 1000
    for (int i = 1; i <= 1000; i++) {
        // Summanden errechnen
        summand = (double) v / (double) i;
        // Vorzeichen wechseln
        v = -v;
        // Summand zu Summe addieren
        summe += summand;
    }

    std::cout << "Die Summe der ersten 1000 Elemente aus Reihe 1.2 beträgt "
              << std::fixed << std::setprecision(5) << summe
              << std::endl;
}

/**
 * Leibnizsche Reihe
 */
void aufgabe_1_1_reihe_1_3() {
    // Summe aller Summanden
    double summe = 0;
    // Vorzeichen, welches jede Iteration wechselt
    int v = 1;
    // berechneter Summand
    double summand;

    // Zähle von 1 bis inklusive 1000
    for (int i = 1; i <= 1000; i++) {
        // Summanden errechnen
        summand = (double) v / (2.0 * (double) i - 1.0);
        // Vorzeichen wechseln
        v = -v;
        // Summand zu Summe addieren
        summe += summand;
    }

    std::cout << "Die Summe der ersten 1000 Elemente aus Reihe 1.3 beträgt "
              << std::fixed << std::setprecision(5) << summe
              << std::endl;
}

/**
 * geometrische Reihe
 */
void aufgabe_1_1_reihe_1_4() {
    // Summe aller Summanden
    double summe = 0;
    // berechneter Summand
    double summand = 1;

    // Zähle von 0 bis exklusive 1000
    for (int i = 0; i < 1000; i++) {
        // Summand zu Summe addieren
        summe += summand;
        // Summand für nächste Iteration berechnen
        summand *= 0.5;
    }

    //Ausgabe
    std::cout << "Die Summe der ersten 1000 Elemente aus Reihe 1.4 beträgt "
              << std::fixed << std::setprecision(5) << summe
              << std::endl;
}

/**
 * geometrische Reihe
 */
void aufgabe_1_2_reihe_1_4() {
    // Summe aller Summanden
    double summe = 0;
    // berechneter Summand
    double summand = 1;
    // vorheriger berechneter Summand
    // mit 0 initialisiert, damit dieser bei 1. Iteration einen anderen Wert hat als Summand
    double letzterSummand = 0;

    // Zählervariable
    int i = 0;
    // Wiederholen, solange summand sich verändert
    while (summand != letzterSummand) {
        // Zähler inkrementieren
        i++;
        // Summand zu Summe addieren
        summe += summand;
        // letzten Summanden speichern
        letzterSummand = summand;
        // Summand für nächste Iteration berechnen
        summand *= 0.5;
    }

    // Ausgabe
    std::cout << "Die Summe der Reihe 1.4, welche sich nach " << i << " Iterationen nicht mehr ändert beträgt "
              << std::fixed << std::setprecision(16) << summe
              << std::endl;
}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    std::cout << "Hello, World!" << std::endl;

    // alle Aufgaben ausführen

    aufgabe_1_1_reihe_1_1();
    aufgabe_1_1_reihe_1_2();
    aufgabe_1_1_reihe_1_3();
    aufgabe_1_1_reihe_1_4();

    aufgabe_1_2_reihe_1_4();

    return 0;
}

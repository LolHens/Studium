// =============================================================================
//
//       Filename:  aufgabe2.cpp
//
//    Description:  Berechnung der harmonischen, alternierend harmonischen,
//                  Leibnizschen und geometrischen Reihe
//
//        Version:  1.0
//        Created:  01.10.2018
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Pierre Kisters
//
// =============================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <Windows.h>

/**
 * Aufgabe 2.1
 * Darstellung einer ASCII-Tabelle (Grundaufgabe)
 */
void aufgabe_2_1_grundaufgabe() {
    // Tabelle ausgeben
    for (int zeile = 0; zeile < 32; zeile++) {
        for (int spalte = 0; spalte < 4; spalte++) {
            // Dezimalzahl aus Zeile und Spalte berechnen
            int dez = zeile + spalte * 32;

            // Platzhalter zwischen den Werten
            if (spalte > 0) std::cout << " ";

            // Wert ausgeben
            std::cout << std::setfill('0') << std::setw(3) << dez;
        }

        std::cout << std::endl;
    }
}

/**
 * Aufgabe 2.1
 * Darstellung einer ASCII-Tabelle
 */
void aufgabe_2_1() {
    // Überschrift ausgeben
    std::cout << "***  ASCII-Table  ***" << std::endl << std::endl;

    // Tabelle ausgeben (2 Zeilen für die Überschriften)
    for (int zeile = -2; zeile < 32; zeile++) {
        // Spalte ausgeben
        for (int spalte = 0; spalte < 4; spalte++) {
            if (zeile == -2) { // Überschriftenzeile

                // Platzhalter zwischen den Überschriften
                if (spalte > 0) std::cout << "    ";

                std::cout << "Okt Dez Hex Zch";

            } else if (zeile == -1) { // Trenner

                std::cout << "------------------";

            } else { // Tabelle

                // Dezimalzahl aus Zeile und Spalte berechnen
                int dez = zeile + spalte * 32;

                // Platzhalter zwischen den Werten
                if (spalte > 0) std::cout << "    ";

                // Wert in verschiedenen Formaten ausgeben
                std::cout << std::setfill('0')
                          << std::setw(3) << std::oct << dez << " "
                          << std::setw(3) << std::dec << dez << " "
                          << std::setw(3) << std::hex << dez << " ";

                // Zeichen ausgeben; Für Sonderzeichen ein "..."
                if (dez > 31 && dez != 127) {
                    char zch = (char) dez;
                    std::cout << " " << zch << " ";
                } else {
                    std::cout << "...";
                }

            }
        }

        std::cout << std::endl;
    }
}

/**
 * Aufgabe 2.2
 * Visualisierung von Rundungsfehlern
 */
void aufgabe_2_2() {
    // Ausgangswert
    float ausgangswert = 1E6;
    // Multiplikator
    float k = 0.1693;

    float x = ausgangswert;

    // Multiplikation
    for (int i = 0; i < 10; i++) {
        x *= k;
    }

    // Division
    for (int i = 0; i < 10; i++) {
        x /= k;
    }

    std::cout << "Der Ausgangswert war " << std::fixed << std::setprecision(8) << ausgangswert << std::endl;
    std::cout << "Der Endwert beträgt  " << std::fixed << std::setprecision(8) << x << std::endl;

    if (x == ausgangswert) {
        std::cout << "Die Werte stimmen überein! (keine Rundungsfehler)" << std::endl;
    } else {
        std::cout << "Die Werte stimmen nicht überein! (Rundungsfehler)" << std::endl;
    }
}

/**
 * Aufgabe 2.3
 * Berechnung einer Dreiecksfläche mit 2 Formeln
 */
void aufgabe_2_3() {
    // Deklaration und Einlesen der 3 Seitenlängen.
    double a, b, c;
    std::cout << "Geben sie Länge a ein: ";
    std::cin >> a;
    std::cout << "Geben sie Länge b ein: ";
    std::cin >> b;
    std::cout << "Geben sie Länge c ein: ";
    std::cin >> c;

    // Berechnung der Radikanten der beiden Formeln
    double s = (a + b + c) / 2.0;
    double radikant1 = s * (s - a) * (s - b) * (s - c);
    double radikant2 = (a + b + c) * (a + b - c) * (b + c - a) * (c + a - b);

    // Prüfung und Fehlerbehandlung, wenn Radikant < 0
    if (radikant1 < 0) {
        std::cout << "Radikant der 1. Formel ist negativ! Es kann sich nicht um ein Dreieck handeln." << std::endl;
    } else {
        // Berechnung der Fläche der 1. Formel
        double flaeche1 = sqrt(radikant1);
        std::cout << "Dreiecksfläche nach 1. Formel: " << flaeche1 << std::endl;
    }

    // Prüfung und Fehlerbehandlung, wenn Radikant < 0
    if (radikant2 < 0) {
        std::cout << "Radikant der 2. Formel ist negativ! Es kann sich nicht um ein Dreieck handeln." << std::endl;
    } else {
        // Berechnung der Fläche der 2. Formel
        double flaeche2 = sqrt(radikant2) / 4;
        std::cout << "Dreiecksfläche nach 2. Formel: " << flaeche2 << std::endl;
    }
}

/*

Aufgabe 2.3
Berechnung einer Dreiecksfläche mit 2 Formeln von Hand

1)
  a = 1; b = 1; c = 1

  Formel 1:
  s = 1/2 * (1 + 1 + 1) = 1/2 * 3 = 1,5
  A = (1,5 * (1,5 - 1) * (1,5 - 1) * (1,5 - 1))^(1/2) = (1,5 * 0,5 * 0,5 * 0,5)^(1/2) = 0,1875^(1/2) ~= 0,433

  Formel 2:
  A = 1/4 * ((1 + 1 + 1) * (1 + 1 - 1) * (1 + 1 - 1) * (1 + 1 - 1))^(1/2) = 1/4 * 3^(1/2) ~= 0,433

2)
  a = 3; b = 4; c = 5

  Formel 1:
  1/2 * (3 + 4 + 5) = 1/2 * 12 = 6
  A = (6 * (6 - 3) * (6 - 4) * (6 - 5))^(1/2) = (6 * 3 * 2 * 1)^(1/2) = 36^(1/2) = 6

  A = 1/4 * ((3 + 4 + 5) * (3 + 4 - 5) * (4 + 5 - 3) * (5 + 3 - 4))^(1/2) = 1/4 * (12 * 2 * 6 * 4)^(1/2) = 1/4 * 576^(1/2) ~= 6

*/

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    std::cout << "Hello, World!" << std::endl;

    aufgabe_2_1();
    std::cout << std::endl;
    aufgabe_2_2();
    std::cout << std::endl;
    aufgabe_2_3();

    return 0;
}

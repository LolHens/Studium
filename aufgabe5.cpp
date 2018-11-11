// =============================================================================
//
//       Filename:  aufgabe4.cpp
//
//    Description:  Chiffres
//
//        Version:  1.0
//        Created:  11.11.2018
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
 * Aufgabe 5.1
 * Chiffrieren mit ROT13
 */
void aufgabe_5_1() {
    string ifs_filename = "../klartext-5-1.txt"; // Dateiname
    ifstream ifs; // Dateistream initialisieren
    ifs.open(ifs_filename); // Datei öffnen
    if (!ifs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(1);
    }

    string ofs_filename = "../geheim-5-1.txt"; // Dateiname
    ofstream ofs; // Dateistream initialisieren
    ofs.open(ofs_filename); // Datei öffnen
    if (!ofs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(2);
    }

    // ROT13 Tabelle
    const char rot13[] = {'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};

    char c;
    while ((c = ifs.get()) != EOF) {
        // Wenn Zeichen ein Buchstabe ist, in Großbuchstabe umwandeln, dann 'A' subtrahieren, um den Index für 'rot13' zu errechnen
        if (isalpha(c))
            ofs << rot13[toupper(c) - 'A'];
        else
            ofs << c;
    }

    ifs.close();
    ofs.close();
}

/**
 * Wendet ein Feld mit einer bestimmten Länge, sodass die Reihenfolge der Elemente bis zu dieser Länge umgekehrt wird.
 * @param a Das zu wendende Feld
 * @param n Die Länge des Felds
 */
void feld_wenden(char a[], unsigned int n) {
    for (int i = 0; i < n / 2; i++) { // Array bis zur Hälfte durchlaufen
        char tmp = a[i]; // Erstes Element sichern
        a[i] = a[n - 1 - i]; // Letztes Element in erstes schreiben
        a[n - 1 - i] = tmp; // Erstes Element in letztes schreiben
    }
}

/**
 * Rotiert ein Feld der Länge 'n' um 'shift' Stellen nach links.
 * @param a Das zu rotierende Feld
 * @param n Die Länge des Felds
 * @param shift Die Anzahl der Stellen, um die rotiert wird
 */
void feld_links_rotieren(char a[], unsigned int n, unsigned int shift) {
    if (shift == 0) return; // Performanceoptimierung
    if (shift >= n) shift %= n; // Wenn 'shift' größer als 'n' ist, dann modulo 'n'

    feld_wenden(a, shift);
    feld_wenden(a, n);
    feld_wenden(a, n - shift);
}

/**
 * Rotiert ein Feld der Länge 'n' um 'shift' Stellen nach rechts.
 * @param a Das zu rotierende Feld
 * @param n Die Länge des Felds
 * @param shift Die Anzahl der Stellen, um die rotiert wird
 */
void feld_rechts_rotieren(char a[], unsigned int n, unsigned int shift) {
    if (shift == 0) return; // Performanceoptimierung
    if (shift >= n) shift %= n; // Wenn 'shift' größer als 'n' ist, dann modulo 'n'

    feld_wenden(a, n - shift);
    feld_wenden(a, n);
    feld_wenden(a, shift);
}

/**
 * Aufgabe 5.2
 * Caesar-Verschlüsselung
 */
void aufgabe_5_2() {
    string ifs_filename = "../klartext-5-1.txt"; // Dateiname
    ifstream ifs; // Dateistream initialisieren
    ifs.open(ifs_filename); // Datei öffnen
    if (!ifs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(1);
    }

    string ofs_filename = "../geheim-5-1.txt"; // Dateiname
    ofstream ofs; // Dateistream initialisieren
    ofs.open(ofs_filename); // Datei öffnen
    if (!ofs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(2);
    }

    char caesar[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

    feld_rechts_rotieren(caesar, 26, 5); // Alphabet rotieren

    cout << caesar << endl;

    char c;
    while ((c = ifs.get()) != EOF) {
        // Wenn Zeichen ein Buchstabe ist, in Großbuchstabe umwandeln, dann A subtrahieren, um den Index für 'caesar' zu errechnen
        if (isalpha(c))
            ofs << caesar[toupper(c) - 'A'];
        else
            ofs << c;
    }

    ifs.close();
    ofs.close();
}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    cout << "Hello, World!" << endl << endl;

    //aufgabe_5_1();
    //cout << endl;
    aufgabe_5_2();
    cout << endl;

    return 0;
}

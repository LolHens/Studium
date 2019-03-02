// =============================================================================
//
//       Filename:  aufgabe4.cpp
//
//    Description:  State Machines
//
//        Version:  1.0
//        Created:  27.10.2018
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
#include <windows.h>

using namespace std;

/**
 * Aufgabe 4.1
 * Zählen von Klein-, Großbuchstaben und Ziffern
 */
void aufgabe_4_1() {
    int maxstring = 256;                    // Puffergröße
    char text[maxstring];                   // Eingabepuffer

    cout << "***** Klein- und Großbuchstaben abzählen *****" << endl;
    cout << "Geben Sie eine Textzeile ein: ";

    {
        char c;
        int i = 0;
        while (i < maxstring - 1 && (c = cin.get()) != '\n') {       // Einzelzeichen lesen
            text[i] = c;                        //  und im Feld ablegen
            i = i + 1;                          // Schleifenzähler erhöhen
        }
        text[i] = '\0';                         // Zeichenkette abschließen
    }

    cout << "Der eingegebene Text lautet '" << text << "'" << endl;

    int summeBuchstaben = 0;
    int summeZiffern = 0;

    for (int i = 0; text[i] != '\0'; i += 1) {
        if (isalpha(text[i])) summeBuchstaben++;
        if (isdigit(text[i])) summeZiffern++;
    }
    cout << setw(6) << summeBuchstaben << " Buchstaben" << endl;
    cout << setw(6) << summeZiffern << " Ziffern" << endl;
}

/**
 * Aufgabe 4.2
 * Zählen von Wörtern
 */
void aufgabe_4_2() {
    cout << "***** Wörter abzählen *****" << endl;

    int maxstring = 256;                    // Puffergröße
    char text[maxstring];                   // Eingabepuffer

    cout << "Geben Sie eine Textzeile ein: ";

    {
        char c;
        int i = 0;
        while (i < maxstring - 1 && (c = cin.get()) != '\n') {       // Einzelzeichen lesen
            text[i] = c;                        //  und im Feld ablegen
            i = i + 1;                          // Schleifenzähler erhöhen
        }
        text[i] = '\0';                         // Zeichenkette abschließen
    }

    cout << "Der eingegebene Text lautet '" << text << "'" << endl;

    const int ZUSTAND_LEER = 0;
    const int ZUSTAND_WORD = 1;

    int zustand = ZUSTAND_LEER;
    int summeWoerter = 0;

    for (int i = 0; text[i] != '\0'; i += 1) {
        if (isspace(text[i])) {
            zustand = ZUSTAND_LEER;
        } else {
            if (zustand == ZUSTAND_LEER) summeWoerter++;
            zustand = ZUSTAND_WORD;
        }
    }
    cout << setw(6) << summeWoerter << " Wörter" << endl;

}

/**
 * Aufgabe 4.3
 * Zählen von Wörtern und Zahlen
 */
void aufgabe_4_3() {
    cout << "***** Wörter abzählen *****" << endl;

    string dateiname = "text-4-3.txt"; // Dateiname
    ifstream ifs; // Dateistream initialisieren
    ifs.open(dateiname); // Datei öffnen
    if (!ifs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(1);
    }

    int maxstring = 256;                    // Puffergröße
    char text[maxstring];                   // Eingabepuffer

    {
        char c;
        int i = 0;
        while (i < maxstring - 1 && (text[i] = ifs.get()) != EOF) { // Zeilen lesen
            i = i + 1;                          // Schleifenzähler erhöhen
        }
        text[i] = '\0';                         // Zeichenkette abschließen
    }

    cout << "Der eingelesene Text lautet '" << text << "'" << endl;

    const int ZUSTAND_LEER = 0;
    const int ZUSTAND_WORD = 1;
    const int ZUSTAND_ZAHL = 2;

    int zustand = ZUSTAND_LEER;
    int summeWoerter = 0;
    int summeZahlen = 0;

    for (int i = 0; text[i] != '\0'; i += 1) {
        if (isspace(text[i])) { // Wenn nächstes Zeichen Leerzeichen ist
            zustand = ZUSTAND_LEER;
        } else if (isdigit(text[i])) { // Wenn nächstes Zeichen Zahl ist
            if (zustand == ZUSTAND_LEER) summeZahlen++;  // Wenn neue Zahl beginnt
            else if (zustand == ZUSTAND_WORD) { // Wenn in einem Wort
                cout << "ERROR: Eine Zahl kann nicht im Wort vorkommen!";
                exit(2);
            }
            zustand = ZUSTAND_ZAHL;
        } else { // Wenn nächstes Zeichen Buchstabe oder sonstiges Zeichen ist
            if (zustand == ZUSTAND_LEER) summeWoerter++;  // Wenn neues Wort beginnt
            else if (zustand == ZUSTAND_ZAHL) {  // Wenn in einer Zahl
                cout << "ERROR: Eine Zahl kann nicht im Wort vorkommen!";
                exit(3);
            }
            zustand = ZUSTAND_WORD;
        }
    }
    cout << setw(6) << summeWoerter << " Wörter" << endl;
    cout << setw(6) << summeZahlen << " Zahlen" << endl;

}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    cout << "Hello, World!" << endl << endl;

    aufgabe_4_1();
    cout << endl;
    aufgabe_4_2();
    cout << endl;
    aufgabe_4_3();
    cout << endl;

    return 0;
}

//
// Created by pierr on 30.01.2019.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cfloat>
#include <string.h>

#include <Windows.h>

using namespace std;

bool munchtest(string zahl) {
    unsigned int summe = 0;
    unsigned int potenzSumme = 0;
    unsigned int cIndex = 0;
    char c = 0;
    while ((c = zahl[cIndex++])) {
        if (!isdigit(c)) cerr << "Keine gültige Zahl eingegeben!" << endl;
        int ziffer = c - '0';
        summe = summe * 10 + ziffer;
        int potenz = 1;
        for (int i = 0; i < ziffer; i++) potenz *= ziffer;
        potenzSumme += potenz;
    }
    return summe == potenzSumme;
}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    cout << "Hello, World!" << endl << endl;

    munchtest("3435");
    cout << endl;

    return 0;
}

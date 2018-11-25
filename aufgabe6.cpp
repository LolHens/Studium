// =============================================================================
//
//       Filename:  aufgabe6.cpp
//
//    Description:  Luhn-Algorythmus
//
//        Version:  1.0
//        Created:  25.11.2018
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

typedef unsigned int uint;

const unsigned int nmat = 10;

/**
 * Diagonale in Matrix zeichnen
 * @param mat Die Matrix
 * @param n X und Y Größe der Matrix
 * @param diag Dicke der Diagonalen
 * @param value Wert mit dem die Diagonale gefüllt werden soll
 */
void matrix_diag(int mat[nmat][nmat], uint n, int diag, int value) {
    if (diag > 2 * n - 1) diag = 2 * n - 1;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            // Abstand zur Diagonalen
            int offset = x - y;
            if (offset < 0) offset *= -1;

            if (offset < (diag + 1) / 2) {
                mat[x][y] = value;
            } else {
                mat[x][y] = 0;
            }
        }
    }
}

/**
 * Dreieck von oben links in die Matrix zeichnen
 * @param mat Die Matrix
 * @param n X und Y Größe der Matrix
 * @param k Größe des Dreiecks
 * @param value Wert mit dem das Dreieck gefüllt werden soll
 */
void matrix_dreieck(int mat[nmat][nmat], uint n, int k, int value) {
    if (k > 2 * n - 1) k = 2 * n - 1;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            // Abstand zur oberen linken Ecke
            int offset = x + y;

            if (offset < k) {
                mat[x][y] = value;
            } else {
                mat[x][y] = 0;
            }
        }
    }
}

/**
 * Rahmen in die Matrix zeichnen
 * @param mat Die Matrix
 * @param n X und Y Größe der Matrix
 * @param frame Breite des Rahmens
 * @param value Wert mit dem der Rahmen gefüllt werden soll
 */
void matrix_frame(int mat[nmat][nmat], uint n, uint frame, int value) {
    if (frame > n / 2 + 1) frame = n / 2 + 1;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (x < frame || x >= n - frame || y < frame || y >= n - frame) {
                mat[x][y] = value;
            } else {
                mat[x][y] = 0;
            }
        }
    }
}

/**
 * Matrix mit Nullen füllen
 * @param mat Die Matrix
 * @param n X und Y Größe der Matrix
 */
void matrix_null(int mat[nmat][nmat], uint n) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            mat[x][y] = 0;
        }
    }
}

/**
 * Matrix ausgeben
 * @param mat Die Matrix
 * @param n X und Y Größe der Matrix
 */
void matrix_print(int mat[nmat][nmat], uint n) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cout << setw(4) << mat[x][y];
        }

        cout << endl;
    }
}

/**
 * Aufgabe 6.1
 * Matrix füllen und ausgeben
 */
void aufgabe_6_1() {
    int mat[nmat][nmat];

    cout << "Null:" << endl;
    matrix_null(mat, nmat);
    matrix_print(mat, nmat);

    cout << "Frame:" << endl;
    matrix_frame(mat, nmat, 2, 1);
    matrix_print(mat, nmat);
    cout << endl;

    cout << "Diag:" << endl;
    matrix_diag(mat, nmat, 3, 1);
    matrix_print(mat, nmat);
    cout << endl;

    cout << "Dreieck:" << endl;
    matrix_dreieck(mat, nmat, 5, 1);
    matrix_print(mat, nmat);
    cout << endl;
}

bool luhn_check(string number) {
    int summe = 0;
    char c;
    int i = 0;
    while ((c = number[i]) != '\0') {
        int ziffer = c - '0';
        int gewichtet = ziffer * ((i % 2) + 1);
        int einerstelle = gewichtet % 10;
        int zehnerstelle = gewichtet / 10;
        int quersumme = einerstelle + zehnerstelle;
        summe += quersumme;

        i++;
    }

    // Ist die Einerstelle der Summe == 0?
    return summe % 10 == 0;
}

/**
 * Aufgabe 6.2
 * Luhn-Algorythmus
 */
void aufgabe_6_2() {
    cout << (luhn_check("61789372994") ? "true" : "false") << endl;
    cout << (luhn_check("446667651") ? "true" : "false") << endl;
    cout << (luhn_check("49927398716") ? "true" : "false") << endl;
    cout << (luhn_check("49927398717") ? "true" : "false") << endl;
    cout << (luhn_check("1234567812345678") ? "true" : "false") << endl;
    cout << (luhn_check("1234567812345670") ? "true" : "false") << endl;
}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    cout << "Hello, World!" << endl << endl;

    aufgabe_6_1();
    cout << endl;
    aufgabe_6_2();
    cout << endl;

    return 0;
}

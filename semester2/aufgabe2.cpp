// =============================================================================
//
//       Filename:  aufgabe1.cpp
//
//    Description:  Game of life
//
//        Version:  1.0
//        Created:  14.03.2019
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
#include <string.h>
#include <windows.h>

using namespace std;

typedef unsigned int uint;

/**
 * Feld zufällig mit 0 oder 1 füllen
 * @param field Zu füllendes Feld
 * @param rows Anzahl der Zeilen
 * @param cols Anzahl der Spalten
 */
void zufallsbelegung(int** field, uint rows, uint cols) {
    // Seed für Zufallsgeneator aus aktueller Zeit festlegen
    srand(time(NULL));

    for (uint row = 0; row < rows; row++)
        for (uint col = 0; col < cols; col++)
            field[row][col] = rand() % 2;
}

/**
 * Die nächste Generation des Feldes berechnen
 * @param field1 Feld für aktuelle Generation
 * @param field2 Feld für nächste Generation
 * @param rows Anzahl der Zeilen
 * @param cols Anzahl der Spalten
 * @return Anzahl der lebenden Zellen der neuen Generation
 */
uint next_generation(int** field1, int** field2, uint rows, uint cols) {
    uint numAlive = 0;

    for (uint row = 0; row < rows; row++)
        for (uint col = 0; col < cols; col++) {
            int numNeighbors = 0;
            for (int rowOff = -1; rowOff <= 1; rowOff++)
                for (int colOff = -1; colOff <= 1; colOff++) {
                    int newRow = row + rowOff;
                    int newCol = col + colOff;
                    if (!(rowOff == 0 && colOff == 0) &&
                        !(row == 0 && rowOff < 0) && newRow < rows &&
                        !(col == 0 && colOff < 0) && newCol < cols)
                        numNeighbors += field1[newRow][newCol];
                }

            int newCell = field1[row][col];

            if (numNeighbors < 2 || numNeighbors > 3)
                newCell = 0;
            else if (numNeighbors == 3)
                newCell = 1;

            field2[row][col] = newCell;

            numAlive += newCell;
        }

    return numAlive;
}

/**
 * Feld in Konsole ausgeben
 * @param field Auszugebenes Feld
 * @param rows Anzahl der Zeilen
 * @param cols Anzahl der Spalten
 */
void print_feld(int** field, uint rows, uint cols) {
    char* feldAusgabe = new char[(cols * 2) * rows + 1];
    unsigned int i = 0;
    for (uint row = 0; row < rows; row++) {
        for (uint col = 0; col < cols; col++) {
            if (col > 0) feldAusgabe[i++] = ' ';
            feldAusgabe[i++] = field[row][col] ? '#' : ' ';
        }
        feldAusgabe[i++] = '\n';
    }
    feldAusgabe[i] = '\0';
    cout << feldAusgabe;
}

/**
 * Neue Matrix erstellen
 * @param rows Anzahl der Zeilen
 * @param cols Anzahl der Spalten
 * @return Erstellte Matrix
 */
int** new_int_matrix(uint rows, uint cols) {
    int** array = new int* [rows]; // allocate pointer array
    *array = new int[rows * cols](); // allocate and initialize data array
    for (uint i = 1; i < rows; i++) // set pointers
        array[i] = array[i - 1] + cols;
    return array;
}

/**
 * Matrix freigeben
 * @param array Matrix
 */
void delete_int_matrix(int** array) {
    delete[] *array; // delete data array
    delete[] array; // delete pointer array
}


/**
 * Aufgabe 2.1
 * Game of life
 */
void aufgabe_2_1() {
    uint rows = 28;
    uint cols = 60;
    int** matrix = new_int_matrix(rows, cols);
    zufallsbelegung(matrix, rows, cols);
    print_feld(matrix, rows, cols);
    cout << endl;

    int c;
    while ((c = getchar()) == '\n') {
        int** matrix2 = new_int_matrix(rows, cols);
        uint numAlive = next_generation(matrix, matrix2, rows, cols);
        delete_int_matrix(matrix);
        matrix = matrix2;

        print_feld(matrix, rows, cols);
        cout << numAlive << endl;
    }

    cout << "exit" << endl;

    delete_int_matrix(matrix);
}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    cout << "Hello, World!" << endl << endl;

    aufgabe_2_1();
    cout << endl;

    return 0;
}

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

struct bmpHeader {
   unsigned short int bfType;
   unsigned int bfSize;
   unsigned int bfReserved;
   unsigned int bfOffBits;
   unsigned int biSize;
   int biWidth;
   int biHeight;
   unsigned short int biPlanes;
   unsigned short int biBitCount;
   unsigned int biCompression;
   unsigned int biSizeImage;
   int biXPelsPerMeter;
   int biYPelsPerMeter;
   unsigned int biClrUsed;
   unsigned int biClrImportant;
};

char* encodeBmp(char grayBytes[], int width, int height) {
    const int bitmapFileHeaderLength = 14;
    const int bitmapInfoHeaderLength = 40;
    const int bitmapHeaderLength = bitmapFileHeaderLength + bitmapInfoHeaderLength;
    const int colorTableLength = 4 * 2;
    const int colorMapLength = width * height;
    const int bitmapFileLength = bitmapHeaderLength + colorTableLength + colorMapLength;

    struct bmpHeader header;
    header.bfType = 0x424D;
    header.bfSize = bitmapFileLength;
    header.bfReserved = 0;
    header.bfOffBits = bitmapHeaderLength;
    header.biSize = bitmapInfoHeaderLength;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = 1;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;

    /*int bmpLength = headerLength + lenght;
    char[] header = {0x424D,
                     bmpLength,
                     0,
                     headerLength,
                     };*/
}

/**
 *
 */
void aufgabe_7_1() {
    string ifs_filename = "../dreifach-7-1.pgm"; // Dateiname
    ifstream ifs; // Dateistream initialisieren
    ifs.open(ifs_filename); // Datei öffnen
    if (!ifs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(1);
    }

    cout << "TEST" << endl;

    char* field = 0;
    ifs >> field;
    ifs >> field;
    const int width = atoi(field);
    ifs >> field;
    const int height = atoi(field);
    ifs >> field;

    char colors[width][height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ifs >> field;
            colors[x][y] = (char) atoi(field);
        }
    }

    string ofs_filename = "../dreifach-out-7-1.pgm"; // Dateiname
    ofstream ofs; // Dateistream initialisieren
    ofs.open(ofs_filename); // Datei öffnen
    if (!ofs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(2);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ifs >> field;
            colors[x][y] = (char) atoi(field);
        }
    }
}

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    cout << "Hello, World!" << endl << endl;

    aufgabe_7_1();
    cout << endl;

    return 0;
}

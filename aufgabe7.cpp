// =============================================================================
//
//       Filename:  aufgabe7.cpp
//
//    Description:  Bearbeiten von Bildern
//
//        Version:  1.0
//        Created:  13.12.2018
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

#pragma pack(1)
struct bmpHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint32_t bfReserved;
    uint32_t bfOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

void writeBmp(ofstream &ofs, const char *grayBytes, int width, int height) {
    const int bitmapFileHeaderLength = 14;
    const int bitmapInfoHeaderLength = 40;
    const int bitmapHeaderLength = bitmapFileHeaderLength + bitmapInfoHeaderLength;

    bmpHeader header = {
            .bfType = 0x4D42,
            .bfSize = 0,
            .bfReserved = 0,
            .bfOffBits = (unsigned int) bitmapHeaderLength,
            .biSize = bitmapInfoHeaderLength,
            .biWidth = (unsigned int) width,
            .biHeight = (unsigned int) height,
            .biPlanes = 1,
            .biBitCount = 32,
            .biCompression = 0,
            .biSizeImage = 0,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };

    ofs.write((char *) &header, sizeof(header));

    char bytes[width * height * 4];

    int i = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char color = *(grayBytes + (height - y - 1) + x * height);
            bytes[i++] = color;
            bytes[i++] = color;
            bytes[i++] = color;
            bytes[i++] = 0;
        }
    }

    ofs.write(bytes, sizeof(bytes));
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

    string field;
    ifs >> field;
    ifs >> field;
    const int width = atoi(field.c_str());
    ifs >> field;
    const int height = atoi(field.c_str());
    ifs >> field;

    char colors[width][height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ifs >> field;
            colors[x][y] = (char) atoi(field.c_str());
        }
    }

    ifs.close();

    string ofs_filename = "../dreifach-out-7-1.bmp"; // Dateiname
    ofstream ofs; // Dateistream initialisieren
    ofs.open(ofs_filename, ofstream::binary); // Datei öffnen
    if (!ofs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(2);
    }

    writeBmp(ofs, (char *) &colors, width, height);

    ofs.close();

    /*for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ifs >> field;
            colors[x][y] = (char) atoi(field);
        }
    }*/
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

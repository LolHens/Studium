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

/**
 * Struct for the header of the BMP file format
 */
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

/**
 * Write the image as BMP
 *
 * @param filename name of the output file
 * @param colors image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 */
void writeBmp(string filename, unsigned char *colors, int width, int height) {
    ofstream ofs; // Dateistream initialisieren
    ofs.open(filename, ofstream::binary); // Datei öffnen
    if (!ofs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(2);
    }

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

    int i = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const int invertedY = height - y - 1;
            char color = colors[x * height + invertedY];
            char bytes[] = {color, color, color, 0};
            ofs.write(bytes, sizeof(bytes));
        }
    }

    ofs.close();
}

/**
 * Read an image from a PGM file
 *
 * @param filename name of the file
 * @param width returned width of the image
 * @param height returned height of the image
 * @return colors image as flat array of graytones
 */
unsigned char *readPgm(string filename, int &width, int &height) {
    ifstream ifs; // Dateistream initialisieren
    ifs.open(filename); // Datei öffnen
    if (!ifs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(1);
    }

    string field;
    ifs >> field;

    if (strcmp(field.c_str(), "P2") != 0) {
        cerr << endl << "ERROR: Falsches Format" << endl;
        exit(1);
    }

    ifs >> field;
    width = stoi(field);
    ifs >> field;
    height = stoi(field);
    ifs >> field;

    auto *colors = (unsigned char *) malloc(width * height * sizeof(unsigned char));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ifs >> field;
            colors[x * height + y] = (unsigned char) stoi(field);
        }
    }

    ifs.close();

    return colors;
}


/**
 * Write the image as PGM
 *
 * @param filename name of the output file
 * @param colors image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 */
void writePgm(string filename, unsigned char *colors, int width, int height) {
    ofstream ofs; // Dateistream initialisieren
    ofs.open(filename); // Datei öffnen
    if (!ofs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(2);
    }

    ofs << "P2" << endl;
    ofs << width << " " << height << endl;
    ofs << 255 << endl;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char color = colors[x * height + y];
            ofs << " " << setw(3) << (int) color;
        }
        ofs << endl;
    }

    ofs.close();
}

/**
 * Aufgabe 7.1
 * Read and then write an image
 */
void aufgabe_7_1() {
    string ifs_filename = "../dreifach-7-1.pgm"; // Dateiname
    int width, height;
    unsigned char *colors = readPgm(ifs_filename, width, height);

    string ofs_filename = "../dreifach-out-7-1.bmp"; // Dateiname
    writeBmp(ofs_filename, colors, width, height);

    string ofs_filename2 = "../dreifach-out-7-1.pgm"; // Dateiname
    writePgm(ofs_filename2, colors, width, height);

    free(colors);
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

// =============================================================================
//
//       Filename:  aufgabe1.cpp
//
//    Description:  Bearbeiten von Bildern
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

typedef unsigned char Pixel;

struct pgm_bild {
    char magic[2]; // Bildtyp
    int nx; // Zeilenzahl
    int ny; // Spaltenzahl
    int graumax; // Max. Grauwert
    Pixel* bild; // Bildmatrix
};

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
 * Read Pixel from image
 * @param image image as flat array of graytones
 * @param x x position
 * @param y y position
 * @param height height of the image
 * @return color at the given position
 */
Pixel getPixel(pgm_bild* bild, int x, int y) {
    return bild->bild[x * bild->ny + y];
}

/**
 * Write Pixel in an image
 * @param image image as flat array of graytones
 * @param x x position
 * @param y y position
 * @param height height of the image
 * @param color color to write
 */
void setPixel(pgm_bild* bild, int x, int y, Pixel color) {
bild->bild[x * bild->ny + y] = color;
}

/**
 * Write the image as BMP
 * @param filename name of the output file
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 */
void bild_schreiben_bmp(string ofs_file_name, pgm_bild* bild) {
    ofstream ofs; // Dateistream initialisieren
    ofs.open(ofs_file_name, ofstream::binary); // Datei öffnen
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
            .biWidth = (unsigned int) bild->nx,
            .biHeight = (unsigned int) bild->ny,
            .biPlanes = 1,
            .biBitCount = 32,
            .biCompression = 0,
            .biSizeImage = 0,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };

    ofs.write((char*) &header, sizeof(header));

    int i = 0;
    for (int y = 0; y < bild->ny; y++)
        for (int x = 0; x < bild->nx; x++) {
            const int invertedY = bild->ny - y - 1;
            char color = getPixel(bild, x, invertedY);
            char bytes[] = {color, color, color, 0};
            ofs.write(bytes, sizeof(bytes));
        }

    ofs.close();
}

/**
 * Read an image from a PGM file
 * @param filename name of the file
 * @param width returned width of the image
 * @param height returned height of the image
 * @param maxGray returned grau max value
 * @return colors image as flat array of graytones
 */
void bild_lesen(pgm_bild* bild, string ifs_file_name) {
    ifstream ifs; // Dateistream initialisieren
    ifs.open(ifs_file_name); // Datei öffnen
    if (!ifs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(1);
    }


    ifs >> bild->magic;
    if (strcmp(bild->magic, "P2") != 0) {
        cerr << endl << "ERROR: Falsches Format" << endl;
        exit(1);
    }

    string field;
    ifs >> field;
    bild->nx = stoi(field);
    ifs >> field;
    bild->ny = stoi(field);
    ifs >> field;
    bild->graumax = stoi(field);

    Pixel* image = (Pixel*) malloc(bild->nx * bild->ny * sizeof(Pixel));

    for (int y = 0; y < bild->ny; y++)
        for (int x = 0; x < bild->nx; x++) {
            ifs >> field;
            setPixel(bild, x, y, (Pixel) stoi(field));
        }

    ifs.close();
}


/**
 * Write the image as PGM
 * @param filename name of the output file
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 */
void bild_schreiben(pgm_bild * bild, string ifs_file_name) {
    ofstream ofs; // Dateistream initialisieren
    ofs.open(ifs_file_name); // Datei öffnen
    if (!ofs) { // Prüfung ob Datei geöffnet werden konnte
        cerr << endl << "ERROR: Datei konnte nicht geöffnet werden" << endl;
        exit(2);
    }

    ofs << "P2" << endl;
    ofs << bild->nx << " " << bild->ny << endl;
    ofs << 255 << endl;

    for (int y = 0; y < bild->ny; y++) {
        for (int x = 0; x < bild->nx; x++) {
            Pixel color = getPixel(bild, x, y);
            ofs << " " << setw(3) << (int) color;
        }
        ofs << endl;
    }

    ofs.close();
}

/**
 * Aufgabe 1.1
 * Read and then write an image
 */
/*void aufgabe_1_1() {
    string ifs_filename = "dreifach-7-1.pgm"; // Dateiname
    int width, height, maxGray;
    Pixel* image = readPgm(ifs_filename, width, height, maxGray);

    string ofs_filename = "dreifach-7-1.out.bmp"; // Dateiname
    writeBmp(ofs_filename, image, width, height);

    string ofs_filename2 = "dreifach-7-1.out.pgm"; // Dateiname
    writePgm(ofs_filename2, image, width, height);

    free(image);
}*/

/**
 * Bild glätten
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @return new image as flat array of graytones
 */
/*Pixel* glaetten(Pixel* image, int width, int height) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sum = 0;
            int numPixels = 0;

            for (int yOffset = -1; yOffset <= 1; yOffset++)
                for (int xOffset = -1; xOffset <= 1; xOffset++) {
                    int newX = x + xOffset;
                    int newY = y + yOffset;

                    if (newX >= 0 &&
                        newY >= 0 &&
                        newX < width &&
                        newY < height) {

                        sum += getPixel(image, newX, newY, height);
                        numPixels++;
                    }
                }

            Pixel newPixel = (Pixel) (sum / numPixels);
            setPixel(newImage, x, y, height, newPixel);
        }
    }

    return newImage;
}*/

/**
 * Bild invertieren
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @param maxGray grau max value
 * @return new image as flat array of graytones
 */
/*Pixel* invertieren(Pixel* image, int width, int height, int maxGray) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            Pixel color = getPixel(image, x, y, height);
            Pixel newPixel = (Pixel) (maxGray - color);
            setPixel(newImage, x, y, height, newPixel);
        }

    return newImage;
}*/

/**
 * Bild Kanten bilden
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @return new image as flat array of graytones
 */
/*Pixel* kantenbildung(Pixel* image, int width, int height) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            Pixel newPixel = 0;

            if (x >= 1 && y >= 1 && x < width - 1 && y < height - 1) {
                int sum = 0;

                for (int yOffset = -1; yOffset <= 1; yOffset++)
                    for (int xOffset = -1; xOffset <= 1; xOffset++) {
                        Pixel pixel = getPixel(image, x + xOffset, y + yOffset, height);

                        if (xOffset == 0 && yOffset == 0)
                            sum += pixel * 4;
                        else if (xOffset == 0 || yOffset == 0)
                            sum += pixel * -1;
                    }

                newPixel = (Pixel) abs(sum / 9);
            }

            setPixel(newImage, x, y, height, newPixel);
        }

    return newImage;
}*/

/**
 * Bild schärfen
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @param maxGray grau max value
 * @return new image as flat array of graytones
 */
/*Pixel* schaerfen(Pixel* image, int width, int height, int maxGray) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            Pixel newPixel = 0;

            if (x >= 1 && y >= 1 && x < width - 1 && y < height - 1) {
                int sum = 0;

                for (int yOffset = -1; yOffset <= 1; yOffset++)
                    for (int xOffset = -1; xOffset <= 1; xOffset++) {
                        Pixel pixel = getPixel(image, x + xOffset, y + yOffset, height);

                        if (xOffset == 0 && yOffset == 0)
                            sum += pixel * 9;
                        else
                            sum += pixel * -1;
                    }

                if (sum < 0) sum = 0;
                else if (sum > maxGray) sum = maxGray;

                newPixel = (Pixel) sum;
            }

            setPixel(newImage, x, y, height, newPixel);
        }

    return newImage;
}*/

/**
 * Aufgabe 7.2
 * Read, edit and then write an image
 */
/*void aufgabe_7_2() {
    string ifs_filename = "dreifach-7-1.pgm"; // Dateiname
    int width, height, maxGray;
    Pixel* image = readPgm(ifs_filename, width, height, maxGray);

    {
        Pixel* newImage = glaetten(image, width, height);

        string ofs_filename = "dreifach-glaetten-7-1.out.bmp"; // Dateiname
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "dreifach-glaetten-7-1.out.pgm"; // Dateiname
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    {
        Pixel* newImage = invertieren(image, width, height, maxGray);

        string ofs_filename = "dreifach-invertieren-7-1.out.bmp";
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "dreifach-invertieren-7-1.out.pgm";
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    {
        Pixel* newImage = kantenbildung(image, width, height);

        string ofs_filename = "dreifach-kantenbildung-7-1.out.bmp";
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "dreifach-kantenbildung-7-1.out.pgm";
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    {
        Pixel* newImage = schaerfen(image, width, height, maxGray);

        string ofs_filename = "dreifach-schaerfen-7-1.out.bmp";
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "dreifach-schaerfen-7-1.out.pgm";
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    free(image);
}*/

//-----------------------------------------------------------------------------
//  Hauptprogramm
//-----------------------------------------------------------------------------
int main() {
    // Terminal CodePage auf UTF8 setzen, um Sonderzeichen korrekt auszugeben
    SetConsoleOutputCP(CP_UTF8);

    // Die Welt begrüßen
    cout << "Hello, World!" << endl << endl;

    aufgabe_1_1();
    cout << endl;
    //aufgabe_1_2();
    //cout << endl;

    return 0;
}

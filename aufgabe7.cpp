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

typedef unsigned char Pixel;

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
Pixel getPixel(Pixel* image, int x, int y, int height) {
    return image[x * height + y];
}

/**
 * Write Pixel in an image
 * @param image image as flat array of graytones
 * @param x x position
 * @param y y position
 * @param height height of the image
 * @param color color to write
 */
void setPixel(Pixel* image, int x, int y, int height, Pixel color) {
    image[x * height + y] = color;
}

/**
 * Write the image as BMP
 * @param filename name of the output file
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 */
void writeBmp(string filename, Pixel* image, int width, int height) {
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

    ofs.write((char*) &header, sizeof(header));

    int i = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const int invertedY = height - y - 1;
            char color = getPixel(image, x, invertedY, height);
            char bytes[] = {color, color, color, 0};
            ofs.write(bytes, sizeof(bytes));
        }
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
Pixel* readPgm(string filename, int& width, int& height, int& maxGray) {
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
    maxGray = stoi(field);

    Pixel* image = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ifs >> field;
            setPixel(image, x, y, height, (Pixel) stoi(field));
        }
    }

    ifs.close();

    return image;
}


/**
 * Write the image as PGM
 * @param filename name of the output file
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 */
void writePgm(string filename, Pixel* image, int width, int height) {
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
            Pixel color = getPixel(image, x, y, height);
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
    int width, height, maxGray;
    Pixel* image = readPgm(ifs_filename, width, height, maxGray);

    string ofs_filename = "../dreifach-7-1.out.bmp"; // Dateiname
    writeBmp(ofs_filename, image, width, height);

    string ofs_filename2 = "../dreifach-7-1.out.pgm"; // Dateiname
    writePgm(ofs_filename2, image, width, height);

    free(image);
}

/**
 * Bild glätten
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @return new image as flat array of graytones
 */
Pixel* glaetten(Pixel* image, int width, int height) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sum = getPixel(image, x, y, height);
            int pixels = 1;
            if (x - 1 >= 0) {
                sum += getPixel(image, x - 1, y, height);
                pixels++;

                if (y - 1 >= 0) {
                    sum += getPixel(image, x - 1, y - 1, height);
                    pixels++;
                }
            }
            if (y - 1 >= 0) {
                sum += getPixel(image, x, y - 1, height);
                pixels++;

                if (x + 1 < width) {
                    sum += getPixel(image, x + 1, y - 1, height);
                    pixels++;
                }
            }
            if (x + 1 < width) {
                sum += getPixel(image, x + 1, y, height);
                pixels++;

                if (y + 1 < height) {
                    sum += getPixel(image, x + 1, y + 1, height);
                    pixels++;
                }
            }
            if (y + 1 < height) {
                sum += getPixel(image, x, y + 1, height);
                pixels++;

                if (x - 1 >= 0) {
                    sum += getPixel(image, x - 1, y + 1, height);
                    pixels++;
                }
            }

            Pixel newPixel = (Pixel) (sum / pixels);
            setPixel(newImage, x, y, height, newPixel);
        }
    }

    return newImage;
}

/**
 * Bild invertieren
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @param maxGray grau max value
 * @return new image as flat array of graytones
 */
Pixel* invertieren(Pixel* image, int width, int height, int maxGray) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel color = getPixel(image, x, y, height);
            Pixel newPixel = (Pixel) (maxGray - color);
            setPixel(newImage, x, y, height, newPixel);
        }
    }

    return newImage;
}

/**
 * Bild Kanten bilden
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @return new image as flat array of graytones
 */
Pixel* kantenbildung(Pixel* image, int width, int height) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x >= 1 && y >= 1 && x < width - 1 && y < height - 1) {
                int sum = getPixel(image, x, y, height) * 4;
                sum += getPixel(image, x - 1, y, height) * -1;
                sum += getPixel(image, x, y - 1, height) * -1;
                sum += getPixel(image, x + 1, y, height) * -1;
                sum += getPixel(image, x, y + 1, height) * -1;

                Pixel newPixel = (Pixel) abs(sum / 9);
                setPixel(newImage, x, y, height, newPixel);
            } else {
                setPixel(newImage, x, y, height, 0);
            }
        }
    }

    return newImage;
}

/**
 * Bild schärfen
 * @param image image as flat array of graytones
 * @param width width of the image
 * @param height height of the image
 * @param maxGray grau max value
 * @return new image as flat array of graytones
 */
Pixel* schaerfen(Pixel* image, int width, int height, int maxGray) {
    Pixel* newImage = (Pixel*) malloc(width * height * sizeof(Pixel));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x >= 1 && y >= 1 && x < width - 1 && y < height - 1) {
                int sum = getPixel(image, x, y, height) * 9;
                sum += getPixel(image, x - 1, y, height) * -1;
                sum += getPixel(image, x, y - 1, height) * -1;
                sum += getPixel(image, x + 1, y, height) * -1;
                sum += getPixel(image, x, y + 1, height) * -1;
                sum += getPixel(image, x - 1, y - 1, height) * -1;
                sum += getPixel(image, x + 1, y - 1, height) * -1;
                sum += getPixel(image, x + 1, y + 1, height) * -1;
                sum += getPixel(image, x - 1, y + 1, height) * -1;
                if (sum < 0) sum = 0;
                else if (sum > maxGray) sum = maxGray;

                Pixel newPixel = (Pixel) sum;
                setPixel(newImage, x, y, height, newPixel);
            } else {
                setPixel(newImage, x, y, height, 0);
            }
        }
    }

    return newImage;
}

/**
 * Aufgabe 7.2
 * Read, edit and then write an image
 */
void aufgabe_7_2() {
    string ifs_filename = "../dreifach-7-1.pgm"; // Dateiname
    int width, height, maxGray;
    Pixel* image = readPgm(ifs_filename, width, height, maxGray);

    {
        Pixel* newImage = glaetten(image, width, height);

        string ofs_filename = "../dreifach-glaetten-7-1.out.bmp"; // Dateiname
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "../dreifach-glaetten-7-1.out.pgm"; // Dateiname
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    {
        Pixel* newImage = invertieren(image, width, height, maxGray);

        string ofs_filename = "../dreifach-invertieren-7-1.out.bmp";
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "../dreifach-invertieren-7-1.out.pgm";
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    {
        Pixel* newImage = kantenbildung(image, width, height);

        string ofs_filename = "../dreifach-kantenbildung-7-1.out.bmp";
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "../dreifach-kantenbildung-7-1.out.pgm";
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    {
        Pixel* newImage = schaerfen(image, width, height, maxGray);

        string ofs_filename = "../dreifach-schaerfen-7-1.out.bmp";
        writeBmp(ofs_filename, newImage, width, height);

        string ofs_filename2 = "../dreifach-schaerfen-7-1.out.pgm";
        writePgm(ofs_filename2, newImage, width, height);

        free(newImage);
    }

    free(image);
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
    aufgabe_7_2();
    cout << endl;

    return 0;
}

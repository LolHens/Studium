#include <iostream>

using namespace std;

char* uintToFormattedBitString(unsigned int value, char delimeter, int blocksize) {
    int bitanzahl = 0;
    for (int i = 0; i < sizeof(unsigned int) * 8; i++) {
        if (1 << i > value)
            break;

        bitanzahl++;
    }

    char* array = new char[bitanzahl + 1 + bitanzahl / blocksize];

    int arrayIndex = 0;

    for (int i = 0; i < bitanzahl; i++) {
        if ((1 << (bitanzahl - 1 - i) & value) > 0)
            array[arrayIndex++] = '1';
        else
            array[arrayIndex++] = '0';

        if ((bitanzahl - 1 - i) % blocksize == 0)
            array[arrayIndex++] = delimeter;
    }

    array[arrayIndex] = '\0';

    return array;

}

int main() {
    unsigned int value = 0;
    cout << "Gib eine Zahl ein:" << endl;
    cin >> value;
    char* array = uintToFormattedBitString(value, ' ', 2);
    cout << array << endl;
    delete array;
}

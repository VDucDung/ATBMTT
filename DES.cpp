#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

// Placeholder definitions for necessary tables and arrays
const int E[48] = {
    32, 1, 2, 3, 4, 5, 4, 5,
    6, 7, 8, 9, 8, 9, 10, 11,
    12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21,
    22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1
};

const int S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

const int IP_INV[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

const int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

const int SHIFTS[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Hàm hoán v?
bitset<32> permutation(bitset<32> input, const int* table, int size) {
    bitset<32> output;
    for (int i = 0; i < size; i++) {
        output[i] = input[table[i] - 1];
    }
    return output;
}

// Hàm d?ch trái xoay vòng
bitset<28> leftCircularShift(bitset<28> input, int shift) {
    return (input << shift) | (input >> (28 - shift));
}

// Hàm n?i hai bitset
bitset<64> concatenate(bitset<32> left, bitset<32> right) {
    bitset<64> output;
    for (int i = 0; i < 32; i++) {
        output[i] = left[i];
        output[i + 32] = right[i];
    }
    return output;
}

// Hàm chia dôi m?t bitset
void split(bitset<64> input, bitset<32>& left, bitset<32>& right) {
    for (int i = 0; i < 32; i++) {
        left[i] = input[i];
        right[i] = input[i + 32];
    }
}

// Hàm m? r?ng bitset t? 32 bit lên 48 bit
bitset<48> expand(bitset<32> input, const int* table, int size) {
    bitset<48> output;
    for (int i = 0; i < size; i++) {
        output[i] = input[table[i] - 1];
    }
    return output;
}

// Hàm tính hàm f
bitset<32> f(bitset<32> right, bitset<48> subkey) {
    // M? r?ng right t? 32 bit lên 48 bit
    bitset<48> expandedRight = expand(right, E, 48);
    // XOR v?i subkey
    expandedRight ^= subkey;

    // Chia 48 bit thành 8 nhóm 6 bit
    bitset<6> groups[8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            groups[i][j] = expandedRight[i * 6 + j];
        }
    }

    // Áp d?ng h?p S
    bitset<4> output[8];
    for (int i = 0; i < 8; i++) {
        int row = groups[i][0] * 2 + groups[i][5];
        int col = groups[i][1] * 8 + groups[i][2] * 4 + groups[i][3] * 2 + groups[i][4];
        int value = S[i][row][col];
        output[i] = bitset<4>(value);
    }

    // N?i các bitset 4 bit l?i thành m?t bitset 32 bit
    bitset<32> outputBitset;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            outputBitset[i * 4 + j] = output[i][j];
        }
    }

    // Áp d?ng hoán v? P
    const int P[32] = {
        16, 7, 20, 21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25
    };

    return permutation(outputBitset, P, 32);
}


bitset<64> encrypt(bitset<64> plaintext, bitset<48> subkeys[16]) {
    // IP table and IP-inverse table should be defined somewhere
    plaintext = permutation(plaintext, IP, 64);

    bitset<32> left, right;
    split(plaintext, left, right);

    for (int i = 0; i < 16; i++) {
        bitset<32> temp = right;
        right = left ^ f(right, subkeys[i]);
        left = temp;
    }

    bitset<64> preoutput = concatenate(right, left);
    return permutation(preoutput, IP_INV, 64);
}

void generateSubkeys(bitset<64> key, bitset<48>* subkeys) {
    // PC1, PC2 and shifts should be defined somewhere
    key = permutation(key, PC1, 56);

    bitset<28> left, right;
    split(key, left, right);

    for (int i = 0; i < 16; i++) {
        left = leftCircularShift(left, SHIFTS[i]);
        right = leftCircularShift(right, SHIFTS[i]);

        bitset<56> combined = concatenate(left, right);
        subkeys[i] = permutation(combined, PC2, 48);
    }
}

int main() {
    int choice;
    cout << "1. Ma hoa\n2. Giai ma\nChon lua chon: ";
    cin >> choice;

    bitset<64> key;
    cout << "Nhap vao key (64-bit): ";
    cin >> key;

    bitset<48> subkeys[16];
    generateSubkeys(key, subkeys);

    if (choice == 1) {
        // Mã hóa
        string plaintext;
        cout << "Nhap vao van ban can ma hoa: ";
        cin.ignore();
        getline(cin, plaintext);

        // Chuy?n d?i van b?n thành dãy bit
        bitset<64> bitstream;
        int bitsProcessed = 0;
        for (char c : plaintext) {
            for (int i = 7; i >= 0; i--) {
                bitstream[bitsProcessed] = (c >> i) & 1;
                bitsProcessed++;
                if (bitsProcessed == 64) {
                    // Ðã 64 bit, mã hóa kh?i này
                    bitset<64> ciphertext = encrypt(bitstream, subkeys);
                    cout << "Ket qua ma hoa: " << ciphertext.to_ullong() << endl;
                    bitstream.reset();
                    bitsProcessed = 0;
                }
            }
        }

        if (bitsProcessed > 0) {
            // Còn du bit, b? sung thêm bit 0 và mã hóa
            while (bitsProcessed < 64) {
                bitstream[bitsProcessed] = 0;
                bitsProcessed++;
            }
            bitset<64> ciphertext = encrypt(bitstream, subkeys);
            cout << "Ket qua ma hoa: " << ciphertext.to_ullong() << endl;
        }

    } else {
        // Gi?i mã
        bitset<64> ciphertext;
        cout << "Nhap vao ma hoa can giai ma: ";
        cin >> ciphertext;

        // Mã hóa kh?i 64 bit
        bitset<64> plaintext = encrypt(ciphertext, subkeys);

        // Chuy?n d?i dãy bit thành van b?n
        string output = "";
        int bitsProcessed = 0;
        char currentChar = 0;
        for (int i = 63; i >= 0; i--) {
            currentChar = (currentChar << 1) | plaintext[i];
            bitsProcessed++;
            if (bitsProcessed == 8) {
                output += currentChar;
                currentChar = 0;
                bitsProcessed = 0;
            }
        }

        cout << "Ket qua giai ma: " << output << endl;
    }

    return 0;
}


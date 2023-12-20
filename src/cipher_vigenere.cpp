//
// Created by ChaCha on 2023-12-20.
//

#include "cipher_vigenere.h"

vector<byte> cipher_vigenere::encypt(const vector<byte> &input) const {
    vector<byte> output(input.size());

    for (int i = 0; i < input.size(); i++) {
        short t = static_cast<int>(input[i]) + static_cast<int>(key[i % key.size()]) + 256;
        output[i] = static_cast<byte>(t);
    }

    return output;
}

vector<byte> cipher_vigenere::dencypt(const vector<byte> &input) const {
    vector<byte> output(input.size());

    for (int i = 0; i < input.size(); i++) {
        short t = static_cast<int>(input[i]) - static_cast<int>(key[i % key.size()]) + 256;
        output[i] = static_cast<byte>(t);
    }
    return output;
}

string cipher_vigenere::get_name() const {
    return "cipher_vigenere";
}


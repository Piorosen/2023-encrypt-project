//
// Created by ChaCha on 2023-12-20.
//

#include "cipher_xor.h"

vector<byte> cipher_xor::encypt(const vector<byte> &input) const {
    vector<byte> output(input.size());

    for (int i = 0; i < input.size(); i++) {
        output[i] = (input[i] ^ key[i % key.size()]);
    }
    return output;
}

vector<byte> cipher_xor::dencypt(const vector<byte> &input) const {
    vector<byte> output(input.size());

    for (int i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
}

string cipher_xor::get_name() const {
    return "chiper_xor";
}

//
// Created by ChaCha on 2023-12-20.
//

#include "cipher_shift.h"

vector<byte> cipher_shift::encypt(const vector<byte> &input) const {
    vector<byte> output(input.size());

    for (int i = 0; i < input.size(); i++) {
        short t = (static_cast<int>(input[i]) + key + 256);
        output[i] = static_cast<byte>(t);
    }
    return output;
}

vector<byte> cipher_shift::dencypt(const vector<byte> &input) const {
    vector<byte> output(input.size());

    for (int i = 0; i < input.size(); i++) {
        short t = (static_cast<int>(input[i]) - key + 256);
        output[i] = static_cast<byte>(t);
    }
    return output;
}

string cipher_shift::get_name() const {
    return "cipher_shift";
}

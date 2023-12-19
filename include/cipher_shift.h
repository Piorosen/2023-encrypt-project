//
// Created by ChaCha on 2023-12-20.

#ifndef SUBSTITUTION_CIPHER_H
#define SUBSTITUTION_CIPHER_H

#include "cipher.h"

class cipher_shift : public cipher {
    int key;
public:
    cipher_shift(int key) : key(key){}
    vector<byte> encypt(const vector<byte> &input) const override;
    vector<byte> dencypt(const vector<byte> &input) const override;
    string get_name() const override;
};


#endif //SUBSTITUTION_CIPHER_H

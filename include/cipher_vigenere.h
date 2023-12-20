//
// Created by ChaCha on 2023-12-20.
//

#ifndef CIPHER_VIGENERE_H
#define CIPHER_VIGENERE_H

#include "cipher.h"

class cipher_vigenere : public cipher {
    vector<byte> key;

public:
    cipher_vigenere(const vector<byte>& key) : key(key){}
    vector<byte> encypt(const vector<byte> &input) const override;
    vector<byte> dencypt(const vector<byte> &input) const override;
    string get_name() const override;
};




#endif //CIPHER_VIGENERE_H

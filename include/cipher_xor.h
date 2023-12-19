//
// Created by ChaCha on 2023-12-20.
//

#ifndef XOR_H
#define XOR_H
#include <cipher.h>


class cipher_xor : public cipher {
private:
    vector<byte> key;
public:
    cipher_xor(const vector<byte>& key) : key(key) {}
    vector<byte> encypt(const vector<byte> &input) const override;
    vector<byte> dencypt(const vector<byte> &input) const override;
    string get_name() const override;
};




#endif //XOR_H

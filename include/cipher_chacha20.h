//
// Created by ChaCha on 2023-12-20.
//

#ifndef CHACHA20_H
#define CHACHA20_H
#include <cipher.h>
#include <cstdint>
#include <array>


class cipher_chacha20 : public cipher {
public:
    cipher_chacha20(array<byte, 32> key, array<byte, 8> nonce);

    vector<byte> encypt(const vector<byte> &input) const override;
    vector<byte> dencypt(const vector<byte> &input) const override;
    string get_name() const override;

private:
    array<byte, 32> key;
    array<byte, 8> nonce;
};



#endif //CHACHA20_H

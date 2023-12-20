//
// Created by ChaCha on 2023-12-20.
//

#ifndef CIPHER_BASE64_H
#define CIPHER_BASE64_H

#include "cipher.h"

class cipher_base64 : public cipher {
private:
    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

public:
    cipher_base64() {}
    vector<byte> encypt(const vector<byte> &input) const override;
    vector<byte> dencypt(const vector<byte> &input) const override;
    string get_name() const override;
};



#endif //CIPHER_BASE64_H

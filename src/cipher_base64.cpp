//
// Created by ChaCha on 2023-12-20.
//

#include "cipher_base64.h"

#include <cstdint>

vector<byte> cipher_base64::encypt(const vector<byte> &input) const {
    std::vector<byte> result;
    uint32_t input_size = input.size();

    for (size_t i = 0; i < input_size; i += 3) {
        // Take the first byte and shift it to the left by 16 bits
        uint32_t combined = static_cast<uint32_t>(input[i]) << 16;
        // Take the second byte (if within bounds) and shift it to the left by 8 bits
        if (i + 1 < input_size) {
            combined += static_cast<uint32_t>(input[i + 1]) << 8;
        }
        // Take the third byte (if within bounds) and add it directly
        if (i + 2 < input_size) {
            combined += static_cast<uint32_t>(input[i + 2]);
        }

        for (int j = 0; j < 4; ++j) {
            if (i + j * 6 <= input_size * 8) {
                result.push_back((byte)base64_chars[(combined >> (18 - j * 6)) & 0x3F]);
            } else {
                result.push_back((byte)'=');
            }
        }
    }

    return result;
}

vector<byte> cipher_base64::dencypt(const vector<byte> &input) const {
    std::vector<byte> result;
    size_t input_size = input.size();

    for (size_t i = 0; i < input_size; i += 4) {
        uint32_t combined = 0;

        for (int j = 0; j < 4; ++j) {
            if (i + j < input_size) {
                size_t index = base64_chars.find((char)input[i + j]);
                if (index != std::string::npos) {
                    combined = (combined << 6) | index;
                }
            }
        }

        for (int j = 0; j < 3; ++j) {
            if (i + j < input_size - 1) {
                result.push_back((byte)((combined >> (16 - j * 8)) & 0xFF));
            }
        }
    }

    return result;
}

string cipher_base64::get_name() const {
    return "cipher_base64";
}


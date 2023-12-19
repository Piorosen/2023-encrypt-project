//
// Created by ChaCha on 2023-12-20.
//

#include "cipher_chacha20.h"

uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32 - n));
}
uint32_t pack4(const byte *a){
    return
        uint32_t(a[0] << 0*8) |
        uint32_t(a[1] << 1*8) |
        uint32_t(a[2] << 2*8) |
        uint32_t(a[3] << 3*8);
}
void unpack4(const uint32_t& src, byte *dst) {
    dst[0] = static_cast<byte>((src >> 0*8) & 0xff);
    dst[1] = static_cast<byte>((src >> 1*8) & 0xff);
    dst[2] = static_cast<byte>((src >> 2*8) & 0xff);
    dst[3] = static_cast<byte>((src >> 3*8) & 0xff);
}
void quarter_round(uint32_t* x, uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    x[a] += x[b]; x[d] = rotl32(x[d] ^ x[a], 16);
    x[c] += x[d]; x[b] = rotl32(x[b] ^ x[c], 12);
    x[a] += x[b]; x[d] = rotl32(x[d] ^ x[a], 8);
    x[c] += x[d]; x[b] = rotl32(x[b] ^ x[c], 7);
}

void next(array<byte, 64>& keystream8, array<uint32_t, 16>& state) {
    uint32_t temp32[16];

    // This is where the crazy voodoo magic happens.
    // Mix the bytes a lot and hope that nobody finds out how to undo it.
    for (int i = 0; i < 16; i++) temp32[i] = state[i];

    for (int i = 0; i < 10; i++){
        quarter_round(temp32, 0, 4, 8, 12);
        quarter_round(temp32, 1, 5, 9, 13);
        quarter_round(temp32, 2, 6, 10, 14);
        quarter_round(temp32, 3, 7, 11, 15);
        quarter_round(temp32, 0, 5, 10, 15);
        quarter_round(temp32, 1, 6, 11, 12);
        quarter_round(temp32, 2, 7, 8, 13);
        quarter_round(temp32, 3, 4, 9, 14);
    }

    for (int i = 0; i < 16; i++) temp32[i] += state[i];

    uint32_t *counter = &state[12];

    // increment counter
    counter[12]++;
    if (0 == counter[12]){
        // wrap around occured, increment higher 32 bits of counter
        counter[13]++;
        // Limited to 2^64 blocks of 64 bytes each.
        // If you want to process more than 1180591620717411303424 bytes
        // you have other problems.
        // We could keep counting with counter[2] and counter[3] (nonce),
        // but then we risk reusing the nonce which is very bad.
        // assert(0 != counter[1]);
    }

    for (size_t i = 0; i < 16; i++) {
        unpack4(temp32[i], keystream8.data() + i*4);
    }
}

array<uint32_t, 16> init(const array<byte, 32>& key, const array<byte, 8>& nonce) {
    array<uint32_t, 16> state;
    const int counter = 0;
    const byte *magic_constant = (byte*)"expand 32-byte k";
    state[ 0] = pack4(magic_constant + 0*4);
    state[ 1] = pack4(magic_constant + 1*4);
    state[ 2] = pack4(magic_constant + 2*4);
    state[ 3] = pack4(magic_constant + 3*4);
    state[ 4] = pack4(key.data() + 0*4);
    state[ 5] = pack4(key.data() + 1*4);
    state[ 6] = pack4(key.data() + 2*4);
    state[ 7] = pack4(key.data() + 3*4);
    state[ 8] = pack4(key.data() + 4*4);
    state[ 9] = pack4(key.data() + 5*4);
    state[10] = pack4(key.data() + 6*4);
    state[11] = pack4(key.data() + 7*4);
    // 64 bit counter initialized to zero by default.

    // Want to process many blocks in parallel?
    // No problem! Just set the counter to the block you want to process.
    state[12] = static_cast<uint32_t>(counter);
    state[13] = state[12] >> 32;

    state[14] = pack4(nonce.data() + 0*4);
    state[15] = pack4(nonce.data() + 1*4);

    return state;
}

cipher_chacha20::cipher_chacha20(array<byte, 32> key, array<byte, 8> nonce)  : key(key), nonce(nonce) {}

vector<byte> cipher_chacha20::encypt(const vector<byte> &input) const {
    array<byte, 64> keystream8;
    auto state = init(this->key, this->nonce);

    vector<byte> output(input.size());
    int position = 64;

    for (size_t i = 0; i < input.size(); i++){
        if (position >= 64){
            next(keystream8, state);
            position = 0;
        }
        output[i] = input[i] ^ keystream8[position];
        position++;
    }
    return output;
}

vector<byte> cipher_chacha20::dencypt(const vector<byte> &input) const {
    return encypt(input);
}

string cipher_chacha20::get_name() const {
    return "cipher_chacha20";
}


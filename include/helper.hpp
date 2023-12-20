//
// Created by ChaCha on 2023-12-20.
//

#ifndef HELPER_HPP
#define HELPER_HPP

#include <cipher.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "cipher_base64.h"
#include "cipher_chacha20.h"
#include "cipher_shift.h"
#include "cipher_xor.h"
#include "cipher_vigenere.h"

using namespace std;

// 파일을 읽어서 vector<byte>로 반환하는 함수
vector<byte> read(const string& filePath) {
    // 파일을 바이너리 모드로 읽기 위해 ifstream 사용
    ifstream file(filePath, ios::binary);

    // 파일 크기 구하기
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // vector<byte>를 파일 크기에 맞게 초기화
    vector<byte> buffer(fileSize);

    // 파일 내용을 vector<byte>로 읽기
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    // 파일 읽기 실패 여부 확인
    if (file.fail()) {
        cerr << "Error: Failed to read the file." << endl;
        return {};
    }

    // 파일 닫기
    file.close();

    return buffer;
}

void save(const vector<byte>& data, const string& file_path) {
    auto file = ofstream(file_path, ios::out | ios::binary);
    file.write((const char*)data.data(), data.size());
    file.close();
}

inline auto convert(const string& key) {
    vector<byte> output(key.size());
    for (int i = 0; i < key.size(); i++) {
        output[i] = static_cast<byte>(key[i]);
    }
    return output;
}

template<int size>
inline std::array<byte, size> convert(const string& key) {
    std::array<byte, size> output;
    int min = std::min((int)key.size(), size);
    for (int i = 0; i < min; i++) {
        output[i] = static_cast<byte>(key[i]);
    }
    return output;
}

vector<shared_ptr<cipher>> init() {
    // init code
    vector<shared_ptr<cipher>> ciphers;

    ciphers.push_back(make_shared<cipher_vigenere>(convert("4t4389eyuisdh87yuiao899&AIUSYGDASD")));
    ciphers.push_back(make_shared<cipher_chacha20>(convert<32>("01234567890123456789012345678901"), convert<8>("01234567")));
    ciphers.push_back(make_shared<cipher_xor>(convert("hello world!")));
    ciphers.push_back(make_shared<cipher_xor>(convert("my name is chacha")));
    ciphers.push_back(make_shared<cipher_xor>(convert("한국어로 진행할 수 있습니다.")));
    ciphers.push_back(make_shared<cipher_shift>(2));
    ciphers.push_back(make_shared<cipher_shift>(7));
    ciphers.push_back(make_shared<cipher_shift>(11));
    ciphers.push_back(make_shared<cipher_shift>(29));
    ciphers.push_back(make_shared<cipher_shift>(99));
    ciphers.push_back(make_shared<cipher_shift>(200));
    ciphers.push_back(make_shared<cipher_shift>(64));
    ciphers.push_back(make_shared<cipher_xor>(convert("nice to meet you.")));
    ciphers.push_back(make_shared<cipher_chacha20>(convert<32>("01234567890123456789012345678901"), convert<8>("01234567")));
    ciphers.push_back(make_shared<cipher_vigenere>(convert("4t4389eyuisdh87yuiao899&AIUSYGDASD")));
    ciphers.push_back(make_shared<cipher_base64>());
    return ciphers;
}

#endif //HELPER_HPP

cmake_minimum_required(VERSION 3.27)
project(2023_encrypt_project)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(2023_encrypt_project
        main.cpp
        src/cipher_xor.cpp
        src/cipher_shift.cpp
        src/cipher_chacha20.cpp)

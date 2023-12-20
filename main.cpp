#include <iostream>
#include <filesystem>

#include "helper.hpp"


using namespace std;


int main(int argc, char** argv) {
    std::cout << "help for you. : \nex) 2023_encrypt_project ./input.txt ./output.txt\n";
    std::cout << "current path : " << std::filesystem::current_path() << "\n";

    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << "\n";
    }

    const string path = argv[1];
    const string save_path = argv[2];

    auto input = read(argv[1]);
    std::cout << "read to successfully. [" << input.size() << "]\n";
    const auto ciphers = init();

    std::cout << "--- Origin --- \n";
    for (const auto& data : input) {
        std::cout << (char)data;
    }
    std::cout << "\n";
    
    for (int i = 0; i < ciphers.size(); i++) {
        input = ciphers[i]->encypt(input);
        // save(input, history_path + to_string(i) + "_enc_" + ciphers[i]->get_name() + ".txt");
    }
    save(input, save_path);
    std::cout << "--- Encrypt --- \n";
    for (const auto& data : input) {
        std::cout << (char)data;
    }
    std::cout << "\n";
    for (int i = ciphers.size() - 1; i >= 0; i--) {
        input = ciphers[i]->dencypt(input);
        // save(input, history_path + to_string(i) + "_dec_" + ciphers[i]->get_name() + ".txt");
    }
    std::cout << "--- Decrypt --- \n";
    for (const auto& data : input) {
        std::cout << (char)data;
    }
    std::cout << "\n";
    std::cout << "--- ---\nfinish\n";


    return 0;
}

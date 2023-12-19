#include <iostream>
#include <filesystem>

#include "helper.hpp"


using namespace std;


int main(int argc, char** argv) {
    std::cout << "aa : " << std::filesystem::current_path() << "\n";

    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << "\n";
    }

    const string path = argv[1];
    const string history_path = argv[2];

    auto input = read(argv[1]);
    std::cout << "read to successfully. [" << input.size() << "]\n";
    const auto ciphers = init();

    for (int i = 0; i < ciphers.size(); i++) {
        input = ciphers[i]->encypt(input);
        save(input, history_path + to_string(i) + "_enc_" + ciphers[i]->get_name() + ".txt");
    }

    for (int i = ciphers.size() - 1; i >= 0; i--) {
        input = ciphers[i]->dencypt(input);
        save(input, history_path + to_string(i) + "_dec_" + ciphers[i]->get_name() + ".txt");
    }

    return 0;
}

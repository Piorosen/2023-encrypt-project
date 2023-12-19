//
// Created by ChaCha on 2023-12-20.
//

#ifndef CHIPER_H
#define CHIPER_H
#include <vector>
#include <string>

using namespace std;

class cipher {
public:
	virtual vector<byte> encypt(const vector<byte>& input) const = 0;
	virtual vector<byte> dencypt(const vector<byte>& input) const = 0;
	virtual string get_name() const = 0;
};

#endif //CHIPER_H

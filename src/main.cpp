#include <fstream>
#include <cstdio>
#include "matrix.h"


class regster_id {
public:
    std::size_t val;
    operator std::size_t() const {
        return val;
    }
};

std::istream& operator >> (std::istream& is, regster_id& reg) {
    char reg_sign;
    is >> reg_sign >> reg.val;
    return is;
}

int main() {
    Matrix matrixes[10];
    std::string command;
    std::cin >> command;
    while (command != "exit") {
        try {
            if (command == "load") {
                regster_id reg;
                std::string filename;
                std::cin >> reg >> filename;
                std::ifstream is(filename);
                std::size_t height, width;
                is >> height >> width;
                Matrix tmp(height, width);
                is >> tmp;
                matrixes[reg] = tmp;
            }
            if (command == "print") {
                regster_id reg;
                std::cin >> reg;
                std::cout << matrixes[reg];
            }
            if (command == "add") {
                regster_id reg1;
                regster_id reg2;
                std::cin >> reg1 >> reg2;
                matrixes[reg1] += matrixes[reg2];
            }
            if (command == "mul") {
                regster_id reg1;
                regster_id reg2;
                std::cin >> reg1 >> reg2;
                matrixes[reg1] *= matrixes[reg2];
            }
            if (command == "elem") {
                regster_id reg;
                std::size_t row_index;
                std::size_t col_index;
                std::cin >> reg >> row_index >> col_index;
                std::cout << matrixes[reg][row_index][col_index] << std::endl;
            }
        }
        catch (const MatrixException& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cin >> command;
    }
    return 0;
}
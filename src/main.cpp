#include <fstream>
#include "matrix.h"

int main() {
    Matrix matrixes[10];
    while (1) {
        std::string command;
        std::cin >> command;
        char reg_sign;
        if (command == "load") {
            std::size_t reg;
            std::string filename;
            std::cin >> reg_sign >> reg >> filename;
            std::filebuf fb;
            if (fb.open(filename, std::ios::in))
            {
                std::istream is(&fb);
                size_t height, width;
                is >> height >> width;
                Matrix tmp(height, width);
                is >> tmp;
                matrixes[reg] = tmp;
                fb.close();
            }
        }
        if (command == "print") {
            std::size_t reg;
            std::cin >> reg_sign >> reg;
            std::cout << matrixes[reg];
        }
        if (command == "add") {
            std::size_t reg1;
            std::size_t reg2;
            std::cin >> reg_sign >> reg1 >> reg_sign >> reg2;
            try{
                matrixes[reg1] += matrixes[reg2];
            }
            catch(const MatrixException& e) {
                std::cerr << e.what() << std::endl;
            }
        }
        if (command == "mul") {
            std::size_t reg1;
            std::size_t reg2;
            std::cin >> reg_sign >> reg1 >> reg_sign >> reg2;
            try {
                matrixes[reg1] *= matrixes[reg2];
            }
            catch (const MatrixException& e) {
                std::cerr << e.what() << std::endl;
            }
        }
        if (command == "elem") {
            std::size_t reg;
            std::size_t row_index;
            std::size_t col_index;
            std::cin >> reg_sign >> reg >> row_index >> col_index;
            try {
                std::cout << matrixes[reg][row_index][col_index] << std::endl;
            }
            catch (const MatrixException& e) {
                std::cerr << e.what() << std::endl;
            }
        }
        if (command == "exit") {
            exit(0);
        }
    }
    return 0;
}
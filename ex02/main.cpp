#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << RED << "Invalid argument count. Please try again!" << std::endl << RESET;
        return (1);
    }
    PmergeMe instance(argc, argv);
}


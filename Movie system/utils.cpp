#include "utils.h"
#include <iostream>
#include <limits>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getValidInput(int maxOption) {
    int choice;
    while (true) {
        std::cout << "Enter your choice (1-" << maxOption << "): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > maxOption) {
            std::cout << "Invalid input. Please try again.\n";
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return choice;
        }
    }
}

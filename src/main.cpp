/*
    Small attempt to write an A* implementation in C++
*/

#include <iostream>
#include <string>
#include <vector>
#include "NodeHeap.h"

int main() {

    size_t numberOfRows  = 6;
    size_t numberofColumns = 10;

    std::string world[6][10] = {
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
        {"|", " ", "|", " ", "|", " ", " ", " ", " ", "|"},
        {"|", " ", "|", " ", " ", " ", " ", " ", " ", "|"},
        {"|", " ", " ", " ", " ", " ", " ", "|", " ", "|"},
        {"|", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}
    };

    for (size_t x = 0; x < numberOfRows; x++) {
        auto& row = world[x];
        for (size_t y = 0; y < numberofColumns; y++) {
            std::cout << row[y] + " ";
        }
        std::cout << std::endl;
    }

    NodeHeap heap;

    addElement(heap, &world[1][1], 4);

    return 0;
}
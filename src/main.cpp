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

    addElement(heap, &world[1][1], 4, 1, 1);
    addElement(heap, &world[2][1], 2, 2, 1);
    addElement(heap, &world[1][3], 2, 1, 3);

    NodeData node = pop(heap);

    world[std::get<0>(node.coordinates)][std::get<1>(node.coordinates)] = "*";

    for (size_t x = 0; x < numberOfRows; x++) {
        auto& row = world[x];
        for (size_t y = 0; y < numberofColumns; y++) {
            std::cout << row[y] + " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
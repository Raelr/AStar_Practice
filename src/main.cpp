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

    int** indices = new int* [numberOfRows];
    for (size_t i = 0; i < numberOfRows; i++) {
        indices[i] = new int[numberofColumns];
    }

    for (size_t x = 0; x < numberOfRows; x++) {
        auto& row = world[x];
        for (size_t y = 0; y < numberofColumns; y++) {
            indices[x][y] = -1;
            std::cout << row[y] + " ";
        }
        std::cout << std::endl;
    }

    NodeHeap heap;
    heap.indices = indices;

    addElement(heap, 2, 1, 1);

    addElement(heap, 1, 1, 2);

    addElement(heap, 3, 2, 1);

    // ------------------------------------------------------
    // ------------------- ALGORITHM ------------------------
    // ------------------------------------------------------

    /*
        1. Define start and end points. 
        2. Add the start node to the heap. 
        3. Start the loop -> check if the current node is equal to the end node.
            a. If current node == end node, then break. 
            b. Else continue.
        4. Get current node from top of heap.  
        5. Get it's neighbours. 
        6. Calculate their fcosts. 
        7. Add them to the heap. 
        8. Register current node as their parent. 
        9. Keep going with the loop. 
    */

    return 0;
}
/*
    Small attempt to write an A* implementation in C++
    This implementation is going to TRY and use a procedural approach (avoid classes and use 
    structs + functions). 

    We'll be trying to use arrays for the most part and may try to remove all dependencies on
    STL types such as Vectors. Why? Because why not!
*/

#include <iostream>
#include <string>
#include "NodeHeap.h"

const int MAX_COLUMNS = 10;

void printWorld(std::string world[][MAX_COLUMNS], int rows, int columns) {
    for (size_t x = 0; x < rows; x++) {
        auto& row = world[x];
        for (size_t y = 0; y < columns; y++) {
            std::cout << row[y] + " ";
        }
        std::cout << std::endl;
    }
}

int main() {

    // Define the number of rows and columns. 
    size_t numberOfRows  = 6;
    size_t numberofColumns = 10;

    // Keep in mind the world coordinates start on the top left. 
    std::string world[6][10] = {
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
        {"|", " ", "|", " ", "|", " ", " ", " ", " ", "|"},
        {"|", " ", "|", " ", " ", " ", " ", " ", " ", "|"},
        {"|", " ", " ", " ", " ", " ", " ", "|", " ", "|"},
        {"|", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}
    };

    NodeHeap::NodeHeap heap = NodeHeap::init(numberOfRows, numberofColumns);
    printWorld(world, numberOfRows, numberofColumns);

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
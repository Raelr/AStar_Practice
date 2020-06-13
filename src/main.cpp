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
#include <cmath>

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

size_t get_single_coord(int x, int y) {
    return (x * 10) + y;
}

int main() {

    // Define the number of rows and columns. 
    const size_t numberOfRows  = 6;
    const size_t numberOfColumns = 10;
    const size_t numDirections = 4;

    NodeHeap::NodeHeap heap = NodeHeap::init(numberOfRows, numberOfColumns);
    
    // Keep in mind the world coordinates start on the top left. 
    std::string world[numberOfRows][numberOfColumns] = {
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
        {"|", " ", "|", " ", "|", " ", " ", " ", " ", "|"},
        {"|", " ", "|", " ", " ", " ", " ", " ", " ", "|"},
        {"|", " ", " ", " ", " ", " ", " ", "|", " ", "|"},
        {"|", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}
    };

    printWorld(world, numberOfRows, numberOfColumns);

    bool closedSet[numberOfRows * numberOfColumns] = {false};

    NodeHeap::Coordinates parents[numberOfRows][numberOfColumns];
    
    NodeHeap::Coordinates goal = NodeHeap::createCoordinates(4,8);
    NodeHeap::Coordinates start = NodeHeap::createCoordinates(1,1);
    world[start.x][start.y] = "S";
    world[goal.x][goal.y] = "E";
    
    NodeHeap::Coordinates directions[4] = {
        NodeHeap::createCoordinates(-1, 0), NodeHeap::createCoordinates(1, 0),
        NodeHeap::createCoordinates(0, -1), NodeHeap::createCoordinates(0, 1)};

    NodeHeap::addElement(heap, 0, start);

    NodeHeap::Coordinates currentCoord = NodeHeap::createCoordinates(0, 0);
    currentCoord = NodeHeap::removeFirst(heap);

    while (currentCoord != goal) {
        for (size_t i = 0; i < numDirections; i++) {
            int coord_x = currentCoord.x + directions[i].x;
            int coord_y = currentCoord.y + directions[i].y;

            if ((coord_x >= 0 || coord_x < numberOfColumns) 
                && (coord_y >= 0 || coord_y < numberOfRows)) {
                
                NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);
                
                if ((world[coord_x][coord_y].find('|') == std::string::npos 
                    && world[coord_x][coord_y].find('-') == std::string::npos)
                    && !NodeHeap::contains(heap, coord_x, coord_y)
                    && !closedSet[get_single_coord(coord_x, coord_y)]) {
                    
                    int gCost = 1; 
                    int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                    int fCost = gCost * hCost;

                    parents[coord_x][coord_y] = std::move(currentCoord);
                    NodeHeap::addElement(heap, fCost, coord);
                }
            }
        }

        closedSet[get_single_coord(currentCoord.x, currentCoord.y)] = true;

        currentCoord = NodeHeap::removeFirst(heap);
    }

    currentCoord = parents[goal.x][goal.y];

    while (currentCoord != start) {
        world[currentCoord.x][currentCoord.y] = "x";
        currentCoord = parents[currentCoord.x][currentCoord.y];
    }

    printWorld(world, numberOfRows, numberOfColumns);

    return 0;
}
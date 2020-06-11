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

bool contains(NodeHeap::Coordinates* coords, NodeHeap::Coordinates coord, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (coords[i] == coord) {
            return true;
        }
    }
    return false;
}

int main() {

    // Define the number of rows and columns. 
    size_t numberOfRows  = 6;
    size_t numberOfColumns = 10;

    // Keep in mind the world coordinates start on the top left. 
    std::string world[6][10] = {
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
        {"|", " ", "|", " ", "|", " ", " ", " ", " ", "|"},
        {"|", " ", "|", " ", " ", " ", " ", " ", " ", "|"},
        {"|", " ", " ", " ", " ", " ", " ", "|", " ", "|"},
        {"|", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}
    };

    NodeHeap::NodeHeap heap = NodeHeap::init(numberOfRows, numberOfColumns);

    world[1][1] = "S";
    world[4][8] = "E";

    printWorld(world, numberOfRows, numberOfColumns);

    NodeHeap::Coordinates closedSet[numberOfRows * numberOfColumns];
    size_t nodes_visited = 0;

    NodeHeap::Coordinates goal = NodeHeap::createCoordinates(4,8);

    NodeHeap::addElement(heap, 0, 1, 1);

    size_t numDirections = 4;

    NodeHeap::Coordinates directions[4] = {
        NodeHeap::createCoordinates(-1, 0), NodeHeap::createCoordinates(1, 0),
        NodeHeap::createCoordinates(0, -1), NodeHeap::createCoordinates(0, 1)};

    NodeHeap::Coordinates currentCoord = NodeHeap::createCoordinates(0, 0);

    // while (currentCoord.x != goal.x || currentCoord.y != goal.y) {
        
    //     currentCoord = NodeHeap::removeFirst(heap);

    //     std::cout << currentCoord.x << ", " << currentCoord.y << std::endl;

    //     for (size_t i = 0; i < numDirections; i++) {
    //         int coord_x = currentCoord.x + directions[i].x;
    //         int coord_y = currentCoord.y + directions[i].y;

    //         if ((coord_x >= 0 || coord_x < numberOfColumns) 
    //             && (coord_y >= 0 || coord_y < numberOfRows)) {
                
    //             if (world[coord_x][coord_y] != "|" || world[coord_x][coord_y] != "-") {
    //                 int gCost = 1; 
    //                 int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
    //                 int fCost = gCost * hCost;
    //                 NodeHeap::addElement(heap, fCost, coord_x, coord_y);
    //             }
    //         }
    //     }
    //     std::cout << "Current coordinate: " << currentCoord.x << ", " << currentCoord.y << std::endl;
    //     world[currentCoord.x][currentCoord.y] = "x";
    //     currentCoord = NodeHeap::removeFirst(heap);
    // }

    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    closedSet[nodes_visited] = currentCoord;
    nodes_visited++;
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);

            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {

            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {

            std::cout << (world[coord_x][coord_y].find('|') == std::string::npos && world[coord_x][coord_y].find('-') == std::string::npos) << std::endl;
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {

            std::cout << (world[coord_x][coord_y].find('|') == std::string::npos && world[coord_x][coord_y].find('-') == std::string::npos) << std::endl;
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {

            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);

            std::cout << (world[coord_x][coord_y].find('|') == std::string::npos && world[coord_x][coord_y].find('-') == std::string::npos) << std::endl;
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)
                && !contains(closedSet, coord, nodes_visited)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    closedSet[nodes_visited] = currentCoord;
    nodes_visited++;
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);

            std::cout << (world[coord_x][coord_y].find('|') == std::string::npos && world[coord_x][coord_y].find('-') == std::string::npos) << std::endl;
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)
                && !contains(closedSet, coord, nodes_visited)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    closedSet[nodes_visited] = currentCoord;
    nodes_visited++;
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {
            
            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);

            std::cout << (world[coord_x][coord_y].find('|') == std::string::npos && world[coord_x][coord_y].find('-') == std::string::npos) << std::endl;
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)
                && !contains(closedSet, coord, nodes_visited)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    closedSet[nodes_visited] = currentCoord;
    nodes_visited++;
    currentCoord = NodeHeap::removeFirst(heap);

    for (size_t i = 0; i < numDirections; i++) {
        int coord_x = currentCoord.x + directions[i].x;
        int coord_y = currentCoord.y + directions[i].y;

        if ((coord_x >= 0 || coord_x < numberOfColumns) 
            && (coord_y >= 0 || coord_y < numberOfRows)) {

            NodeHeap::Coordinates coord = NodeHeap::createCoordinates(coord_x, coord_y);

            std::cout << (world[coord_x][coord_y].find('|') == std::string::npos && world[coord_x][coord_y].find('-') == std::string::npos) << std::endl;
            
            if ((world[coord_x][coord_y].find('|') == std::string::npos 
                && world[coord_x][coord_y].find('-') == std::string::npos)
                && !NodeHeap::contains(heap, coord_x, coord_y)
                && !contains(closedSet, coord, nodes_visited)) {
                int gCost = 1; 
                int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                int fCost = gCost * hCost;
                NodeHeap::addElement(heap, fCost, coord_x, coord_y);
            }
        }
    }

    world[currentCoord.x][currentCoord.y] = "x";
    closedSet[nodes_visited] = currentCoord;
    nodes_visited++;
    currentCoord = NodeHeap::removeFirst(heap);

    printWorld(world, numberOfRows, numberOfColumns);

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
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

// Constrains the world to only allowing 10 columns (at least for now)
const int MAX_COLUMNS = 10;

// Simply prints the world out. 
void printWorld(std::string world[][MAX_COLUMNS], int rows, int columns) {
    for (size_t x = 0; x < rows; x++) {
        auto& row = world[x];
        for (size_t y = 0; y < columns; y++) {
            std::cout << row[y] + " ";
        }
        std::cout << std::endl;
    }
}

// This method returns the flattened index of a 2D array. 
size_t get_single_coord(int x, int y) {
    return (x * 10) + y;
}

int main() {

    // Define the number of rows and columns. 
    const size_t numberOfRows  = 6;
    const size_t numberOfColumns = 10;

    // Define the number of directions the agent can move in (currently limited to four). 
    const size_t numDirections = 4;

    // Initialise the nodeheap.
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

    // ----------------------- PREPARATION ----------------------------

    // Initialise the closed set (the vector storing all visited nodes)
    bool closedSet[numberOfRows * numberOfColumns] = {false};

    // Initialise the vector that stores all parent nodes.
    NodeHeap::Coordinates parents[numberOfRows * numberOfColumns];
    
    // Initialise the start and end nodes. 
    NodeHeap::Coordinates goal = NodeHeap::createCoordinates(4,8);
    NodeHeap::Coordinates start = NodeHeap::createCoordinates(1,1);
    // Set the nodes to Start and End symbols (S and E). 
    world[start.x][start.y] = "S";
    world[goal.x][goal.y] = "E";

    // Print the world so we can see it's starting state. 
    std::cout << "STARTING WORLD STATE:" << std::endl;
    printWorld(world, numberOfRows, numberOfColumns);
    
    // Define all the directions possible for the agent (for finding neighbours).
    NodeHeap::Coordinates directions[4] = {
        NodeHeap::createCoordinates(-1, 0), NodeHeap::createCoordinates(1, 0),
        NodeHeap::createCoordinates(0, -1), NodeHeap::createCoordinates(0, 1)};

    // Initialises the current coordinate to the start node. 
    NodeHeap::Coordinates currentCoord = start;

    // --------------------------- ALGORITHM ----------------------------------

    // Loop until we find the goal node.
    while (currentCoord != goal) {
        // Check each direction that we specified.
        for (size_t i = 0; i < numDirections; i++) {
            // Get the coordinate of the neighbour node. 
            int coord_x = currentCoord.x + directions[i].x;
            int coord_y = currentCoord.y + directions[i].y;
            // Make sure the node is within the world bounds.
            if ((coord_x >= 0 || coord_x < numberOfColumns) 
                && (coord_y >= 0 || coord_y < numberOfRows)) {
                // Make sure the node isn't blocked (would be more complex if this were in
                // an actual game)
                if ((world[coord_x][coord_y].find('|') == std::string::npos 
                    && world[coord_x][coord_y].find('-') == std::string::npos)
                    // Make sure the node doesn't already exist in the node heap.
                    && !NodeHeap::contains(heap, coord_x, coord_y)
                    // Make sure the node hasn't already been processed.
                    && !closedSet[get_single_coord(coord_x, coord_y)]) {
                    
                    // Calculate heuristic (using Manhatten Distance). 
                    int gCost = 1; 
                    int hCost = (abs(coord_x - goal.x)) + abs(coord_y - goal.y);
                    int fCost = gCost * hCost;
                    // Set the neighbour's parent to the current node.
                    parents[get_single_coord(coord_x, coord_y)] = std::move(currentCoord);
                    // Add the neighbour to the heap for processing.
                    NodeHeap::addElement(heap, fCost, NodeHeap::createCoordinates(coord_x, coord_y));
                }
            }
        }
        // Make sure we've set the current node as being processed.
        closedSet[get_single_coord(currentCoord.x, currentCoord.y)] = true;
        // Remove the next element of the heap.
        currentCoord = NodeHeap::removeFirst(heap);
        // Keep looping until we find the goal node.
    }

    // Once we've found the end node, set the current coordinate to the parent of the end node 
    // (we want the end node to remain untouched in this intance)
    currentCoord = parents[get_single_coord(goal.x, goal.y)];

    // Now, iterate backward from the goal node until we reach the start node. 
    while (currentCoord != start) {
        // Set the node to 'x' (to signify a movement in the path)
        world[currentCoord.x][currentCoord.y] = "x";
        // Set the current coordinate to the parent of currentCoord. 
        currentCoord = parents[get_single_coord(currentCoord.x, currentCoord.y)];
        // Keep iterating until we reach the start node.
    }

    // ---------------------------- END OF ALGORITHM ----------------------------

    // Finally, print the modified world (which should hopefully show the path)
    std::cout << "ENDING WORLD STATE:" << std::endl;
    printWorld(world, numberOfRows, numberOfColumns);

    return 0;
}
/*
    Small attempt to write an A* implementation in C++
*/

#include <iostream>
#include <string>

struct node {
    bool isObstacle;
    char symbol;
};

int main() {

    size_t numberOfRows = 6;
    size_t numberOfColumns = 10;

    std::string world[6][10] = {
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
        {"|", " ", "|", " ", "|", " ", " ", " ", " ", "|"},
        {"|", " ", "|", " ", "|", " ", " ", " ", " ", "|"},
        {"|", " ", " ", " ", "|", " ", " ", "|", " ", "|"},
        {"|", " ", " ", " ", " ", " ", " ", "|", " ", "|"},
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-"}
    };

    for (size_t x = 0; x < numberOfRows; x++) {
        auto& row = world[x];
        for (size_t y = 0; y < numberOfColumns; y++) {
            std::cout << row[y] + " ";
        }
        std::cout << std::endl;
    }

    std::pair start = std::pair(1, 1);
    std::pair end = std::pair(4, 8);



    return 0;
}
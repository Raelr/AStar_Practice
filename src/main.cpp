/*
    Small attempt to write an A* implementation in C++
*/

#include <iostream>
#include <string>
#include <vector>

int main() {

    size_t numberOfRows  = 6;
    size_t numberofColumns = 10;

    std::vector<std::tuple<int,int>> blocked;

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
            if (row[y] == "|" || row[y] == "-") { 
                blocked.emplace_back(std::make_tuple(x, y)); 
            }
            std::cout << row[y] + " ";
        }
        std::cout << std::endl;
    }

    /*  What do we need to make this work?
        1. Need a way to define f and g costs. 
        2. Need a way to define parents of nodes. 
        3. Need to know how to work our way back. 
    */

    return 0;
}
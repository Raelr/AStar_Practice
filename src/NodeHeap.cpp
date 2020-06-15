/*
    Implementation of the NodeHeap.h file.
*/

#include "NodeHeap.h"
#include "iostream"

namespace NodeHeap {
    // Adds an element to the heap - allocates an index to the element
    // and then sorts the element based on the inputted fcost. 
    void addElement(NodeHeap& heap,int fcost, Coordinates coordinate) {
        // Add the node to the end of the heap. 
        heap.fCosts.emplace_back(fcost);
        heap.coordinates.emplace_back(coordinate);
        heap.indices[coordinate.x][coordinate.y] = heap.coordinates.size() - 1;
        //std::cout << "Added new element to heap! Heap is now size: " << heap.fCosts.size() 
        //        << std::endl;
        // Sort the heap from the bottom. 
        sortUp(heap);
    }

    // Checks whether an index is valid for a collection. 
    // Pretty self explanatory.
    bool isInBounds(int index, int size) {
        return (index >= 0) && (index < size);
    }

    // Checks whether a node coordinate exists in the heap.
    // i.e: the index is not registered as -1.
    bool contains(const NodeHeap& heap,int x,int y) {
        // All indices registered as -1 indicate a missing index. 
        return heap.indices[x][y] != -1;
    }

    // Will sort the heap if any changes are made. 
    void updateHeap(NodeHeap& heap) {
        sortUp(heap);
    }

    // Sorts the heap from the bottom - i.e the latest element inputted. Generally called in the
    // addElement method. 
    void sortUp(NodeHeap& heap) {

        // Keep checking the parent and comparing the value with it. If the parent is larger than the
        // current element then swap their positions and indices. 
        
        int item_idx = heap.fCosts.size() - 1;
        //std::cout << "Start index: " << item_idx << std::endl;
        int parent_idx = (item_idx-1)/2;
        //std::cout << "Parent index: " << parent_idx << std::endl;

        while (true) {
            int item_cost = heap.fCosts[item_idx];
            int parent_cost = heap.fCosts[parent_idx];
            if (item_cost < parent_cost) {
                //std::cout << "The new item has a smaller fcost! Swapping values " << std::endl;

                // Swap the values. 
                std::iter_swap(heap.fCosts.begin() + item_idx, heap.fCosts.begin() + parent_idx);
                std::iter_swap(heap.coordinates.begin() + item_idx, heap.coordinates.begin() + parent_idx);

                // Swap the index values. 
                heap.indices[heap.coordinates[item_idx].x][heap.coordinates[item_idx].y] = item_idx;
                heap.indices[heap.coordinates[parent_idx].x][heap.coordinates[parent_idx].y] = parent_idx;

                item_idx = parent_idx;
            } else {
                // Break out of the loop if the value is larger than it's parent. 
                break;
            }

            // Update the parent index. 
            parent_idx = (parent_idx-1)/2;
        }
    }

    // Removes and returns the first element. The element is then replaced with the last element in 
    // the collection. The heap is then sorted again using the sortDown method. 
    Coordinates removeFirst(NodeHeap& heap) {
        Coordinates firstCoords = heap.coordinates.front();
        // Update the index of the first element to -1 since it no longer lives in the heap. 
        heap.indices[firstCoords.x][firstCoords.y] = -1;
        
        // Move the values at the back to the front and reduce the size of the array. 
        heap.coordinates.front() = std::move(heap.coordinates.back());
        heap.coordinates.pop_back();
        heap.fCosts.front() = std::move(heap.fCosts.back());
        heap.fCosts.pop_back();

        //std::cout << "First element used to be: " << firstCoords.x << ", " 
        //        << firstCoords.y << std::endl;

        //std::cout << "coords is now size: " << heap.coordinates.size() << std::endl;
        
        // Sort from the top (since the last element has been placed at the front of the heap).
        sortDown(heap);

        //std::cout << "First element is now: " << heap.coordinates.front().x << ", " 
        //        << heap.coordinates.front().y << std::endl;

        // return the first coordinates. 
        return firstCoords;
    }

    // Creates a Coordinates struct and returns it. 
    Coordinates createCoordinates(int x, int y) {
        Coordinates coordinate;
        coordinate.x = x;
        coordinate.y = y;
        return coordinate;
    }

    // Sorts the heap from the top - the element in position 0. 
    // Generally called in the removeFirst method. 
    void sortDown(NodeHeap& heap) {
        int element = heap.fCosts.front();
        int index = 0;
        while (true) {
            // Get the left and right children. 
            int childIndexLeft = (index * 2) + 1;
            int childIndexRight = (index * 2) + 2;
            int swapIndex = 0;

            // Check if the left child is in bounds. 
            if (isInBounds(childIndexLeft, heap.fCosts.size())) {
                swapIndex = childIndexLeft;
                // Check if the right child is in bounds. 
                if (isInBounds(childIndexRight, heap.fCosts.size())) {
                    // Check if the right child has higher priority to the left child. 
                    if (heap.fCosts[childIndexLeft] > heap.fCosts[childIndexRight]) {
                        swapIndex = childIndexRight;
                    }
                }
                // If the element has less priority than its child then swap the values. 
                if (element > heap.fCosts[swapIndex]) {
                    // Swap the values.
                    std::iter_swap(heap.fCosts.begin() + index, heap.fCosts.begin() + swapIndex);
                    std::iter_swap(heap.coordinates.begin() + index, heap.coordinates.begin() + swapIndex);
                    // Replace their indices.
                    heap.indices[heap.coordinates[swapIndex].x][heap.coordinates[swapIndex].y] = swapIndex;
                    heap.indices[heap.coordinates[index].x][heap.coordinates[index].y] = index;
                    // Update the index and keep going. 
                    index = swapIndex;
                } else {
                    return;
                }
            } else {
                return;
            }
        }
    }

    // Prints all the indices registered in the heap (for debugging purposes). 
    void printIndices(NodeHeap& heap, int rows, int columns) {
        for (size_t x = 0; x < rows; x++) {
            auto& row = heap.indices[x];
            for (size_t y = 0; y < columns; y++) {
                // Print the value of the index
                std::cout << row[y] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Creates a statically sized NodeHeap.
    NodeHeap init(int rows, int columns) {
        NodeHeap heap;
        int** indices = new int* [rows];
        // Allocate memory for the arrays within the index array, 
        for (size_t x = 0; x < rows; x++) {
            indices[x] = new int[columns];
            auto& row = indices[x];
            for (size_t y = 0; y < columns; y++) {
                indices[x][y] = -1;
            }
        }
        heap.indices = indices;
        return heap;
    }

    // Simple operators for comparisons.

    bool operator==(const Coordinates& coordA, const Coordinates& coordB) {
        return coordA.x == coordB.x && coordA.y == coordB.y;
    }

    bool operator!=(const Coordinates& coordA, const Coordinates& coordB) {
        return coordA.x != coordB.x || coordA.y != coordB.y;
    }
}


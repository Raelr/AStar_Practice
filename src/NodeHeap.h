/*
    This file defines the signature of the NodeHeap. 
    The NodeHeap is a highly specialised data structure which stores and sorts nodes by their
    fcost. 

    The NodeHeap keeps track of nodes via three collections:
    1.  fCosts collection - sorts and tracks all fCosts. This will be used to find the highest
        priority node. 
    2.  coordinates - Keeps track of the coordinates of the fCost nodes. Will be used to get 
        the lowest fCost node's coordinates.
    3.  indices - a 2D array which keeps track of the indices of every element in the heap. 
*/

#ifndef NODE_HEAP_H
#define NODE_HEAP_H

#include <vector>

namespace NodeHeap {

        // Stores the x and y values of specific coordinates.
    struct Coordinates {
        int x;
        int y;
    };

    // The NodeHeap struct - used to organise node fcosts. 
    struct NodeHeap {
        // List of fCosts - the collection used to calculate node priorities. 
        std::vector<int> fCosts;
        // List of coordinates - returned to algorithm and can be used to find indices. 
        std::vector<Coordinates> coordinates;
        // 2D array of indices - used to find a node's index. 
        int** indices;
    };

    // Adds an element to the heap - allocates an index to the element
    // and then sorts the element based on the inputted fcost. 
    void addElement(NodeHeap& heap, int fcost, Coordinates coordinate);

    // Sorts the heap from the bottom - i.e the latest element inputted. Generally called in the
    // addElement method. 
    void sortUp(NodeHeap& heap);

    // Sorts the heap from the top - the element in position 0. 
    // Generally called in the removeFirst method. 
    void sortDown(NodeHeap& heap);
    // Removes and returns the first element. The element is then replaced with the last element in 
    // the collection. The heap is then sorted again using the sortDown method. 
    Coordinates removeFirst(NodeHeap& heap);
    
    // Simply returns a coordinates struct
    Coordinates createCoordinates(int x, int y);
    
    // Checks whether an index is valid for a collection. 
    bool isInBounds(int index, int size);
    
    // Checks whether a node coordinate exists in the heap.
    // i.e: the index is not registered as 0.
    bool contains(const NodeHeap& heap, int x, int y);
    
    // Returns the size of the heap. 
    bool size(NodeHeap& heap);
    
    // Will sort the heap if any changes are made. 
    void updateHeap(NodeHeap& heap);
    
    // Prints all the indices registered in the heap (for debugging purposes). 
    void printIndices(NodeHeap& heap, int rows, int columns);
    
    // Initialises a NodeHeap struct and allocated memory for the indices array.
    NodeHeap init(int rows, int columns);

    bool operator==(const Coordinates&, const Coordinates&);

    bool operator!=(const Coordinates&, const Coordinates&);

    bool operator<(const Coordinates&, const Coordinates&);
}

#endif
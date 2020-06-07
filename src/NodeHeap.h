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

struct NodeHeap {
    std::vector<int> fCosts;
    std::vector<std::pair<int, int>> coordinates;
    int** indices;
};

void addElement(NodeHeap& heap, int fcost, int x, int y);

void sortUp(NodeHeap& heap);
void sortDown(NodeHeap& heap);

std::tuple<int, int> removeFirst(NodeHeap& heap);

bool isInBounds(int index, int size);
bool contains(const NodeHeap& heap, int x, int y);
bool size(NodeHeap& heap);

void updateHeap(NodeHeap& heap);
void printIndices(NodeHeap& heap, int rows, int columns);

#endif
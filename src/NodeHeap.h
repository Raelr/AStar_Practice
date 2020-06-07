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
bool contains(const NodeHeap& heap, int x, int y, int idx);
bool size(NodeHeap& heap);

void updateHeap(NodeHeap& heap);
void printIndices(NodeHeap& heap, int rows, int columns);

#endif
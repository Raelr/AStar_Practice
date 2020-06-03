#ifndef NODE_HEAP_H
#define NODE_HEAP_H

#include <vector>

struct NodeHeap {
    std::vector<int> elements;
    std::vector<std::pair<int, int>> coordinates;
};

void addElement(NodeHeap& heap, int fcost, int x, int y);

void sortUp(NodeHeap& heap);

std::tuple<int, int> removeFirst(NodeHeap& heap);

#endif
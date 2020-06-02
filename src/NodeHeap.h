#ifndef NODE_HEAP_H
#define NODE_HEAP_H

#include <vector>

struct NodeHeap {
    std::vector<std::tuple<std::string*, int>> elements;
};

void addElement(NodeHeap& heap, std::string* element, int fcost);

#endif
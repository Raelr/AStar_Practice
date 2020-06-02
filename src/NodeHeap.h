#ifndef NODE_HEAP_H
#define NODE_HEAP_H

#include <vector>

struct NodeHeap {
    std::vector<std::tuple<std::string*, int>> elements;
    std::vector<std::pair<int, int>> coordinates;
};

struct NodeData {
    std::tuple<int, int> coordinates;
    std::string* element;
};

void addElement(NodeHeap& heap, std::string* element, int fcost, int x, int y);

void sortUp(NodeHeap& heap);

NodeData pop(NodeHeap& heap);

#endif
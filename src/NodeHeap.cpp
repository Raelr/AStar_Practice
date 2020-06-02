#include "NodeHeap.h"

void addElement(NodeHeap& heap, std::string* element, int fcost) {
    auto tuple = std::make_tuple(element, fcost);
    heap.elements.emplace_back(tuple);
}
#include "NodeHeap.h"
#include "iostream"

void addElement(NodeHeap& heap, std::string* element, int fcost) {
    auto tuple = std::make_tuple(element, fcost);
    heap.elements.emplace_back(tuple);
    std::cout << "Added new element to heap! Heap is now size: " << heap.elements.size() << std::endl;
    sortUp(heap);
}

void sortUp(NodeHeap& heap) {
    int start_idx = heap.elements.size() - 1;
    std::cout << "Start index: " << start_idx << std::endl;
    int parent_idx = (start_idx-1)/2;
    std::cout << "Parent index: " << parent_idx << std::endl;
}
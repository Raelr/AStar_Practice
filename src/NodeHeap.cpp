#include "NodeHeap.h"
#include "iostream"

void addElement(NodeHeap& heap, std::string* element, int fcost, int x, int y) {
    heap.elements.emplace_back(std::make_tuple(element, fcost));
    heap.coordinates.emplace_back(std::pair<int, int>(x, y));
    std::cout << "Added new element to heap! Heap is now size: " << heap.elements.size() << std::endl;
    sortUp(heap);
}

void sortUp(NodeHeap& heap) {
    int start_idx = heap.elements.size() - 1;
    std::cout << "Start index: " << start_idx << std::endl;
    int parent_idx = (start_idx-1)/2;
    std::cout << "Parent index: " << parent_idx << std::endl;

    while (true) {
        int item_cost = std::get<1>(heap.elements[start_idx]);
        int parent_cost = std::get<1>(heap.elements[parent_idx]);
        if (item_cost < parent_cost) {
            std::cout << "The new item has a smaller fcost! Swapping values " << std::endl;
            std::iter_swap(heap.elements.begin() + start_idx, heap.elements.begin() + parent_idx);
            std::iter_swap(heap.coordinates.begin() + start_idx, heap.coordinates.begin() + parent_idx);
        } else {
            break;
        }

        parent_idx = (parent_idx-1)/2;
    }
}

NodeData pop(NodeHeap& heap) {
    NodeData data;
    data.coordinates = heap.coordinates[0];
    data.element = std::get<0>(heap.elements[0]);

    return data;
}
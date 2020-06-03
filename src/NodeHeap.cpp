#include "NodeHeap.h"
#include "iostream"

void addElement(NodeHeap& heap,int fcost, int x, int y) {
    heap.elements.emplace_back(fcost);
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
        int item_cost = heap.elements[start_idx];
        int parent_cost = heap.elements[parent_idx];
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

std::tuple<int, int> removeFirst(NodeHeap& heap) {
    std::tuple<int, int> firstCoords = heap.coordinates[0];
    heap.coordinates.front() = std::move(heap.coordinates.back());
    heap.coordinates.pop_back();

    std::cout << "First element used to be: " << std::get<0>(firstCoords) << ", " 
            << std::get<1>(firstCoords) << std::endl;

    std::cout << "coords is now size: " << heap.coordinates.size() << std::endl;

    std::cout << "First element is now: " << std::get<0>(heap.coordinates.front()) << ", " 
            << std::get<1>(heap.coordinates.front()) << std::endl;

    return firstCoords;
}
#include "NodeHeap.h"
#include "iostream"

void addElement(NodeHeap& heap,int fcost, int x, int y) {
    heap.fCosts.emplace_back(fcost);
    heap.coordinates.emplace_back(std::pair<int, int>(x, y));
    std::cout << "Added new element to heap! Heap is now size: " << heap.fCosts.size() 
            << std::endl;
    sortUp(heap);
}

bool isInBounds(int index, int size) {
    return (index >= 0) && (index < size);
}

bool contains(const NodeHeap& heap,int x,int y) {
    bool found = false;
    for (size_t i = 0; i < heap.coordinates.size(); i++) {
        if (x == std::get<0>(heap.coordinates[i]) && 
            y == std::get<1>(heap.coordinates[i])) {
            
            found = true;
            break;
        }        
    }
    return found;
}

void updateHeap(NodeHeap& heap) {
    sortUp(heap);
}

void sortUp(NodeHeap& heap) {
    int item_idx = heap.fCosts.size() - 1;
    std::cout << "Start index: " << item_idx << std::endl;
    int parent_idx = (item_idx-1)/2;
    std::cout << "Parent index: " << parent_idx << std::endl;

    while (true) {
        int item_cost = heap.fCosts[item_idx];
        int parent_cost = heap.fCosts[parent_idx];
        if (item_cost < parent_cost) {
            std::cout << "The new item has a smaller fcost! Swapping values " << std::endl;
            std::iter_swap(heap.fCosts.begin() + item_idx, heap.fCosts.begin() + parent_idx);
            std::iter_swap(heap.coordinates.begin() + item_idx, heap.coordinates.begin() + parent_idx);
            item_idx = parent_idx;
        } else {
            break;
        }

        parent_idx = (parent_idx-1)/2;
    }
}

std::tuple<int, int> removeFirst(NodeHeap& heap) {
    std::tuple<int, int> firstCoords = heap.coordinates.front();
    heap.coordinates.front() = std::move(heap.coordinates.back());
    heap.coordinates.pop_back();
    heap.fCosts.front() = std::move(heap.fCosts.back());
    heap.fCosts.pop_back();

    std::cout << "First element used to be: " << std::get<0>(firstCoords) << ", " 
            << std::get<1>(firstCoords) << std::endl;

    std::cout << "coords is now size: " << heap.coordinates.size() << std::endl;
    
    sortDown(heap);

    std::cout << "First element is now: " << std::get<0>(heap.coordinates.front()) << ", " 
            << std::get<1>(heap.coordinates.front()) << std::endl;

    return firstCoords;
}

void sortDown(NodeHeap& heap) {
    auto element = heap.fCosts.front();
    int index = 0;
    while (true) {
        int childIndexLeft = (index * 2) + 1;
        int childIndexRight = (index * 2) + 2;
        int swapIndex = 0;

        if (isInBounds(childIndexLeft, heap.fCosts.size())) {
            swapIndex = childIndexLeft;

            if (isInBounds(childIndexRight, heap.fCosts.size())) {
                if (heap.fCosts[childIndexLeft] > heap.fCosts[childIndexRight]) {
                    swapIndex = childIndexRight;
                }
            }
            if (element > heap.fCosts[swapIndex]) {
                std::iter_swap(heap.fCosts.begin() + index, heap.fCosts.begin() + swapIndex);
                std::iter_swap(heap.coordinates.begin() + index, heap.coordinates.begin() + swapIndex);
                index = swapIndex;
            } else {
                return;
            }
        } else {
            return;
        }
    }
}
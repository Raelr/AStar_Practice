#include "NodeHeap.h"
#include "iostream"

void addElement(NodeHeap& heap,int fcost, int x, int y) {
    heap.fCosts.emplace_back(fcost);
    heap.coordinates.emplace_back(std::pair<int, int>(x, y));
    heap.indices[x][y] = heap.coordinates.size() - 1;
    std::cout << "Added new element to heap! Heap is now size: " << heap.fCosts.size() 
            << std::endl;
    sortUp(heap);
}

bool isInBounds(int index, int size) {
    return (index >= 0) && (index < size);
}

bool contains(const NodeHeap& heap,int x,int y, int idx) {
    
    bool found = false;

    if (idx != -1 && (idx >= 0 && idx < heap.fCosts.size())) {
        if (std::get<0>(heap.coordinates[idx]) == x &&
            std::get<1>(heap.coordinates[idx]) == y) {
                found = true;
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

            heap.indices[std::get<0>(heap.coordinates[item_idx])][std::get<1>(heap.coordinates[item_idx])] = item_idx;
            heap.indices[std::get<0>(heap.coordinates[parent_idx])][std::get<1>(heap.coordinates[parent_idx])] = parent_idx;

            item_idx = parent_idx;
        } else {
            break;
        }

        parent_idx = (parent_idx-1)/2;
    }
}

std::tuple<int, int> removeFirst(NodeHeap& heap) {
    std::tuple<int, int> firstCoords = heap.coordinates.front();

    heap.indices[std::get<0>(firstCoords)][std::get<1>(firstCoords)] = -1;
    
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

                heap.indices[std::get<0>(heap.coordinates[swapIndex])][std::get<1>(heap.coordinates[swapIndex])] = swapIndex;
                heap.indices[std::get<0>(heap.coordinates[index])][std::get<1>(heap.coordinates[index])] = index;

                index = swapIndex;
            } else {
                return;
            }
        } else {
            return;
        }
    }
}

void printIndices(NodeHeap& heap, int rows, int columns) {
    for (size_t x = 0; x < rows; x++) {
        auto& row = heap.indices[x];
        for (size_t y = 0; y < columns; y++) {
            std::cout << row[y] << " ";
        }
        std::cout << std::endl;
    }
}
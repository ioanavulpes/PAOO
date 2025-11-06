#include "Wardrobe.hpp"
#include <iostream>
using namespace std;

Wardrobe::Wardrobe(size_t initialCapacity)
    : items(new ClothingItem[initialCapacity]), size(0), capacity(initialCapacity)
{
    cout << "[Wardrobe ctor] Capacity = " << capacity << "\n";
}

Wardrobe::~Wardrobe() {
    cout << "[Wardrobe dtor] Releasing memory\n";
    delete[] items;
}

Wardrobe::Wardrobe(const Wardrobe& other)
    : items(new ClothingItem[other.capacity]), size(other.size), capacity(other.capacity)
{
    cout << "[Wardrobe copy ctor] Deep copy " << size << " items\n";
    for (size_t i = 0; i < size; ++i)
        items[i] = other.items[i];
}

Wardrobe::Wardrobe(Wardrobe&& other) 
    : items(other.items), size(other.size), capacity(other.capacity)
{
    cout << "[Wardrobe move ctor] Take ownership\n";
    other.items = nullptr;
    other.size = 0;
    other.capacity = 0;
}

void Wardrobe::add(const ClothingItem& item) {
    if (size == capacity) {
        cout << "[Wardrobe] Resizing from " << capacity << " to " << capacity * 2 << "\n";
        ClothingItem* newItems = new ClothingItem[capacity * 2];
        for (size_t i = 0; i < size; ++i)
            newItems[i] = items[i];
        delete[] items;
        items = newItems;
        capacity *= 2;
    }
    items[size++] = item; 
}

void Wardrobe::print() const {
    cout << "Wardrobe (" << size << " items):\n";
    for (size_t i = 0; i < size; ++i) {
        cout << "  - ";
        items[i].print();
    }
}

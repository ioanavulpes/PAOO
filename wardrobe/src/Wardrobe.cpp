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


// Copy constructor (Item 12: Copy all parts of the object)

Wardrobe::Wardrobe(const Wardrobe& other)
    : items(new ClothingItem[other.capacity]),
      size(other.size),
      capacity(other.capacity)
{
    cout << "[Wardrobe copy ctor] Deep copy " << size << " items\n";
    for (size_t i = 0; i < size; ++i)
        items[i] = other.items[i];
}


// COPY ASSIGNMENT OPERATOR (Item 10, 11, 12)

Wardrobe& Wardrobe::operator=(const Wardrobe& other) {

    cout << "[Wardrobe copy=] Copy assignment\n";

    // Item 11 — self assignment check
    if (this == &other)
        return *this;

    // Item 12 — copy ALL parts of the object
    ClothingItem* newItems = new ClothingItem[other.capacity];
    for (size_t i = 0; i < other.size; ++i)
        newItems[i] = other.items[i];

    delete[] items;

    items = newItems;
    size = other.size;
    capacity = other.capacity;

    // Item 10 — return *this to allow chained assignment
    return *this;
}

// MOVE CONSTRUCTOR
Wardrobe::Wardrobe(Wardrobe&& other) noexcept
    : items(other.items),
      size(other.size),
      capacity(other.capacity)
{
    cout << "[Wardrobe move ctor] Take ownership\n";

    other.items = nullptr;
    other.size = 0;
    other.capacity = 0;
}

// MOVE ASSIGNMENT
Wardrobe& Wardrobe::operator=(Wardrobe&& other) noexcept {

    cout << "[Wardrobe move=] Move assignment\n";

    if (this == &other)
        return *this;

    delete[] items;

    items = other.items;
    size = other.size;
    capacity = other.capacity;

    other.items = nullptr;
    other.size = 0;
    other.capacity = 0;

    return *this;
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

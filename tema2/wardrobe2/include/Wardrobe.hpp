#pragma once
#include "ClothingItem.hpp"
#include <cstddef>

class Wardrobe {
public:
    Wardrobe(size_t initialCapacity = 2);

    // Rule of 5
    ~Wardrobe();
    Wardrobe(const Wardrobe& other);             // copy constructor
    Wardrobe& operator=(const Wardrobe& other);  // copy assignment (Item 10,11,12)

    Wardrobe(Wardrobe&& other) noexcept;         
    Wardrobe& operator=(Wardrobe&& other) noexcept; // move assignment

    void add(const ClothingItem& item);
    void print() const;

private:
    ClothingItem* items;
    size_t size;
    size_t capacity;
};

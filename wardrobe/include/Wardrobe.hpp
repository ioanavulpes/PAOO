#pragma once
#include "ClothingItem.hpp"
#include <cstddef>

class Wardrobe {
private:
    ClothingItem* items; 
    size_t size;
    size_t capacity;

public:
    Wardrobe(size_t initialCapacity = 2);
    ~Wardrobe();

   
    Wardrobe(const Wardrobe& other);     
    Wardrobe(Wardrobe&& other) noexcept;

    void add(const ClothingItem& item);
    void print() const;
};

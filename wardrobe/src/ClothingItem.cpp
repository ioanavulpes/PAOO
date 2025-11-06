#include "ClothingItem.hpp"
#include <iostream>

ClothingItem::ClothingItem(std::string n, std::string s, double p)
    : name(n), size(s), price(p) {}

std::string ClothingItem::getName() {
    return name; 
}

std::string ClothingItem::getSize() {
    return size;
}

double ClothingItem::getPrice() {
    return price; 
}

void ClothingItem::print() {
    std::cout << name << " (" << size << ") - " << price << " RON\n";
}

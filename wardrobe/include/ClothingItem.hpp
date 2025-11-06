#pragma once
#include <string>

class ClothingItem {
private:
    std::string name;
    std::string size;
    double price;

public:
    ClothingItem() = default;
    ClothingItem(std::string n, std::string s, double p);

    std::string getName();  
    std::string getSize();  
    double getPrice();      

    void print();
};

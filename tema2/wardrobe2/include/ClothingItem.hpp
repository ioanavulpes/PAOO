#pragma once
#include <string>

class ClothingItem {
private:
    std::string name;
    std::string size;
    double price;

public:
    ClothingItem(std::string n = "", std::string s = "", double p = 0.0);

    std::string getName();
    std::string getSize();
    double getPrice();

    void print();
};



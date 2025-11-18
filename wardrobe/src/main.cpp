#include "Wardrobe.hpp"
#include <iostream>
using namespace std;

Wardrobe makeWardrobe() {
    Wardrobe w;
    w.add(ClothingItem("Tricou", "M", 49.99));
    w.add(ClothingItem("Jeansi", "32", 159.99));
    return w; 
}

int main() {
    cout << " Construct normal \n";
    Wardrobe w1;
    w1.add(ClothingItem("Hanorac", "L", 189.99));
    w1.add(ClothingItem("Geaca", "M", 299.99));
    w1.print();

    cout << "\n Copy construct \n";
    Wardrobe w2 = w1; 
    w2.print();

    cout << "\n Move construct \n";
    Wardrobe w3 = makeWardrobe(); 
    w3.print();

    cout << "\n End \n";
    return 0;
}

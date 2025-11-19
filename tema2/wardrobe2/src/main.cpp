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
    cout << "== Construct normal ==\n";
    Wardrobe w1;
    w1.add(ClothingItem("Hanorac", "L", 189.99));
    w1.add(ClothingItem("Geaca", "M", 299.99));
    w1.print();

    cout << "\n== Copy construct ==\n";
    Wardrobe w2 = w1; 
    w2.print();

    cout << "\n== Move construct ==\n";
    Wardrobe w3 = makeWardrobe(); 
    w3.print();

  
    // ITEM 10, 11, 12 DEMO
   

    cout << "\n== Copy assignment (Item 10,11,12) ==\n";
    Wardrobe w4;
    w4.add(ClothingItem("Sapca", "L", 39.99));

    w4 = w1;    
    w4.print();

    cout << "\n== Self assignment test (Item 11) ==\n";
    w4 = w4;    
    cout << "Self assignment OK\n";

    cout << "\n== Chained assignment test (Item 10) ==\n";
    Wardrobe w5, w6;
    w5 = w6 = w1;   
    w5.print();

    cout << "\n== End ==\n";
    return 0;
}

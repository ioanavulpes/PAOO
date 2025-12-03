#include "Investment.h"
#include <iostream>
#include <iomanip>

// Investment base class implementation
void Investment::printInfo() const {
    std::cout << "  Type: " << getType() << "\n";
    std::cout << "  Value: $" << std::fixed << std::setprecision(2) << getValue() << "\n";
}

// Stock implementation
Stock::Stock(const std::string& symbol, double price, int shares)
    : symbol_(symbol), price_(price), shares_(shares) {
    std::cout << "  [Stock created: " << symbol_ << "]\n";
}

Stock::~Stock() {
    std::cout << "  [Stock destroyed: " << symbol_ << "]\n";
}

std::string Stock::getType() const {
    return "Stock";
}

double Stock::getValue() const {
    return price_ * shares_;
}

void Stock::printInfo() const {
    Investment::printInfo();
    std::cout << "  Symbol: " << symbol_ << "\n";
    std::cout << "  Price: $" << price_ << " x " << shares_ << " shares\n";
}

// Bond implementation
Bond::Bond(const std::string& issuer, double faceValue, double interestRate)
    : issuer_(issuer), faceValue_(faceValue), interestRate_(interestRate) {
    std::cout << "  [Bond created: " << issuer_ << "]\n";
}

Bond::~Bond() {
    std::cout << "  [Bond destroyed: " << issuer_ << "]\n";
}

std::string Bond::getType() const {
    return "Bond";
}

double Bond::getValue() const {
    return faceValue_ * (1.0 + interestRate_);
}

void Bond::printInfo() const {
    Investment::printInfo();
    std::cout << "  Issuer: " << issuer_ << "\n";
    std::cout << "  Face Value: $" << faceValue_ << " @ " 
              << (interestRate_ * 100) << "% interest\n";
}

// Factory function - raw pointer (old style - NOT RECOMMENDED)
Investment* createInvestment(int type) {
    if (type == 0) {
        return new Stock("AAPL", 150.0, 10);
    } else if (type == 1) {
        return new Bond("US Treasury", 1000.0, 0.05);
    }
    return nullptr;
}

// Factory function - unique_ptr (RECOMMENDED for exclusive ownership)
std::unique_ptr<Investment> createInvestmentSmart(int type) {
    if (type == 0) {
        return std::make_unique<Stock>("GOOGL", 2800.0, 5);
    } else if (type == 1) {
        return std::make_unique<Bond>("Corporate Bond", 5000.0, 0.08);
    }
    return nullptr;
}

// Factory function - shared_ptr (RECOMMENDED for shared ownership)
std::shared_ptr<Investment> createInvestmentShared(int type) {
    if (type == 0) {
        return std::make_shared<Stock>("TSLA", 700.0, 20);
    } else if (type == 1) {
        return std::make_shared<Bond>("Municipal Bond", 10000.0, 0.04);
    }
    return nullptr;
}



#ifndef INVESTMENT_H
#define INVESTMENT_H

#include <string>
#include <memory>

// Base class for investment hierarchy
class Investment {
public:
    virtual ~Investment() = default;
    virtual std::string getType() const = 0;
    virtual double getValue() const = 0;
    virtual void printInfo() const;
};

// Derived class: Stock
class Stock : public Investment {
private:
    std::string symbol_;
    double price_;
    int shares_;

public:
    Stock(const std::string& symbol, double price, int shares);
    ~Stock();
    
    std::string getType() const override;
    double getValue() const override;
    void printInfo() const override;
};

// Derived class: Bond
class Bond : public Investment {
private:
    std::string issuer_;
    double faceValue_;
    double interestRate_;

public:
    Bond(const std::string& issuer, double faceValue, double interestRate);
    ~Bond();
    
    std::string getType() const override;
    double getValue() const override;
    void printInfo() const override;
};

// Factory function - returns raw pointer (demonstrates need for smart pointers)
Investment* createInvestment(int type);

// Better factory function - returns unique_ptr
std::unique_ptr<Investment> createInvestmentSmart(int type);

// Shared factory function - returns shared_ptr
std::shared_ptr<Investment> createInvestmentShared(int type);

#endif // INVESTMENT_H



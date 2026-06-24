#include "ElectronicsProduct.h"
#include <iostream>
#include <iomanip>
#include <cmath>

ElectronicsProduct::ElectronicsProduct(int id, const string& name, double price, int quantity,
                                       const string& supplier, int warranty)
    : Product(id, name, price, quantity, supplier), warranty(warranty), depreciation(10) {}

double ElectronicsProduct::getDepreciatedValue() const {
    // 每月貶值10%
    int monthsOld = warranty;  // 簡化:使用warranty作為月份
    double depreciationFactor = pow(0.9, monthsOld);
    return price * depreciationFactor;
}

string ElectronicsProduct::getInfo() const {
    return "Electronics | " + name + " | Warranty: " + to_string(warranty) + " months";
}

double ElectronicsProduct::calculateValue() const {
    // 電子產品按貶值價計算
    return getDepreciatedValue() * quantity;
}

string ElectronicsProduct::toCSV() const {
    return to_string(id) + ",ELECTRONICS," + name + "," + to_string(static_cast<int>(price * 100)) + ","
           + to_string(quantity) + "," + supplier + "," + to_string(warranty);
}

void ElectronicsProduct::displayDetails() const {
    cout << "[ELECTRONICS] ID: " << id << " | Name: " << name << " | Price: $"
         << fixed << setprecision(2) << price << " | Depreciated: $" << getDepreciatedValue()
         << " | Qty: " << quantity << " | Warranty: " << warranty << " months" << endl;
}

bool ElectronicsProduct::isValid() const {
    return Product::isValid() && warranty > 0;
}

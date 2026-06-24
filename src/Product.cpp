#include "Product.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

int Product::nextId = 1001;

Product::Product(int id, const string& name, double price, int quantity, const string& supplier)
    : id(id), name(name), price(price), quantity(quantity), supplier(supplier) {
    createdDate = time(nullptr);
    if (id >= nextId) {
        nextId = id + 1;
    }
}

bool Product::addStock(int amount) {
    if (amount <= 0) return false;
    quantity += amount;
    return true;
}

bool Product::removeStock(int amount) {
    if (amount <= 0 || amount > quantity) return false;
    quantity -= amount;
    return true;
}

double Product::calculateValue() const {
    return price * quantity;
}

bool Product::isValid() const {
    return id > 0 && !name.empty() && price > 0 && quantity >= 0 && !supplier.empty();
}

string Product::toCSV() const {
    return "";
}

void Product::displayDetails() const {
    cout << "ID: " << id << " | 名稱: " << name << " | 價格: $" << fixed << setprecision(2) << price
         << " | 數量: " << quantity << " | 供應商: " << supplier << endl;
}

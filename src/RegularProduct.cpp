#include "RegularProduct.h"
#include <iostream>
#include <iomanip>

RegularProduct::RegularProduct(int id, const string& name, double price, int quantity,
                               const string& supplier, const string& category)
    : Product(id, name, price, quantity, supplier), category(category) {}

string RegularProduct::getInfo() const {
    return "普通商品 | " + name + " | 類別: " + category;
}

string RegularProduct::toCSV() const {
    return to_string(id) + ",REGULAR," + name + "," + to_string(static_cast<int>(price * 100)) + ","
           + to_string(quantity) + "," + supplier + "," + category;
}

void RegularProduct::displayDetails() const {
    cout << "[普通商品] ID: " << id << " | 名稱: " << name << " | 價格: $"
         << fixed << setprecision(2) << price << " | 數量: " << quantity
         << " | 供應商: " << supplier << " | 類別: " << category << endl;
}

bool RegularProduct::isValid() const {
    return Product::isValid() && !category.empty();
}

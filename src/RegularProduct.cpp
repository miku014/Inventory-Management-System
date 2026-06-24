#include "RegularProduct.h"
#include <iostream>
#include <iomanip>

RegularProduct::RegularProduct(int id, const string& name, double price, int quantity,
                               const string& supplier, const string& category)
    : Product(id, name, price, quantity, supplier), category(category) {}

string RegularProduct::getInfo() const {
    return "Regular | " + name + " | Category: " + category;
}

string RegularProduct::toCSV() const {
    return to_string(id) + ",REGULAR," + name + "," + to_string(static_cast<int>(price * 100)) + ","
           + to_string(quantity) + "," + supplier + "," + category;
}

void RegularProduct::displayDetails() const {
    cout << "[REGULAR] ID: " << id << " | Name: " << name << " | Price: $"
         << fixed << setprecision(2) << price << " | Qty: " << quantity
         << " | Supplier: " << supplier << " | Category: " << category << endl;
}

bool RegularProduct::isValid() const {
    return Product::isValid() && !category.empty();
}

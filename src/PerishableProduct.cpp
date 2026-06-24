#include "PerishableProduct.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

PerishableProduct::PerishableProduct(int id, const string& name, double price, int quantity,
                                     const string& supplier, const string& expiryDate)
    : Product(id, name, price, quantity, supplier), expiryDate(expiryDate) {}

bool PerishableProduct::isExpired() const {
    string today = Utils::getCurrentDate();
    return Utils::compareDates(today, expiryDate) > 0;
}

int PerishableProduct::getDaysUntilExpiry() const {
    if (isExpired()) return -1;
    return Utils::daysUntilDate(expiryDate);
}

string PerishableProduct::getInfo() const {
    return "Perishable | " + name + " | Expires: " + expiryDate;
}

double PerishableProduct::calculateValue() const {
    if (isExpired()) return 0.0;  // 過期商品無價值
    return price * quantity;
}

string PerishableProduct::toCSV() const {
    return to_string(id) + ",PERISHABLE," + name + "," + to_string(static_cast<int>(price * 100)) + ","
           + to_string(quantity) + "," + supplier + "," + expiryDate;
}

void PerishableProduct::displayDetails() const {
    cout << "[PERISHABLE] ID: " << id << " | Name: " << name << " | Price: $"
         << fixed << setprecision(2) << price << " | Qty: " << quantity
         << " | Supplier: " << supplier << " | Expiry: " << expiryDate;
    if (isExpired()) {
        cout << " [EXPIRED]";
    } else {
        cout << " (" << getDaysUntilExpiry() << " days left)";
    }
    cout << endl;
}

bool PerishableProduct::isValid() const {
    return Product::isValid() && Utils::isDate(expiryDate);
}

bool PerishableProduct::removeStock(int amount) {
    if (isExpired()) {
        cout << "Cannot remove expired product!" << endl;
        return false;
    }
    return Product::removeStock(amount);
}

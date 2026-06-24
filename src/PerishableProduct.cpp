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
    return "易腐商品 | " + name + " | 到期日: " + expiryDate;
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
    cout << "[易腐商品] ID: " << id << " | 名稱: " << name << " | 價格: $"
         << fixed << setprecision(2) << price << " | 數量: " << quantity
         << " | 供應商: " << supplier << " | 到期日: " << expiryDate;
    if (isExpired()) {
        cout << " [已過期]";
    } else {
        cout << " (剩餘 " << getDaysUntilExpiry() << " 天到期)";
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

#ifndef PERISHABLE_PRODUCT_H
#define PERISHABLE_PRODUCT_H

#include "Product.h"
#include <ctime>

// 易腐商品類（如食品）
class PerishableProduct : public Product {
public:
    PerishableProduct(int id, const string& name, double price, int quantity,
                      const string& supplier, const string& expiryDate);

    void setExpiryDate(const string& date) { expiryDate = date; }
    string getExpiryDate() const { return expiryDate; }

    // 檢查是否過期
    bool isExpired() const;
    int getDaysUntilExpiry() const;

    // 實現虛函數
    string getType() const override { return "Perishable Product"; }
    string getInfo() const override;
    double calculateValue() const override;  // 過期商品價值為0
    string toCSV() const override;
    void displayDetails() const override;
    bool isValid() const override;
    bool removeStock(int amount) override;  // 檢查過期

private:
    string expiryDate;  // 格式: "YYYY-MM-DD"
};

#endif // PERISHABLE_PRODUCT_H

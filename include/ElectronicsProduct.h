#ifndef ELECTRONICS_PRODUCT_H
#define ELECTRONICS_PRODUCT_H

#include "Product.h"

// 電子產品類
class ElectronicsProduct : public Product {
public:
    ElectronicsProduct(int id, const string& name, double price, int quantity,
                       const string& supplier, int warranty = 12);

    void setWarranty(int months) { warranty = months; }
    int getWarranty() const { return warranty; }

    // 計算折舊值
    double getDepreciatedValue() const;
    int getDepreciation() const { return depreciation; }

    // 實現虛函數
    string getType() const override { return "Electronics Product"; }
    string getInfo() const override;
    double calculateValue() const override;
    string toCSV() const override;
    void displayDetails() const override;
    bool isValid() const override;

private:
    int warranty;       // 保修期（月數）
    int depreciation;   // 折舊率（百分比）
};

#endif // ELECTRONICS_PRODUCT_H

#ifndef REGULAR_PRODUCT_H
#define REGULAR_PRODUCT_H

#include "Product.h"

// 普通商品類
class RegularProduct : public Product {
public:
    RegularProduct(int id, const string& name, double price, int quantity, 
                   const string& supplier, const string& category = "General");

    void setCategory(const string& newCategory) { category = newCategory; }
    string getCategory() const { return category; }

    // 實現虛函數
    string getType() const override { return "Regular Product"; }
    string getInfo() const override;
    string toCSV() const override;
    void displayDetails() const override;
    bool isValid() const override;

private:
    string category;
};

#endif // REGULAR_PRODUCT_H

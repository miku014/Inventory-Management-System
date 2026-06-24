#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// 商品基類（使用虛函數實現多態）
class Product {
public:
    Product(int id, const string& name, double price, int quantity, const string& supplier);
    virtual ~Product() = default;

    // 基本信息
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    string getSupplier() const { return supplier; }
    time_t getCreatedDate() const { return createdDate; }

    // 設置方法
    void setName(const string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setSupplier(const string& newSupplier) { supplier = newSupplier; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }

    // 庫存操作
    virtual bool addStock(int amount);
    virtual bool removeStock(int amount);
    bool isLowStock() const { return quantity <= 10; }

    // 虛函數 - 用於多態
    virtual string getType() const = 0;
    virtual string getInfo() const = 0;
    virtual double calculateValue() const;
    virtual bool isValid() const;
    virtual string toCSV() const;
    virtual void displayDetails() const;

    // 靜態方法
    static int getNextId() { return nextId; }
    static void setNextId(int id) { nextId = id; }

protected:
    int id;
    string name;
    double price;
    int quantity;
    string supplier;
    time_t createdDate;
    static int nextId;
};

#endif // PRODUCT_H

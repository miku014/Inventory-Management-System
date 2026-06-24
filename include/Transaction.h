#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// 交易類型
enum TransactionType {
    STOCK_IN,   // 進貨
    STOCK_OUT   // 出貨
};

class Transaction {
public:
    Transaction(int productId, TransactionType type, int quantity, double unitPrice);

    // Getters
    int getProductId() const { return productId; }
    TransactionType getType() const { return type; }
    int getQuantity() const { return quantity; }
    double getUnitPrice() const { return unitPrice; }
    double getTotalAmount() const { return quantity * unitPrice; }
    time_t getTimestamp() const { return timestamp; }
    string getTypeString() const { return (type == STOCK_IN) ? "In" : "Out"; }

    // 顯示信息
    void displayInfo() const;
    string toCSV() const;

static Transaction fromCSV(const string& csvLine);

private:
    int productId;
    TransactionType type;
    int quantity;
    double unitPrice;
    time_t timestamp;
};

#endif // TRANSACTION_H

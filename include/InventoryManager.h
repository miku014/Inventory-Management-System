#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "Product.h"
#include "RegularProduct.h"
#include "PerishableProduct.h"
#include "ElectronicsProduct.h"
#include "Transaction.h"
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <memory>

using namespace std;

// 庫存管理類
class InventoryManager {
public:
    InventoryManager();
    ~InventoryManager();

    // 商品管理
    bool addProduct(Product* product);
    bool removeProduct(int productId);
    Product* getProduct(int productId) const;
    vector<Product*> getAllProducts() const;
    vector<Product*> searchByName(const string& name) const;

    // 庫存操作
    bool stockIn(int productId, int quantity, double unitPrice);
    bool stockOut(int productId, int quantity, double unitPrice);
    
    // 統計信息
    int getTotalProducts() const { return products.size(); }
    int getTotalQuantity() const;
    double getTotalValue() const;
    vector<Product*> getLowStockProducts() const;
    vector<Product*> getExpiredProducts() const;

    // 交易記錄
    void addTransaction(const Transaction& trans);
    vector<Transaction> getTransactionHistory() const { return transactions; }
    vector<Transaction> getProductTransactions(int productId) const;

    // 數據驗證
    bool isProductIdExists(int id) const;
    int getNextProductId() const;

    // 清空數據
    void clear();

private:
    vector<Product*> products;              // STL: Vector - 存儲所有商品
    map<int, Product*> productIndex;        // STL: Map - 快速查詢
    queue<Transaction> transactions;        // STL: Queue - 交易隊列
};

#endif // INVENTORY_MANAGER_H

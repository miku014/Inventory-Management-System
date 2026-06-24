#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Product.h"
#include "RegularProduct.h"
#include "PerishableProduct.h"
#include "ElectronicsProduct.h"
#include "Transaction.h"
#include "InventoryManager.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// 文件管理類
class FileManager {
public:
    FileManager(const string& dataDir = "data");

    // 保存數據
    bool saveProducts(const vector<Product*>& products, const string& filename = "products.csv");
    bool saveTransactions(const vector<Transaction>& transactions, const string& filename = "transactions.csv");

    // 加載數據
    vector<Product*> loadProducts(const string& filename = "products.csv");
    vector<Transaction> loadTransactions(const string& filename = "transactions.csv");

    // 路徑管理
    string getFilePath(const string& filename) const;
    bool ensureDataDirectory() const;

private:
    string dataDirectory;

    // 輔助方法
    vector<string> splitCSVLine(const string& line) const;
    string trimString(const string& str) const;
};

#endif // FILE_MANAGER_H

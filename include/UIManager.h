#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "InventoryManager.h"
#include "FileManager.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// UI管理類
class UIManager {
public:
    UIManager(InventoryManager* manager, FileManager* fileManager);

    // 主菜單
    void run();
    void showMainMenu();

private:
    InventoryManager* manager;
    FileManager* fileManager;
    bool running;

    // 菜單函數
    void handleProductManagement();
    void handleInventoryOperations();
    void handleReports();
    void handleDataManagement();

    // 商品操作
    void addProduct();
    void viewProduct();
    void modifyProduct();
    void deleteProduct();
    void listAllProducts();

    // 庫存操作
    void stockIn();
    void stockOut();
    void checkLowStock();
    void viewAllTransactions();

    // 報表功能
    void showInventoryReport();
    void showValueReport();
    void showProductTypeReport();
    void showTransactionReport();

    // 數據管理
    void saveData();
    void loadData();

    // 輔助方法
    void clearScreen() const;
    void printHeader(const string& title) const;
    void printSeparator() const;
    void pause() const;
    int getInput(const string& prompt) const;
    string getStringInput(const string& prompt) const;
    double getDoubleInput(const string& prompt) const;
    int selectProduct();
    int getProductType();
};

#endif // UI_MANAGER_H

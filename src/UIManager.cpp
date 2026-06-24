#include "UIManager.h"
#include "Utils.h"
#include <algorithm>
#include <limits>

UIManager::UIManager(InventoryManager* manager, FileManager* fileManager)
    : manager(manager), fileManager(fileManager), running(true) {}

void UIManager::run() {
    loadData();
    while (running) {
        showMainMenu();
    }
    saveData();
}

void UIManager::showMainMenu() {
    clearScreen();
    printHeader("=== 庫存管理系統 ===");
    cout << "1. 商品管理" << endl;
    cout << "2. 庫存操作" << endl;
    cout << "3. 報表查詢" << endl;
    cout << "4. 數據管理" << endl;
    cout << "0. 退出" << endl;
    cout << endl;

    int choice = getInput("請選擇");
    switch (choice) {
        case 1:
            handleProductManagement();
            break;
        case 2:
            handleInventoryOperations();
            break;
        case 3:
            handleReports();
            break;
        case 4:
            handleDataManagement();
            break;
        case 0:
            running = false;
            cout << "感謝使用，再見！" << endl;
            break;
        default:
            cout << "無效選擇！" << endl;
            pause();
    }
}

void UIManager::handleProductManagement() {
    bool subMenu = true;
    while (subMenu) {
        clearScreen();
        printHeader("=== 商品管理 ===");
        cout << "1. 新增商品" << endl;
        cout << "2. 查詢商品" << endl;
        cout << "3. 修改商品" << endl;
        cout << "4. 刪除商品" << endl;
        cout << "5. 列表所有商品" << endl;
        cout << "0. 返回" << endl;

        int choice = getInput("請選擇");
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProduct();
                break;
            case 3:
                modifyProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                listAllProducts();
                break;
            case 0:
                subMenu = false;
                break;
            default:
                cout << "無效選擇！" << endl;
                pause();
        }
    }
}

void UIManager::handleInventoryOperations() {
    bool subMenu = true;
    while (subMenu) {
        clearScreen();
        printHeader("=== 庫存操作 ===");
        cout << "1. 進貨" << endl;
        cout << "2. 出貨" << endl;
        cout << "3. 低庫存警告" << endl;
        cout << "4. 交易紀錄" << endl;
        cout << "0. 返回" << endl;

        int choice = getInput("請選擇");
        switch (choice) {
            case 1:
                stockIn();
                break;
            case 2:
                stockOut();
                break;
            case 3:
                checkLowStock();
                break;
            case 4:
                viewAllTransactions();
                break;
            case 0:
                subMenu = false;
                break;
            default:
                cout << "無效選擇！" << endl;
                pause();
        }
    }
}

void UIManager::handleReports() {
    bool subMenu = true;
    while (subMenu) {
        clearScreen();
        printHeader("=== 報表查詢 ===");
        cout << "1. 庫存統計報表" << endl;
        cout << "2. 價值統計報表" << endl;
        cout << "3. 商品類型報表" << endl;
        cout << "4. 交易報表" << endl;
        cout << "0. 返回" << endl;

        int choice = getInput("請選擇");
        switch (choice) {
            case 1:
                showInventoryReport();
                break;
            case 2:
                showValueReport();
                break;
            case 3:
                showProductTypeReport();
                break;
            case 4:
                showTransactionReport();
                break;
            case 0:
                subMenu = false;
                break;
            default:
                cout << "無效選擇！" << endl;
                pause();
        }
    }
}

void UIManager::handleDataManagement() {
    bool subMenu = true;
    while (subMenu) {
        clearScreen();
        printHeader("=== 數據管理 ===");
        cout << "1. 保存數據" << endl;
        cout << "2. 加載數據" << endl;
        cout << "0. 返回" << endl;

        int choice = getInput("請選擇");
        switch (choice) {
            case 1:
                saveData();
                break;
            case 2:
                loadData();
                break;
            case 0:
                subMenu = false;
                break;
            default:
                cout << "無效選擇！" << endl;
                pause();
        }
    }
}

void UIManager::addProduct() {
    clearScreen();
    printHeader("=== 新增商品 ===");

    int type = getProductType();
    int id = manager->getNextProductId();
    string name = getStringInput("商品名稱");
    double price = getDoubleInput("商品價格");
    int quantity = getInput("初始庫存數量");
    string supplier = getStringInput("供應商");

    Product* product = nullptr;

    if (type == 1) {
        string category = getStringInput("商品類別");
        product = new RegularProduct(id, name, price, quantity, supplier, category);
    } else if (type == 2) {
        string expiryDate = getStringInput("過期日期 (YYYY-MM-DD)");
        product = new PerishableProduct(id, name, price, quantity, supplier, expiryDate);
    } else if (type == 3) {
        int warranty = getInput("保修期(月數)");
        product = new ElectronicsProduct(id, name, price, quantity, supplier, warranty);
    }

    if (product && manager->addProduct(product)) {
        cout << "✓ 商品新增成功！(ID: " << id << ")" << endl;
    } else {
        cout << "✗ 商品新增失敗！" << endl;
        delete product;
    }
    pause();
}

void UIManager::viewProduct() {
    clearScreen();
    printHeader("=== 查詢商品 ===");
    int id = getInput("請輸入商品ID");
    Product* product = manager->getProduct(id);

    if (product) {
        product->displayDetails();
    } else {
        cout << "✗ 未找到該商品！" << endl;
    }
    pause();
}

void UIManager::modifyProduct() {
    clearScreen();
    printHeader("=== 修改商品 ===");
    int id = getInput("請輸入商品ID");
    Product* product = manager->getProduct(id);

    if (!product) {
        cout << "✗ 未找到該商品！" << endl;
        pause();
        return;
    }

    cout << "當前商品信息：" << endl;
    product->displayDetails();
    cout << endl;
    cout << "1. 修改名稱" << endl;
    cout << "2. 修改價格" << endl;
    cout << "3. 修改供應商" << endl;
    cout << "0. 返回" << endl;

    int choice = getInput("請選擇");
    switch (choice) {
        case 1:
            product->setName(getStringInput("新名稱"));
            cout << "✓ 已更新" << endl;
            break;
        case 2:
            product->setPrice(getDoubleInput("新價格"));
            cout << "✓ 已更新" << endl;
            break;
        case 3:
            product->setSupplier(getStringInput("新供應商"));
            cout << "✓ 已更新" << endl;
            break;
    }
    pause();
}

void UIManager::deleteProduct() {
    clearScreen();
    printHeader("=== 刪除商品 ===");
    int id = getInput("請輸入商品ID");

    Product* product = manager->getProduct(id);
    if (!product) {
        cout << "✗ 未找到該商品！" << endl;
        pause();
        return;
    }

    product->displayDetails();
    string confirm = getStringInput("確認刪除? (yes/no)");

    if (confirm == "yes") {
        if (manager->removeProduct(id)) {
            cout << "✓ 商品已刪除！" << endl;
        } else {
            cout << "✗ 刪除失敗！" << endl;
        }
    }
    pause();
}

void UIManager::listAllProducts() {
    clearScreen();
    printHeader("=== 所有商品 ===");

    vector<Product*> products = manager->getAllProducts();
    if (products.empty()) {
        cout << "目前沒有商品" << endl;
    } else {
        for (const auto& product : products) {
            product->displayDetails();
        }
    }
    pause();
}

void UIManager::stockIn() {
    clearScreen();
    printHeader("=== 進貨 ===");
    int id = selectProduct();
    if (id == -1) return;

    int quantity = getInput("進貨數量");
    double unitPrice = getDoubleInput("單價");

    if (manager->stockIn(id, quantity, unitPrice)) {
        cout << "✓ 進貨成功！" << endl;
    } else {
        cout << "✗ 進貨失敗！" << endl;
    }
    pause();
}

void UIManager::stockOut() {
    clearScreen();
    printHeader("=== 出貨 ===");
    int id = selectProduct();
    if (id == -1) return;

    int quantity = getInput("出貨數量");
    double unitPrice = getDoubleInput("單價");

    if (manager->stockOut(id, quantity, unitPrice)) {
        cout << "✓ 出貨成功！" << endl;
    } else {
        cout << "✗ 出貨失敗或庫存不足！" << endl;
    }
    pause();
}

void UIManager::checkLowStock() {
    clearScreen();
    printHeader("=== 低庫存警告 ===");

    vector<Product*> lowStock = manager->getLowStockProducts();
    if (lowStock.empty()) {
        cout << "✓ 所有商品庫存充足！" << endl;
    } else {
        cout << "⚠ 以下商品庫存低於10件：" << endl;
        for (const auto& product : lowStock) {
            product->displayDetails();
        }
    }
    pause();
}

void UIManager::viewAllTransactions() {
    clearScreen();
    printHeader("=== 交易紀錄 ===");

    vector<Transaction> transactions = manager->getTransactionHistory();
    if (transactions.empty()) {
        cout << "沒有交易紀錄" << endl;
    } else {
        for (const auto& trans : transactions) {
            trans.displayInfo();
        }
    }
    pause();
}

void UIManager::showInventoryReport() {
    clearScreen();
    printHeader("=== 庫存統計報表 ===");

    cout << setw(10) << "商品數量" << ": " << manager->getTotalProducts() << endl;
    cout << setw(10) << "總庫存" << ": " << manager->getTotalQuantity() << " 件" << endl;
    cout << setw(10) << "總價值" << ": $" << fixed << setprecision(2) << manager->getTotalValue() << endl;
    cout << endl;

    vector<Product*> products = manager->getAllProducts();
    if (!products.empty()) {
        cout << "各商品庫存：" << endl;
        for (const auto& product : products) {
            cout << setw(20) << left << product->getName() << ": " << product->getQuantity() << " 件\n";
        }
    }
    pause();
}

void UIManager::showValueReport() {
    clearScreen();
    printHeader("=== 價值統計報表 ===");

    double totalValue = manager->getTotalValue();
    cout << "庫存總價值: $" << fixed << setprecision(2) << totalValue << endl;
    cout << endl;

    vector<Product*> products = manager->getAllProducts();
    sort(products.begin(), products.end(),
         [](Product* a, Product* b) { return a->calculateValue() > b->calculateValue(); });

    if (!products.empty()) {
        cout << "按價值排序：" << endl;
        for (const auto& product : products) {
            cout << setw(20) << left << product->getName() << ": $" 
                 << fixed << setprecision(2) << product->calculateValue() << endl;
        }
    }
    pause();
}

void UIManager::showProductTypeReport() {
    clearScreen();
    printHeader("=== 商品類型報表 ===");

    int regular = 0, perishable = 0, electronics = 0;
    double regularValue = 0, perishableValue = 0, electronicsValue = 0;

    for (const auto& product : manager->getAllProducts()) {
        if (dynamic_cast<RegularProduct*>(product)) {
            regular++;
            regularValue += product->calculateValue();
        } else if (dynamic_cast<PerishableProduct*>(product)) {
            perishable++;
            perishableValue += product->calculateValue();
        } else if (dynamic_cast<ElectronicsProduct*>(product)) {
            electronics++;
            electronicsValue += product->calculateValue();
        }
    }

    cout << "普通商品: " << regular << "件, 總值: $" << fixed << setprecision(2) << regularValue << endl;
    cout << "易腐商品: " << perishable << "件, 總值: $" << fixed << setprecision(2) << perishableValue << endl;
    cout << "電子產品: " << electronics << "件, 總值: $" << fixed << setprecision(2) << electronicsValue << endl;
    pause();
}

void UIManager::showTransactionReport() {
    clearScreen();
    printHeader("=== 交易報表 ===");

    vector<Transaction> transactions = manager->getTransactionHistory();
    if (transactions.empty()) {
        cout << "沒有交易紀錄" << endl;
    } else {
        double totalIn = 0, totalOut = 0;
        for (const auto& trans : transactions) {
            if (trans.getType() == STOCK_IN) {
                totalIn += trans.getTotalAmount();
            } else {
                totalOut += trans.getTotalAmount();
            }
        }
        cout << "進貨總額: $" << fixed << setprecision(2) << totalIn << endl;
        cout << "出貨總額: $" << fixed << setprecision(2) << totalOut << endl;
    }
    pause();
}

void UIManager::saveData() {
    clearScreen();
    printHeader("=== 保存數據 ===");

    vector<Product*> products = manager->getAllProducts();
    vector<Transaction> transactions = manager->getTransactionHistory();

    if (fileManager->saveProducts(products) && fileManager->saveTransactions(transactions)) {
        cout << "✓ 數據已保存！" << endl;
    } else {
        cout << "✗ 保存失敗！" << endl;
    }
    pause();
}

void UIManager::loadData() {
    manager->clear();
    vector<Product*> products = fileManager->loadProducts();
    for (auto product : products) {
        manager->addProduct(product);
    }
    cout << "✓ 已加載 " << products.size() << " 個商品" << endl;
    pause();
}

void UIManager::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UIManager::printHeader(const string& title) const {
    cout << title << endl;
    printSeparator();
}

void UIManager::printSeparator() const {
    cout << "================================" << endl;
}

void UIManager::pause() const {
    cout << "\n按 Enter 繼續..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int UIManager::getInput(const string& prompt) const {
    int value;
    cout << prompt << ": ";
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "輸入無效，請重試: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string UIManager::getStringInput(const string& prompt) const {
    string value;
    cout << prompt << ": ";
    getline(cin, value);
    return value;
}

double UIManager::getDoubleInput(const string& prompt) const {
    double value;
    cout << prompt << ": ";
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "輸入無效，請重試: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

int UIManager::selectProduct() {
    listAllProducts();
    clearScreen();
    return getInput("輸入商品ID");
}

int UIManager::getProductType() {
    cout << "請選擇商品類型:" << endl;
    cout << "1. 普通商品" << endl;
    cout << "2. 易腐商品(食品等)" << endl;
    cout << "3. 電子產品" << endl;
    return getInput("請選擇");
}

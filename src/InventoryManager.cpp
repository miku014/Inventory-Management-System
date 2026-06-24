#include "InventoryManager.h"
#include <algorithm>
#include <iostream>

InventoryManager::InventoryManager() {}

InventoryManager::~InventoryManager() {
    for (auto product : products) {
        delete product;
    }
    products.clear();
    productIndex.clear();
}

bool InventoryManager::addProduct(Product* product) {
    if (!product || !product->isValid()) return false;
    if (isProductIdExists(product->getId())) return false;

    products.push_back(product);
    productIndex[product->getId()] = product;
    return true;
}

bool InventoryManager::removeProduct(int productId) {
    auto it = find_if(products.begin(), products.end(),
                     [productId](Product* p) { return p->getId() == productId; });
    if (it == products.end()) return false;

    productIndex.erase(productId);
    delete *it;
    products.erase(it);
    return true;
}

Product* InventoryManager::getProduct(int productId) const {
    auto it = productIndex.find(productId);
    return (it != productIndex.end()) ? it->second : nullptr;
}

vector<Product*> InventoryManager::getAllProducts() const {
    return products;
}

vector<Product*> InventoryManager::searchByName(const string& name) const {
    vector<Product*> results;
    copy_if(products.begin(), products.end(), back_inserter(results),
           [&name](Product* p) { return p->getName().find(name) != string::npos; });
    return results;
}

bool InventoryManager::stockIn(int productId, int quantity, double unitPrice) {
    Product* product = getProduct(productId);
    if (!product) return false;

    if (product->addStock(quantity)) {
        addTransaction(Transaction(productId, STOCK_IN, quantity, unitPrice));
        return true;
    }
    return false;
}

bool InventoryManager::stockOut(int productId, int quantity, double unitPrice) {
    Product* product = getProduct(productId);
    if (!product) return false;

    if (product->removeStock(quantity)) {
        addTransaction(Transaction(productId, STOCK_OUT, quantity, unitPrice));
        return true;
    }
    return false;
}

int InventoryManager::getTotalQuantity() const {
    int total = 0;
    for (const auto& product : products) {
        total += product->getQuantity();
    }
    return total;
}

double InventoryManager::getTotalValue() const {
    double total = 0;
    for (const auto& product : products) {
        total += product->calculateValue();
    }
    return total;
}

vector<Product*> InventoryManager::getLowStockProducts() const {
    vector<Product*> results;
    copy_if(products.begin(), products.end(), back_inserter(results),
           [](Product* p) { return p->isLowStock(); });
    return results;
}

vector<Product*> InventoryManager::getExpiredProducts() const {
    vector<Product*> results;
    for (auto product : products) {
        auto perishable = dynamic_cast<PerishableProduct*>(product);
        if (perishable && perishable->isExpired()) {
            results.push_back(product);
        }
    }
    return results;
}

void InventoryManager::addTransaction(const Transaction& trans) {
    transactions.push(trans);
}

vector<Transaction> InventoryManager::getProductTransactions(int productId) const {
    vector<Transaction> results;
    queue<Transaction> tempQueue = transactions;
    while (!tempQueue.empty()) {
        if (tempQueue.front().getProductId() == productId) {
            results.push_back(tempQueue.front());
        }
        tempQueue.pop();
    }
    return results;
}

bool InventoryManager::isProductIdExists(int id) const {
    return productIndex.find(id) != productIndex.end();
}

int InventoryManager::getNextProductId() const {
    return Product::getNextId();
}

void InventoryManager::clear() {
    for (auto product : products) {
        delete product;
    }
    products.clear();
    productIndex.clear();
    while (!transactions.empty()) {
        transactions.pop();
    }
}

#include "FileManager.h"
#include "Utils.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

FileManager::FileManager(const string& dataDir) : dataDirectory(dataDir) {
    ensureDataDirectory();
}

bool FileManager::saveProducts(const vector<Product*>& products, const string& filename) {
    string filepath = getFilePath(filename);
    ofstream file(filepath);
    if (!file.is_open()) return false;

    // 寫入CSV頭
    file << "ID,Type,Name,Price,Quantity,Supplier,Extra" << endl;

    for (const auto& product : products) {
        file << product->toCSV() << endl;
    }

    file.close();
    return true;
}

bool FileManager::saveTransactions(const vector<Transaction>& transactions, const string& filename) {
    string filepath = getFilePath(filename);
    ofstream file(filepath);
    if (!file.is_open()) return false;

    file << "ProductID,Type,Quantity,UnitPrice,Timestamp" << endl;

    for (const auto& trans : transactions) {
        file << trans.toCSV() << endl;
    }

    file.close();
    return true;
}

vector<Product*> FileManager::loadProducts(const string& filename) {
    vector<Product*> products;
    string filepath = getFilePath(filename);
    ifstream file(filepath);
    if (!file.is_open()) return products;

    string line;
    getline(file, line);  // 跳過頭行

    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> tokens = splitCSVLine(line);
        if (tokens.size() < 6) continue;

        int id = stoi(tokens[0]);
        string type = tokens[1];
        string name = trimString(tokens[2]);
        double price = stod(tokens[3]) / 100.0;
        int quantity = stoi(tokens[4]);
        string supplier = trimString(tokens[5]);

        Product* product = nullptr;

        if (type == "REGULAR") {
            string category = (tokens.size() > 6) ? trimString(tokens[6]) : "General";
            product = new RegularProduct(id, name, price, quantity, supplier, category);
        } else if (type == "PERISHABLE") {
            string expiryDate = (tokens.size() > 6) ? trimString(tokens[6]) : "2025-12-31";
            product = new PerishableProduct(id, name, price, quantity, supplier, expiryDate);
        } else if (type == "ELECTRONICS") {
            int warranty = (tokens.size() > 6) ? stoi(tokens[6]) : 12;
            product = new ElectronicsProduct(id, name, price, quantity, supplier, warranty);
        }

        if (product) {
            products.push_back(product);
        }
    }

    file.close();
    return products;
}

vector<Transaction> FileManager::loadTransactions(const string& filename) {
    vector<Transaction> transactions;
    string filepath = getFilePath(filename);
    ifstream file(filepath);
    if (!file.is_open()) return transactions;

    string line;
    getline(file, line);  // 跳過頭行

    while (getline(file, line)) {
        if (line.empty()) continue;
        transactions.push_back(Transaction::fromCSV(line));
    }

    file.close();
    return transactions;
}

string FileManager::getFilePath(const string& filename) const {
    return dataDirectory + "/" + filename;
}

bool FileManager::ensureDataDirectory() const {
    try {
        fs::create_directories(dataDirectory);
        return true;
    } catch (...) {
        return false;
    }
}

vector<string> FileManager::splitCSVLine(const string& line) const {
    vector<string> tokens;
    string current;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            tokens.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    tokens.push_back(current);
    return tokens;
}

string FileManager::trimString(const string& str) const {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

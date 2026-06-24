#include "Transaction.h"
#include <iomanip>

Transaction::Transaction(int productId, TransactionType type, int quantity, double unitPrice)
    : productId(productId), type(type), quantity(quantity), unitPrice(unitPrice) {
    timestamp = time(nullptr);
}

void Transaction::displayInfo() const {
    time_t t = timestamp;
    struct tm* timeinfo = localtime(&t);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    cout << "[" << buffer << "] Product ID: " << productId 
         << " | Type: " << getTypeString() 
         << " | Qty: " << quantity 
         << " | Unit: $" << fixed << setprecision(2) << unitPrice
         << " | Total: $" << getTotalAmount() << endl;
}

string Transaction::toCSV() const {
    return to_string(productId) + "," + getTypeString() + "," + to_string(quantity) + ","
           + to_string(static_cast<int>(unitPrice * 100)) + "," + to_string(timestamp);
}

Transaction Transaction::fromCSV(const string& csvLine) {
    size_t pos = 0;
    string token;
    vector<string> tokens;
    string line = csvLine;

    while ((pos = line.find(',')) != string::npos) {
        tokens.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    tokens.push_back(line);

    int productId = stoi(tokens[0]);
    TransactionType type = (tokens[1] == "In") ? STOCK_IN : STOCK_OUT;
    int quantity = stoi(tokens[2]);
    double unitPrice = stod(tokens[3]) / 100.0;

    Transaction trans(productId, type, quantity, unitPrice);
    trans.timestamp = stol(tokens[4]);
    return trans;
}

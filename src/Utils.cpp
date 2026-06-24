#include "Utils.h"
#include <cctype>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <cmath>

string Utils::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

string Utils::toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

vector<string> Utils::split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool Utils::isInteger(const string& str) {
    if (str.empty()) return false;
    size_t start = (str[0] == '-') ? 1 : 0;
    return str.find_first_not_of("0123456789", start) == string::npos;
}

bool Utils::isDouble(const string& str) {
    if (str.empty()) return false;
    try {
        stod(str);
        return true;
    } catch (...) {
        return false;
    }
}

bool Utils::isDate(const string& str) {
    // 簡單檢查 YYYY-MM-DD 格式
    if (str.length() != 10) return false;
    if (str[4] != '-' || str[7] != '-') return false;
    return isInteger(str.substr(0, 4)) && isInteger(str.substr(5, 2)) && isInteger(str.substr(8, 2));
}

string Utils::getCurrentDate() {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    struct tm* timeinfo = localtime(&time);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer);
}

string Utils::getDateString(time_t timestamp) {
    struct tm* timeinfo = localtime(&timestamp);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer);
}

int Utils::compareDates(const string& date1, const string& date2) {
    // 返回: 負數表示date1<date2, 0表示相等, 正數表示date1>date2
    if (date1 < date2) return -1;
    if (date1 > date2) return 1;
    return 0;
}

int Utils::daysUntilDate(const string& targetDate) {
    string today = getCurrentDate();
    // 簡單計算: 通過字符串比較進行近似
    int todayDays = stoi(targetDate.substr(0, 4)) * 365 + stoi(targetDate.substr(5, 2)) * 30 + stoi(targetDate.substr(8, 2));
    int targetDays = stoi(today.substr(0, 4)) * 365 + stoi(today.substr(5, 2)) * 30 + stoi(today.substr(8, 2));
    return todayDays - targetDays;
}

string Utils::formatCurrency(double amount, int precision) {
    stringstream ss;
    ss << fixed << setprecision(precision) << amount;
    return ss.str();
}

string Utils::formatInteger(int num, int width) {
    stringstream ss;
    ss << setfill('0') << setw(width) << num;
    return ss.str();
}

string Utils::padString(const string& str, int width, bool leftAlign) {
    stringstream ss;
    if (leftAlign) {
        ss << left << setfill(' ') << setw(width) << str;
    } else {
        ss << right << setfill(' ') << setw(width) << str;
    }
    return ss.str();
}

bool Utils::validatePrice(double price) {
    return price > 0;
}

bool Utils::validateQuantity(int quantity) {
    return quantity >= 0;
}

bool Utils::validateId(int id) {
    return id > 0;
}

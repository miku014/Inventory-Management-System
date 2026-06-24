#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

namespace Utils {
    // 字符串處理
    string trim(const string& str);
    string toLower(const string& str);
    vector<string> split(const string& str, char delimiter);
    bool isInteger(const string& str);
    bool isDouble(const string& str);
    bool isDate(const string& str);  // 檢查"YYYY-MM-DD"格式

    // 日期處理
    string getCurrentDate();
    string getDateString(time_t timestamp);
    int compareDates(const string& date1, const string& date2);
    int daysUntilDate(const string& targetDate);

    // 格式化
    string formatCurrency(double amount, int precision = 2);
    string formatInteger(int num, int width = 4);
    string padString(const string& str, int width, bool leftAlign = true);

    // 驗證
    bool validatePrice(double price);
    bool validateQuantity(int quantity);
    bool validateId(int id);
}

#endif // UTILS_H

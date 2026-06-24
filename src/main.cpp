#include <iostream>
#include "InventoryManager.h"
#include "FileManager.h"
#include "UIManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // 設定輸出編碼為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入編碼為 UTF-8
    #endif

    // 初始化系統
    InventoryManager manager;
    FileManager fileManager("data");
    UIManager ui(&manager, &fileManager);

    // 運行UI
    ui.run();

    return 0;
}

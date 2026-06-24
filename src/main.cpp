#include <iostream>
#include "InventoryManager.h"
#include "FileManager.h"
#include "UIManager.h"

using namespace std;

int main() {
    // 初始化系統
    InventoryManager manager;
    FileManager fileManager("data");
    UIManager ui(&manager, &fileManager);

    // 運行UI
    ui.run();

    return 0;
}

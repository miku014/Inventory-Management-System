# 庫存管理系統 (Inventory Management System) - 開發迭代與設計決策說明書

本文件記錄本系統的完整開發迭代歷程、架構演進、核心技術決策，以及在開發過程中遇到的技術挑戰與解決方案。

---

## 1. 開發迭代階段與歷程

本專案的開發過程分為五個核心迭代階段：

### 迭代 1：需求分析與 OOP 類別層級設計
* **目標**：確立系統核心類別與繼承關係。
* **成果**：
  * 設計 `Product` 作為抽象基底類別，定義純虛擬函數 `getType()` 與 `getInfo()` 以支援多型。
  * 衍生出 `RegularProduct`、`PerishableProduct`、`ElectronicsProduct` 三個子類別。
  * 引入虛擬解構子 `virtual ~Product() = default;`，確保釋放衍生類別時能正確調用析構程序，避免資源遺失。

### 迭代 2：核心業務邏輯與 STL 整合
* **目標**：實作庫存管理與交易流水記錄，運用標準模板庫 (STL)。
* **成果**：
  * 建立 `InventoryManager` 類別。
  * **STL Vector**：使用 `std::vector<Product*>` 儲存動態分配的商品指針。
  * **STL Map**：使用 `std::map<int, Product*>` 對商品 ID 進行索引，將查詢時間複雜度由 $O(N)$ 降至 $O(\log N)$。
  * **STL Queue**：使用 `std::queue<Transaction>` 儲存交易歷史，符合進出貨記錄「先進先出 (FIFO)」與流水的特性。
  * **STL Algorithm**：整合 `std::find_if`、`std::copy_if`、`std::sort` 等演算法，用於商品搜尋、低庫存篩選與報表價值排序。

### 迭代 3：數據持久化與檔案 I/O
* **目標**：實現關機後數據不遺失的持久化功能。
* **成果**：
  * 建立 `FileManager` 類別，負責 CSV 格式檔案的讀寫。
  * **美分單位設計**：在 CSV 中以「美分」整數格式儲存金額（如 `$12.34` 儲存為 `1234`），在讀取時再除以 `100.0`，徹底解決浮點數在文本轉換與計算中的精度丟失問題。
  * **自動路徑管理**：使用 C++17 `std::filesystem` 建立 `data/` 資料夾，自動檢測並確保儲存路徑存在。

### 迭代 4：終端機互動介面 (Terminal UI) 實作
* **目標**：搭建友善、安全的選單操作介面。
* **成果**：
  * 建立 `UIManager` 類別，使用無窮循環配合 `switch-case` 搭建多級選單。
  * 實作嚴格的輸入流控制（如 `cin.clear()` 與 `cin.ignore()`），防止使用者輸入非數值字元時導致終端機陷入死循環。

### 迭代 5：系統重構、錯誤修復與優化 (AI 協同開發)
* **目標**：修復編譯錯誤、排除潛在的記憶體洩漏與改進 UI 互動缺陷。
* **成果**：
  * 解決了 Windows 環境下 MSVC 編譯器對於 UTF-8 中文字元集的解析錯誤。
  * 解決了 STL 容器類型轉換不匹配的嚴重編譯阻礙。
  * 重構了商品選擇互動流程，消除了過早清空螢幕的 UI 缺憾。
  * 補全了加載數據時的記憶體回收機制。

---

## 2. 技術挑戰與解決方案 (技術誌)

在編譯與整合測試階段，系統遇到了數個重大挑戰，以下是詳細的排除紀錄：

### 挑戰 2.1：MSVC 編譯器 UTF-8 中文字元集解析語法錯誤
* **現象**：在 Windows 環境下使用 MSVC 編譯時，`UIManager.cpp` 出現大量莫名其妙的語法錯誤（如 `error C2001: 字串字面值中的換行`、`error C2143: 語法錯誤: 遺漏 ';'`）。
* **原因分析**：
  * 源文件以 UTF-8 編碼儲存。但 MSVC 在繁體中文 Windows 系統上預設使用 Code Page 950 (Big5) 來解讀源文件。
  * UTF-8 的中文字元（如「總價值」的「值」，其位元組編碼為 `\xe5\x80\xbc`）在被當作 Big5 解析時，其尾部多位元組被誤判為包含 ASCII 的 `\`（`0x5c`，反斜線轉義字元）。
  * 這導致緊隨其後的雙引號 `"` 被轉義（變為 `\"`），使得字串字面值未能正常閉合，編譯器將下一行程式碼視為字串的一部分，從而引發「字串字面值中換行」等語法崩潰。
* **解決方案**：
  * 修改 `CMakeLists.txt`，在 MSVC 編譯環境下強制加上 `/utf-8` 編譯參數：
    ```cmake
    if(MSVC)
        target_compile_options(inventory_system PRIVATE /W4 /utf-8)
        target_compile_definitions(inventory_system PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif()
    ```
  * 同時加入 `_CRT_SECURE_NO_WARNINGS` 定義，抑制 MSVC 對標準庫 `localtime` 等安全警告，實現乾淨無警告的編譯。

### 挑戰 2.2：STL `std::queue` 與 `std::vector` 的類型不匹配
* **現象**：編譯器報錯，無法將 `std::queue<Transaction>` 隱式轉換為 `std::vector<Transaction>`。
* **原因分析**：
  * 在 `InventoryManager.h` 中，交易記錄儲存在 `std::queue<Transaction> transactions` 中。
  * 然而，`getTransactionHistory()` 函數的原型宣告回傳 `std::vector<Transaction>`，且原先以 inline 方式編寫：`return transactions;`。
  * C++ 的 `std::queue` 是容器轉接器（Container Adapter），不提供向 `std::vector` 的自動轉換或複製構造。
* **解決方案**：
  * 將 `getTransactionHistory()` 的 inline 實作從標頭檔移除，僅保留宣告。
  * 在 `InventoryManager.cpp` 中實作該函數，透過局部隊列的複製與彈出，將數據逐一填充至 vector 中回傳：
    ```cpp
    vector<Transaction> InventoryManager::getTransactionHistory() const {
        vector<Transaction> results;
        queue<Transaction> tempQueue = transactions;
        while (!tempQueue.empty()) {
            results.push_back(tempQueue.front());
            tempQueue.pop();
        }
        return results;
    }
    ```

### 挑戰 2.3：商品選擇介面過早清空螢幕的體驗問題
* **現象**：進行進貨或出貨操作時，系統列出商品後，會立即清空畫面並提示輸入 ID，使用者在輸入時無法對照商品清單。
* **解決方案**：
  * 重構 `UIManager::selectProduct()`。直接在該函數內讀取所有商品，並將清單與輸入提示呈現在同一個畫面上，免除調用 `listAllProducts()` 產生的多餘暫停與清屏。
  * 在輸入提示中整合「輸入 0 取消」機制，回傳 `-1`，並讓呼叫端（進貨、出貨、修改、刪除）直接安全返回，大幅提升系統容錯率與流暢度。

### 挑戰 2.4：數據加載時的動態指針記憶體洩漏
* **現象**：分析代碼發現，在 `UIManager::loadData()` 中從 CSV 檔案載入商品指針陣列並加入 manager 時，若 `addProduct` 因為 ID 重複等原因失敗，該指針未被釋放，導致記憶體洩漏。
* **解決方案**：
  * 優化加載邏輯。當 `manager->addProduct(product)` 回傳 `false` 時，明確呼叫 `delete product;` 釋放該指針，保證系統的記憶體安全。

---

## 3. 開發總結與反思

本系統的開發迭代過程，充分展現了 C++ 語言在記憶體管理、物件導向抽象以及 STL 標準庫運用上的強大能力。
1. **多型設計** 使得商品基底類別可以擴展出截然不同的業務邏輯（如電子產品折舊、食品過期），而核心庫存管理邏輯（`InventoryManager`）無需針對每種新商品撰寫重複代碼，實現了高內聚、低耦合。
2. **浮點數精度規避** 透過在檔案中採用「分」作為存儲單位，完美規避了實務上最棘手的財務計算精度誤差，是軟體工程中十分實用的設計模式。
3. **字元集編碼適應** 的經驗提醒我們，在跨平台開發（Linux/Windows）時，必須明確指定編譯器的源碼字元集參數，以確保中文等多位元組字元在各平台下的編譯一致性。

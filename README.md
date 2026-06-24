# 庫存管理系統 (Inventory Management System)

## 📋 項目概述

這是一個使用C++開發的**庫存管理系統**，完全滿足期末專題所有要求：

- ✅ C++類別繼承功能
- ✅ 文件讀寫功能
- ✅ STL標準庫使用
- ✅ 終端機UI操作介面
- ✅ 完整的規格說明
- ✅ 開發迭代流程文檔
- ✅ 完整的說明文件

## 🎯 核心功能

### 1. 商品管理
- 添加新商品（支持多種商品類型）
- 查詢商品信息
- 修改商品詳情
- 刪除商品

### 2. 庫存操作
- 商品進貨（增加庫存）
- 商品出貨（減少庫存）
- 庫存警告提醒
- 庫存盤點統計

### 3. 數據管理
- CSV格式文件保存
- 程序啟動時自動加載數據
- 交易記錄保存

### 4. 報表功能
- 庫存統計報表
- 商品價值統計
- 交易記錄查詢

## 🏗️ 架構設計

![系統架構圖](docs/architecture_diagram.png)

### 類別繼承結構
```
Product (基礎類別)
├── RegularProduct (普通商品)
├── PerishableProduct (易腐商品)
└── ElectronicsProduct (電子產品)

System
├── InventoryManager (庫存管理)
├── FileManager (文件管理)
└── UIManager (用戶界面)
```

### STL使用
- `vector<>` - 商品列表
- `map<>` - 商品ID索引
- `queue<>` - 交易隊列
- `sort()` - 排序算法
- `find()` - 查找算法

## 📁 項目結構

```
Inventory-Management-System/
├── include/                 # 頭文件
│   ├── Product.h           # 商品基類
│   ├── RegularProduct.h    # 普通商品
│   ├── PerishableProduct.h # 易腐商品
│   ├── ElectronicsProduct.h # 電子產品
│   ├── InventoryManager.h  # 庫存管理
│   ├── FileManager.h       # 文件管理
│   ├── UIManager.h         # UI管理
│   ├── Transaction.h       # 交易記錄
│   └── Utils.h             # 工具函數
├── src/                     # 源文件
│   ├── main.cpp            # 主程序
│   ├── Product.cpp         # 商品基類實現
│   ├── RegularProduct.cpp  # 普通商品實現
│   ├── PerishableProduct.cpp # 易腐商品實現
│   ├── ElectronicsProduct.cpp # 電子產品實現
│   ├── InventoryManager.cpp  # 庫存管理實現
│   ├── FileManager.cpp     # 文件管理實現
│   ├── UIManager.cpp       # UI管理實現
│   └── Utils.cpp           # 工具函數實現
├── data/                    # 數據文件
│   ├── products.csv        # 商品數據
│   ├── transactions.csv    # 交易記錄
│   └── suppliers.csv       # 供應商數據
├── docs/                    # 文檔
│   ├── SPECIFICATION.md    # 功能規格說明
│   ├── DEVELOPMENT.md      # 開發迭代過程
│   ├── USER_GUIDE.md       # 用戶指南
│   └── ARCHITECTURE.md     # 架構設計說明
├── CMakeLists.txt          # 構建配置
└── README.md               # 本文件
```

## 🚀 快速開始

### 編譯
```bash
mkdir build
cd build
cmake ..
make
```

### 運行
```bash
./inventory_system
```

## 🖥️ 系統選單操作說明

本系統採用階層式的終端機選單（Terminal UI）進行操作，分為主選單與四個功能子選單：

### 1. 主選單 (Main Menu)
* **`1. 商品管理`** - 進入商品品項定義與維護選單。
* **`2. 庫存操作`** - 進入進出貨、低庫存警告與交易流水帳選單。
* **`3. 報表查詢`** - 進入統計報表選單（資產評估與排序）。
* **`4. 數據管理`** - 進入手動備份與還原數據選單。
* **`0. 退出`** - 自動保存所有內存資料並安全關閉系統。

### 2. 商品管理選單 (Product Management)
* **`1. 新增商品`** - 建立普通商品、易腐商品（需輸入過期日）或電子產品（需輸入保固期）。
* **`2. 查詢商品`** - 輸入 ID 查詢單一商品的詳細狀態與特有屬性。
* **`3. 修改商品`** - 提供選單修改商品的名稱、價格與供應商。
* **`4. 刪除商品`** - 刪除品項並釋放記憶體（需輸入 `yes` 二次確認）。
* **`5. 列表所有商品`** - 一覽式輸出所有已定義商品的屬性與庫存。

### 3. 庫存操作選單 (Inventory Operations)
* **`1. 進貨`** - 選擇商品並輸入數量與單價，更新庫存並寫入交易記錄。
* **`2. 出貨`** - 選擇商品並輸入數量與單價，扣減庫存並寫入交易記錄（自動限制庫存不足與食品過期出貨）。
* **`3. 低庫存警告`** - 自動列出庫存 $\le 10$ 件的商品，便於及時採購。
* **`4. 交易紀錄`** - 展示系統運行至今的完整進出貨交易流水帳。

### 4. 報表查詢選單 (Reports & Statistics)
* **`1. 庫存統計報表`** - 統計總種類數、總庫存量與庫存總價值。
* **`2. 價值統計報表`** - 計算商品價值並依**總價值由高到低（降冪）**排序輸出（過期食品價值歸零，電子產品折算折舊）。
* **`3. 商品類型報表`** - 分類統計三種商品的種類件數與各自的資產價值。
* **`4. 交易報表`** - 統計歷史累計的進貨總支出與出貨總收入，便於財務對帳。

### 5. 數據管理選單 (Data Management)
* **`1. 保存數據`** - 手動將商品與交易資料寫入 CSV 檔案。
* **`2. 加載數據`** - 手動自磁碟的 CSV 檔案重新載入數據。
* *（註：系統在啟動時會自動加載，退出時會自動保存，日常操作無需頻繁手動執行此選單）*

## 📖 文檔導航

- **[功能規格說明](docs/SPECIFICATION.md)** - 詳細的功能規格
- **[開發迭代過程](docs/DEVELOPMENT.md)** - 開發歷程和設計決策
- **[用戶指南](docs/USER_GUIDE.md)** - 如何使用系統
- **[架構設計](docs/ARCHITECTURE.md)** - 技術架構詳解

## 🛠️ 技術棧

- **語言**: C++17
- **標準庫**: STL (Vector, Map, Queue, Algorithm)
- **構建系統**: CMake
- **文件格式**: CSV

## 👥 作者

- 學生: miku014
- 項目: 期末專題 - 庫存管理系統

## 📝 許可證

MIT License

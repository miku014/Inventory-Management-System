cmake_minimum_required(VERSION 3.10)
project(InventoryManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目錄
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源文件
set(SOURCES
    src/main.cpp
    src/Product.cpp
    src/RegularProduct.cpp
    src/PerishableProduct.cpp
    src/ElectronicsProduct.cpp
    src/InventoryManager.cpp
    src/FileManager.cpp
    src/UIManager.cpp
    src/Transaction.cpp
    src/Utils.cpp
)

# 可執行文件
add_executable(inventory_system ${SOURCES})

# 如果需要額外的編譯選項
if(MSVC)
    target_compile_options(inventory_system PRIVATE /W4 /utf-8)
    target_compile_definitions(inventory_system PRIVATE _CRT_SECURE_NO_WARNINGS _HAS_STD_BYTE=0)
else()
    target_compile_options(inventory_system PRIVATE -Wall -Wextra -pedantic)
endif()

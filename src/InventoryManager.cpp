#include "InventoryManager.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <limits>

InventoryManager::InventoryManager() {
}

InventoryManager::~InventoryManager() {
}

void InventoryManager::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void InventoryManager::addItem() {
    std::cout << "\n--- Add Item ---\n";
    Item item;
    item.is_deleted = 0;

    std::cout << "Enter ID (positive): ";
    while (!(std::cin >> item.id) || item.id <= 0) {
        std::cout << "Invalid ID. Enter a positive integer: ";
        clearInput();
    }
    clearInput();

    std::cout << "Enter Name: ";
    std::string nameInput;
    while (true) {
        std::getline(std::cin, nameInput);
        if (!nameInput.empty()) {
            std::strncpy(item.name, nameInput.c_str(), sizeof(item.name) - 1);
            item.name[sizeof(item.name) - 1] = '\0';
            break;
        } else {
            std::cout << "Name cannot be empty. Enter Name: ";
        }
    }

    std::cout << "Enter Quantity (0 or more): ";
    while (!(std::cin >> item.quantity) || item.quantity < 0) {
        std::cout << "Invalid Quantity. Enter 0 or more: ";
        clearInput();
    }

    std::cout << "Enter Price (0 or more): ";
    while (!(std::cin >> item.price) || item.price < 0) {
        std::cout << "Invalid Price. Enter 0 or more: ";
        clearInput();
    }

    if (add_item(item)) {
        std::cout << "Item added successfully!\n";
    } else {
        std::cout << "Failed to add item. ID may already exist.\n";
    }
}

void InventoryManager::viewItem() {
    std::cout << "\n--- View Item ---\n";
    int id;
    std::cout << "Enter ID to view: ";
    while (!(std::cin >> id) || id <= 0) {
        std::cout << "Invalid ID. Enter a positive integer: ";
        clearInput();
    }

    Item item;
    if (get_item(id, &item)) {
        printItemHeader();
        printItem(item);
    } else {
        std::cout << "Item not found or has been deleted.\n";
    }
}

void InventoryManager::updateItem() {
    std::cout << "\n--- Update Item ---\n";
    int id;
    std::cout << "Enter ID to update: ";
    while (!(std::cin >> id) || id <= 0) {
        std::cout << "Invalid ID. Enter a positive integer: ";
        clearInput();
    }

    Item item;
    if (!get_item(id, &item)) {
        std::cout << "Item not found or has been deleted.\n";
        return;
    }
    
    std::cout << "Item found! Enter new details.\n";
    clearInput();

    std::cout << "Enter New Name: ";
    std::string nameInput;
    while (true) {
        std::getline(std::cin, nameInput);
        if (!nameInput.empty()) {
            std::strncpy(item.name, nameInput.c_str(), sizeof(item.name) - 1);
            item.name[sizeof(item.name) - 1] = '\0';
            break;
        } else {
            std::cout << "Name cannot be empty. Enter Name: ";
        }
    }

    std::cout << "Enter New Quantity (0 or more): ";
    while (!(std::cin >> item.quantity) || item.quantity < 0) {
        std::cout << "Invalid Quantity. Enter 0 or more: ";
        clearInput();
    }

    std::cout << "Enter New Price (0 or more): ";
    while (!(std::cin >> item.price) || item.price < 0) {
        std::cout << "Invalid Price. Enter 0 or more: ";
        clearInput();
    }

    if (update_item(id, item)) {
        std::cout << "Item updated successfully!\n";
    } else {
        std::cout << "Failed to update item.\n";
    }
}

void InventoryManager::deleteItem() {
    std::cout << "\n--- Delete Item ---\n";
    int id;
    std::cout << "Enter ID to delete: ";
    while (!(std::cin >> id) || id <= 0) {
        std::cout << "Invalid ID. Enter a positive integer: ";
        clearInput();
    }

    if (delete_item(id)) {
        std::cout << "Item deleted successfully!\n";
    } else {
        std::cout << "Failed to delete item. It may not exist or is already deleted.\n";
    }
}

void InventoryManager::listAllItems() {
    std::cout << "\n--- List All Items ---\n";
    const int MAX_ITEMS = 1000;
    std::vector<Item> items(MAX_ITEMS);

    int count = list_items(items.data(), MAX_ITEMS);
    if (count == 0) {
        std::cout << "No active items in inventory.\n";
        return;
    }

    items.resize(count);

    // Using std::sort to sort by ID
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.id < b.id;
    });

    printItemHeader();
    for (const auto& item : items) {
        printItem(item);
    }
    std::cout << "Total items: " << count << "\n";
}

void InventoryManager::printItemHeader() {
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(40) << "Name"
              << std::setw(15) << "Quantity"
              << std::setw(15) << "Price" << "\n";
    std::cout << std::string(80, '-') << "\n";
}

void InventoryManager::printItem(const Item& item) {
    std::cout << std::left << std::setw(10) << item.id
              << std::setw(40) << item.name
              << std::setw(15) << item.quantity
              << std::fixed << std::setprecision(2) << std::setw(15) << item.price << "\n";
}

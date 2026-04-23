#include "InventoryManager.h"
#include <iostream>
#include <limits>

void printMenu() {
    std::cout << "\n=== Hybrid Inventory Manager ===\n";
    std::cout << "1 Add item\n";
    std::cout << "2 View item\n";
    std::cout << "3 Update item\n";
    std::cout << "4 Delete item\n";
    std::cout << "5 List all\n";
    std::cout << "6 Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    InventoryManager manager;
    int choice = 0;

    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                manager.addItem();
                break;
            case 2:
                manager.viewItem();
                break;
            case 3:
                manager.updateItem();
                break;
            case 4:
                manager.deleteItem();
                break;
            case 5:
                manager.listAllItems();
                break;
            case 6:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please enter 1-6.\n";
        }
    }

    return 0;
}

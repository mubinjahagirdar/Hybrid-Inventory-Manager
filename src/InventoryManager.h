#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "../include/inventory.h"
#include <vector>

class InventoryManager {
public:
    InventoryManager();
    ~InventoryManager();

    void addItem();
    void viewItem();
    void updateItem();
    void deleteItem();
    void listAllItems();

private:
    void printItemHeader();
    void printItem(const Item& item);
    void clearInput(); // helper to clear cin buffer
};

#endif // INVENTORY_MANAGER_H

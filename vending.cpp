#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class
class Item {
protected:
    string name;
    double price;
    int stock;

public:
    Item(string name, double price, int stock) : name(name), price(price), stock(stock) {}

    virtual void displayItem() const = 0; // Pure virtual function
    virtual bool dispenseItem() = 0;     // Pure virtual function

    virtual ~Item() {}
};

// Derived Class: RefundableItem (Adheres to LSP)
class RefundableItem : public Item {
public:
    RefundableItem(string name, double price, int stock) : Item(name, price, stock) {}

    void displayItem() const override {
        cout << "Refundable Item: " << name << ", Price: $" << price << ", Stock: " << stock << endl;
    }

    bool dispenseItem() override {
        if (stock > 0) {
            stock--;
            cout << "Dispensing Refundable Item: " << name << endl;
            return true;
        } else {
            cout << "Out of stock!" << endl;
            return false;
        }
    }

    void processRefund() const {
        cout << "Refund processed for: " << name << endl;
    }
};

// Derived Class: NonRefundableItem (Adheres to LSP)
class NonRefundableItem : public Item {
public:
    NonRefundableItem(string name, double price, int stock) : Item(name, price, stock) {}

    void displayItem() const override {
        cout << "Non-Refundable Item: " << name << ", Price: $" << price << ", Stock: " << stock << endl;
    }

    bool dispenseItem() override {
        if (stock > 0) {
            stock--;
            cout << "Dispensing Non-Refundable Item: " << name << endl;
            return true;
        } else {
            cout << "Out of stock!" << endl;
            return false;
        }
    }
};

// ItemManager Class (Handles Items)
class ItemManager {
private:
    Item** items;
    int itemCount;

public:
    ItemManager(Item** itemArray, int count) : itemCount(count) {
        items = new Item*[itemCount];
        for (int i = 0; i < itemCount; i++) {
            items[i] = itemArray[i];
        }
    }

    void displayItems() {
        for (int i = 0; i < itemCount; i++) {
            items[i]->displayItem();
        }
    }

    Item* getItem(int index) {
        if (index >= 0 && index < itemCount) {
            return items[index];
        }
        return nullptr;
    }

    ~ItemManager() {
        for (int i = 0; i < itemCount; i++) {
            delete items[i];
        }
        delete[] items;
    }
};

// VendingMachine Class
class VendingMachine {
private:
    ItemManager* itemManager;
    static int totalItemsDispensed;
    static double totalRevenue;

public:
    VendingMachine(ItemManager* manager) : itemManager(manager) {}

    void selectItem(int itemNumber) {
        Item* item = itemManager->getItem(itemNumber - 1);
        if (item && item->dispenseItem()) {
            totalItemsDispensed++;
            totalRevenue += item->dispenseItem() ? item->getPrice() : 0;
        } else {
            cout << "Invalid selection or out of stock!" << endl;
        }
    }

    static void displayStats() {
        cout << "Total items dispensed: " << totalItemsDispensed << endl;
        cout << "Total revenue: $" << totalRevenue << endl;
    }
};

int VendingMachine::totalItemsDispensed = 0;
double VendingMachine::totalRevenue = 0.0;

int main() {
    // Create Items
    Item* items[] = {
        new RefundableItem("Refundable Chips", 1.50, 10),
        new NonRefundableItem("Non-Refundable Soda", 1.25, 8)};

    ItemManager* manager = new ItemManager(items, 2);
    VendingMachine vendingMachine(manager);

    cout << "Available items:" << endl;
    manager->displayItems();

    cout << "\nSelecting item:" << endl;
    vendingMachine.selectItem(1); // Dispenses Refundable Item
    vendingMachine.selectItem(2); // Dispenses Non-Refundable Item

    cout << "\nStats:" << endl;
    VendingMachine::displayStats();

    delete manager;

    return 0;
}

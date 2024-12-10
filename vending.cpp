#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract Base class
class Item {
protected:
    string name;
    double price;
    int stock;

public:
    Item(string name, double price, int stock) 
        : name(name), price(price), stock(stock) {}

    virtual void displayItem() const = 0; // Pure virtual function

    virtual bool dispenseItem() {
        if (stock > 0) {
            stock--;
            cout << "Dispensing " << name << endl;
            return true;
        } else {
            cout << "Out of stock!" << endl;
            return false;
        }
    }

    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void restock(int amount) { stock += amount; }
};

// Derived class: Snack
class Snack : public Item {
public:
    Snack(string name, double price, int stock) 
        : Item(name, price, stock) {}

    void displayItem() const override {
        cout << "Snack: " << name << ", Price: $" << price 
             << ", Stock: " << stock << endl;
    }
};

// Derived class: Beverage
class Beverage : public Item {
public:
    Beverage(string name, double price, int stock) 
        : Item(name, price, stock) {}

    void displayItem() const override {
        cout << "Beverage: " << name << ", Price: $" << price 
             << ", Stock: " << stock << endl;
    }
};

// New class: ItemManager (SRP)
class ItemManager {
private:
    vector<Item*> items;

public:
    void addItem(Item* item) {
        items.push_back(item);
    }

    void displayItems() {
        for (size_t i = 0; i < items.size(); i++) {
            cout << i + 1 << ". ";
            items[i]->displayItem();
        }
    }

    Item* getItem(int index) {
        if (index >= 0 && index < items.size()) {
            return items[index];
        }
        return nullptr;
    }

    ~ItemManager() {
        for (Item* item : items) {
            delete item;
        }
        cout << "ItemManager memory cleaned up." << endl;
    }
};

// VendingMachine class
class VendingMachine {
private:
    ItemManager& itemManager;
    static int totalItemsDispensed;
    static double totalRevenue;

public:
    VendingMachine(ItemManager& manager) : itemManager(manager) {}

    void selectItem(int itemNumber) {
        Item* selectedItem = itemManager.getItem(itemNumber - 1);
        if (selectedItem) {
            if (selectedItem->dispenseItem()) {
                totalItemsDispensed++;
                totalRevenue += selectedItem->getPrice();
            }
        } else {
            cout << "Invalid item selection!" << endl;
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
    // Creating an ItemManager instance
    ItemManager itemManager;

    // Adding items to the manager
    itemManager.addItem(new Snack("Chips", 1.50, 10));
    itemManager.addItem(new Snack("Chocolate", 2.00, 5));
    itemManager.addItem(new Beverage("Soda", 1.25, 8));

    VendingMachine vendingMachine(itemManager);

    cout << "Available items:" << endl;
    itemManager.displayItems();

    cout << "\nSelecting item:" << endl;
    vendingMachine.selectItem(2);

    cout << "\nAvailable items after selection:" << endl;
    itemManager.displayItems();

    cout << "\nStats:" << endl;
    VendingMachine::displayStats();

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

// Abstract Base class
class Item {
protected:
    string name;
    double price;
    int stock;

public:
    // Constructor
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

// VendingMachine class
class VendingMachine {
private:
    Item** items; // Array of pointers to Item
    int itemCount;
    static int totalItemsDispensed;
    static double totalRevenue;

public:
    VendingMachine(Item** itemArray, int count) 
        : items(itemArray), itemCount(count) {}

    void displayItems() {
        for (int i = 0; i < itemCount; i++) {
            items[i]->displayItem(); // Polymorphic call
        }
    }

    void selectItem(int itemNumber) {
        if (itemNumber > 0 && itemNumber <= itemCount) {
            if (items[itemNumber - 1]->dispenseItem()) {
                totalItemsDispensed++;
                totalRevenue += items[itemNumber - 1]->getPrice();
            }
        } else {
            cout << "Invalid item selection!" << endl;
        }
    }

    static void displayStats() {
        cout << "Total items dispensed: " << totalItemsDispensed << endl;
        cout << "Total revenue: $" << totalRevenue << endl;
    }

    ~VendingMachine() {
        for (int i = 0; i < itemCount; i++) {
            delete items[i];
        }
        delete[] items;
        cout << "VendingMachine memory cleaned up." << endl;
    }
};

int VendingMachine::totalItemsDispensed = 0;
double VendingMachine::totalRevenue = 0.0;

int main() {
    // Creating snack and beverage items
    Item* snack1 = new Snack("Chips", 1.50, 10);
    Item* snack2 = new Snack("Chocolate", 2.00, 5);
    Item* beverage1 = new Beverage("Soda", 1.25, 8);

    Item* items[] = {snack1, snack2, beverage1};

    VendingMachine* vendingMachine = new VendingMachine(items, 3);

    cout << "Available items:" << endl;
    vendingMachine->displayItems();

    cout << "\nSelecting item:" << endl;
    vendingMachine->selectItem(2);

    cout << "\nAvailable items after selection:" << endl;
    vendingMachine->displayItems();

    cout << "\nStats:" << endl;
    VendingMachine::displayStats();

    delete vendingMachine;

    return 0;
}

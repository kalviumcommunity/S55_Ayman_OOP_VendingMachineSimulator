#include <iostream>
#include <string>
using namespace std;

// Base class
class Item {
private:
    string name;
    double price;
    int stock;

public:
    // Constructor Overloading (Compile-Time Polymorphism)
    Item() : name(""), price(0.0), stock(0) {} // Default constructor

    Item(string name, double price, int stock) { // Parameterized constructor
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    // Accessors (getters) and mutators (setters)
    string getName() const { return name; }
    void setName(string name) { this->name = name; }

    double getPrice() const { return price; }
    void setPrice(double price) { this->price = price; }

    int getStock() const { return stock; }
    void setStock(int stock) { this->stock = stock; }

    // Function Overloading (Compile-Time Polymorphism)
    void displayItem() {
        cout << "Item: " << name << ", Price: $" << price << ", Stock: " << stock << endl;
    }

    void displayItem(bool detailed) {
        if (detailed) {
            cout << "Detailed View - Item Name: " << name << ", Price: $" << price 
                 << ", Stock Available: " << stock << endl;
        } else {
            displayItem();
        }
    }

    bool dispenseItem() {
        if (stock > 0) {
            stock--;
            cout << "Dispensing " << name << endl;
            return true;
        } else {
            cout << "Out of stock!" << endl;
            return false;
        }
    }
};

// Derived class: Snack (Single Inheritance)
class Snack : public Item {
public:
    Snack(string name, double price, int stock) : Item(name, price, stock) {}
    void displaySnack() {
        cout << "Snack: ";
        displayItem();
    }
};

// Derived class: Beverage (Hierarchical Inheritance)
class Beverage : public Item {
public:
    Beverage(string name, double price, int stock) : Item(name, price, stock) {}
    void displayBeverage() {
        cout << "Beverage: ";
        displayItem();
    }
};

// VendingMachine class
class VendingMachine {
private:
    Item* items;
    int itemCount;
    static int totalItemsDispensed;
    static double totalRevenue;

public:
    VendingMachine(Item* itemArray, int count) {
        itemCount = count;
        items = new Item[itemCount];
        for (int i = 0; i < itemCount; i++) {
            items[i] = itemArray[i];
        }
    }

    void displayItems() {
        for (int i = 0; i < itemCount; i++) {
            cout << i + 1 << ". ";
            items[i].displayItem();
        }
    }

    void selectItem(int itemNumber) {
        if (itemNumber > 0 && itemNumber <= itemCount) {
            if (items[itemNumber - 1].dispenseItem()) {
                totalItemsDispensed++;
                totalRevenue += items[itemNumber - 1].getPrice();
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
        delete[] items;
        cout << "VendingMachine memory cleaned up." << endl;
    }
};

int VendingMachine::totalItemsDispensed = 0;
double VendingMachine::totalRevenue = 0.0;

int main() {
    // Creating snack and beverage items
    Snack snack1("Chips", 1.50, 10);
    Snack snack2("Chocolate", 2.00, 5);
    Beverage beverage1("Soda", 1.25, 8);

    Item items[] = {snack1, snack2, beverage1};

    VendingMachine* vendingMachine = new VendingMachine(items, 3);

    cout << "Available items:" << endl;
    vendingMachine->displayItems();

    cout << "\nSelecting item:" << endl;
    vendingMachine->selectItem(2);

    cout << "\nAvailable items after selection:" << endl;
    vendingMachine->displayItems();

    cout << "\nDetailed view of item 1:" << endl;
    items[0].displayItem(true); // Using overloaded function

    cout << "\nStats:" << endl;
    VendingMachine::displayStats();

    delete vendingMachine;

    return 0;
}

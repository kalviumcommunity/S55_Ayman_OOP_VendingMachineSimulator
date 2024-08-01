#include<iostream>
#include<string>
using namespace std;

class Item {
private:
    string name;
    double price;
    int stock;

public:
    Item(string name, double price, int stock) {
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    void displayItem() {
        cout << "Item: " << this->name << ", Price: " << this->price << ", Stock: " << this->stock << endl;
    }

    bool dispenseItem() {
        if (this->stock > 0) {
            this->stock--;
            cout << "Dispensing " << this->name << endl;
            return true;
        } else {
            cout << "Out of stock!" << endl;
            return false;
        }
    }
};

class VendingMachine {
private:
    Item item;

public:
    VendingMachine(Item vendingItem) : item(vendingItem) {}

    void displayItems() {
        item.displayItem();
    }

    void selectItem() {
        item.dispenseItem();
    }
};

int main() {
    Item snack("Chips", 1.50, 10);
    VendingMachine vendingMachine(snack);

    cout << "Available items:" << endl;
    vendingMachine.displayItems();

    cout << "\nSelecting item:" << endl;
    vendingMachine.selectItem();

    cout << "\nAvailable items after selection:" << endl;
    vendingMachine.displayItems();

    return 0;
}

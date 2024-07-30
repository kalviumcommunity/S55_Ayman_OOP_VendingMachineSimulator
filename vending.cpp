#include <iostream>
#include <string>
using namespace std;

class Item {
private:
    string name;
    double price;
    int stock;

public:
    Item(string itemName, double itemPrice, int itemStock) {
        name = itemName;
        price = itemPrice;
        stock = itemStock;
    }

    void displayItem() {
        cout << "Item: " << name << ", Price: " << price << ", Stock: " << stock << endl;
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

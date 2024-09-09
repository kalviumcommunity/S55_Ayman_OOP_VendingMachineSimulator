#include<iostream>
#include<string>
using namespace std;

class Item {
private:
    string name;
    double price;
    int stock;

public:

    Item(){
        name="";
        price=0.0;
        stock=0;
    }

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
    Item items[3];

public:
    VendingMachine(Item itemArray[]) {
        for (int i = 0; i < 3; i++) {
            items[i] = itemArray[i];
        }
    }

    void displayItems() {
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". ";
            items[i].displayItem();
        }
    }

    void selectItem(int itemNumber) {
        if (itemNumber > 0 && itemNumber <= 3) {
            items[itemNumber - 1].dispenseItem();
        } else {
            cout << "Invalid item selection!" << endl;
        }
    }
};

int main() {

    Item snack1("Chips", 1.50, 10);
    Item snack2("Chocolate", 2.00, 5);
    Item snack3("Soda", 1.25, 8);

    Item snacks[] = {snack1, snack2, snack3};

    VendingMachine vendingMachine(snacks);

    cout << "Available items:" << endl;
    vendingMachine.displayItems();

    cout << "\nSelecting item:" << endl;
    vendingMachine.selectItem(2);

    cout << "\nAvailable items after selection:" << endl;
    vendingMachine.displayItems();

    return 0;
}

#include<iostream>
#include<string>
using namespace std;

class Item {
protected:
    string name;
    double price;
    int stock;

public:
    Item(string itemName, double itemPrice, int itemStock) {
        this->name = itemName;
        this->price = itemPrice;
        this->stock = itemStock;
    }

    virtual void displayItem() = 0;
    virtual bool dispenseItem() = 0;

    string getName(){
         return name; 
         }
    double getPrice(){ 
        return price;
         }
    int getStock(){
         return stock; 
         }

};

class Snack : public Item {
public:
    Snack(string itemName, double itemPrice, int itemStock)
        : Item(itemName, itemPrice, itemStock) {}

    
    void displayItem() override {
        cout << "Snack: " << this->name << ", Price: " << this->price << ", Stock: " << this->stock << endl;
    }

    bool dispenseItem() override {
        if (this->stock > 0) {
            this->stock--;
            cout << "Dispensing snack: " << this->name << endl;
            return true;
        } else {
            cout << "Out of stock!" << endl;
            return false;
        }
    }
};

class Beverage : public Item {
public:
    Beverage(string itemName, double itemPrice, int itemStock)
        : Item(itemName, itemPrice, itemStock) {}

    void displayItem() override {
        cout << "Beverage: " << this->name << ", Price: " << this->price << ", Stock: " << this->stock << endl;
    }

    bool dispenseItem() override {
        if (this->stock > 0) {
            this->stock--;
            cout << "Dispensing beverage: " << this->name << endl;
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

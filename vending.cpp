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

    double getPrice() const {
        return price;
    }
};

class VendingMachine {
private:
    Item* items; // Pointer to a dynamically allocated array of Item objects
    int itemCount; // Number of items in the vending machine
    static int totalItemsDispensed;
    static double totalRevenue;

public:
    // Constructor with dynamic memory allocation for items
    VendingMachine(Item* itemArray, int count) {
        itemCount = count;
        items = new Item[itemCount]; // Allocate memory for the array of Item objects
        for (int i = 0; i < itemCount; i++) {
            items[i] = itemArray[i]; // Copy the content of each Item into the array
        }
    }

    void displayItems() {
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". ";
            items[i].displayItem();
        }
    }

    void selectItem(int itemNumber) {
        if (itemNumber > 0 && itemNumber <= itemCount) {
            if (items[itemNumber - 1].dispenseItem()) {
                totalItemsDispensed++; // Increment total items dispensed
                totalRevenue += items[itemNumber - 1].getPrice(); // Add item price to total revenue
            }
        }else {
            cout << "Invalid item selection!" << endl;
        }
    }

    void displayStats() {
        cout << "Total items dispensed: " << totalItemsDispensed << endl;
        cout << "Total revenue: $" << totalRevenue << endl;
    }

    // Destructor to deallocate dynamic memory
    ~VendingMachine() {
        delete[] items; // Deallocate the array of Item objects
        cout << "VendingMachine memory cleaned up." << endl;
    }
};

int VendingMachine::totalItemsDispensed = 0;
double VendingMachine::totalRevenue = 0.0;

int main() {

    Item snack1("Chips", 1.50, 10);
    Item snack2("Chocolate", 2.00, 5);
    Item snack3("Soda", 1.25, 8);

    Item snacks[] = {snack1, snack2, snack3};

    VendingMachine* vendingMachine = new VendingMachine(snacks, 3);   

    cout << "Available items:" << endl;
    vendingMachine->displayItems();

    cout << "\nSelecting item:" << endl;
    vendingMachine->selectItem(2);

    cout << "\nAvailable items after selection:" << endl;
    vendingMachine->displayItems();

    cout<<"\n";
    cout<<"\nStats:"<<endl;
    vendingMachine->displayStats();

    delete vendingMachine;  // Calls VendingMachine destructor to deallocate memory

    return 0;
}

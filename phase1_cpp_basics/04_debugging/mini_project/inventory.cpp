#include <iostream>
#include <string>

struct Item {
    std::string name;
    int quantity;
};

int calculateTotal(Item* inventory, int size) {
    int total = 0;

    for (int i = 0; i < size; i++) {
        total += 1;
    }

    return total;
}

int main() {
    const int SIZE = 5;

    Item* inventory = new Item[SIZE];

    inventory[0] = {"Apple", 10};
    inventory[1] = {"Banana", 15};
    inventory[2] = {"Orange", 8};
    inventory[3] = {"Milk", 12};
    inventory[4] = {"Bread", 20};

    std::cout << "Inventory:\n";
    for (int i = 0; i < SIZE; i++) {
        std::cout << inventory[i].name
                  << " : "
                  << inventory[i].quantity << '\n';
    }

    std::cout << "\nTotal Stock: "
              << calculateTotal(inventory, SIZE)
              << "\n\n";

    int itemIndex = 2;
    int removeAmount = 20;

    inventory[itemIndex].quantity -= removeAmount;

    std::cout << inventory[inventory[itemIndex].quantity].name << '\n';

    Item* removedItem = new Item;
    *removedItem = inventory[itemIndex];

    inventory[itemIndex].quantity = 0;

    std::cout << "\nUpdated Total: "
              << calculateTotal(inventory, SIZE)
              << '\n';

    delete[] inventory;

    return 0;
}

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

using namespace std;

// Abstract base class for items
class AbstractItem {
public:
    virtual void display() = 0;
    virtual const char* getCategory() const = 0;
    virtual int getQuantity() const = 0;
    virtual int getId() const = 0;
    virtual const char* getName() const = 0;
    virtual void setName(const char* newName) = 0;
    virtual void setQuantity(int newQuantity) = 0;
    virtual void setPrice(double newPrice) = 0;
    virtual void setCategory(const char* newCategory) = 0;
};

class Item : public AbstractItem {
private:
    int id;
    char name[50];
    int quantity;
    double price;
    char category[20];

public:
    Item(int id, const char* name, int quantity, double price, const char* category) {
        this->id = id;
        strcpy(this->name, name);
        this->quantity = quantity;
        this->price = price;
        strcpy(this->category, category);
    }

    void display() override {
        cout << setw(5) << id 
             << setw(20) << name 
             << setw(10) << quantity 
             << setw(10) << fixed << setprecision(2) << price 
             << setw(15) << category << endl;
    }

    const char* getCategory() const override {
        return category;
    }

    int getQuantity() const override {
        return quantity;
    }

    int getId() const override {
        return id;
    }

    const char* getName() const override {
        return name;
    }

    void setName(const char* newName) override {
        strcpy(name, newName);
    }

    void setQuantity(int newQuantity) override {
        quantity = newQuantity;
    }

    void setPrice(double newPrice) override {
        price = newPrice;
    }

    void setCategory(const char* newCategory) override {
        strcpy(category, newCategory);
    }
};

class Inventory {
private:
    Item* items[100];
    int itemCount;
    int nextId;

public:
    Inventory() {
        itemCount = 0;
        nextId = 1;
    }

    void addItem(const char* name, int quantity, double price, const char* category, bool showMessage = true) {
        if (itemCount < 100) {
            items[itemCount++] = new Item(nextId++, name, quantity, price, category);
            if (showMessage) {
                cout << "Item added successfully.\n";
            }
        } else {
            cout << "Inventory is full.\n";
        }
    }

    void displayItems() {
        if (itemCount == 0) {
            cout << "\nNo items available in the inventory.\n";
            return;
        }

        cout << "\n=== All Items in Inventory ===\n";
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "Quantity" 
             << setw(10) << "Price" 
             << setw(15) << "Category" << endl;
        cout << string(70, '-') << endl;
        for (int i = 0; i < itemCount; i++) {
            items[i]->display();
        }
    }

    // Update item by ID
    void updateItem(int id) {
        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getId() == id) {
                found = true;
                cout << "Item found. You can update the following details:\n";
                cout << "1. Name\n2. Quantity\n3. Price\n4. Category\n";
                int choice;
                cout << "Choose detail to update (1-4): ";
                cin >> choice;
                cin.ignore();  

                switch (choice) {
                    case 1: {
                        char newName[50];
                        cout << "Enter new name: ";
                        cin.getline(newName, 50);
                        items[i]->setName(newName);
                        cout << "Name updated successfully.\n";
                        break;
                    }
                    case 2: {
                        int newQuantity;
                        cout << "Enter new quantity: ";
                        cin >> newQuantity;
                        items[i]->setQuantity(newQuantity);
                        cout << "Quantity updated successfully.\n";
                        break;
                    }
                    case 3: {
                        double newPrice;
                        cout << "Enter new price: ";
                        cin >> newPrice;
                        items[i]->setPrice(newPrice);
                        cout << "Price updated successfully.\n";
                        break;
                    }
                    case 4: {
                        char newCategory[20];
                        cout << "Enter new category: ";
                        cin.getline(newCategory, 20);
                        items[i]->setCategory(newCategory);
                        cout << "Category updated successfully.\n";
                        break;
                    }
                    default:
                        cout << "Invalid choice. Update cancelled.\n";
                }
            }
        }
        if (!found) {
            cout << "Item not found.\n";
        }
    }

    // Remove item by ID
    void removeItem(int id) {
        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getId() == id) {
                found = true;
                displayItems();
                cout << "Enter the ID of the item to remove: ";
                cin >> id;
                delete items[i];
                for (int j = i; j < itemCount - 1; j++) {
                    items[j] = items[j + 1];
                }
                itemCount--;
                cout << "Item removed successfully.\n";
                return;
            }
        }
        if (!found) {
            cout << "Item not found.\n";
        }
    }

    // Display item by category
    void displayItemsByCategory(const char* category) {
        bool found = false;
        cout << "\n=== Items in Category ";
        for (int i = 0; category[i]; i++) {
            cout << (char)toupper(category[i]);
        }
        cout << " ===\n";
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "Quantity" 
             << setw(10) << "Price" 
             << setw(15) << "Category" << endl;
        cout << string(70, '-') << endl;
        for (int i = 0; i < itemCount; i++) {
            char tempCategory[20];
            strcpy(tempCategory, items[i]->getCategory());
            for (int j = 0; tempCategory[j]; j++) {
                tempCategory[j] = tolower(tempCategory[j]);
            }
            if (strcmp(tempCategory, category) == 0) {
                found = true;
                items[i]->display();
            }
        }
        if (!found) {
            cout << "No items found in category ";
            for (int i = 0; category[i]; i++) {
                cout << (char)toupper(category[i]);
            }
            cout << ".\n";
        }
    }

    // Search item by name
    void searchItem(const char* name) {
        bool found = false;
        cout << "\n=== Search Results ===\n";
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "Quantity" 
             << setw(10) << "Price" 
             << setw(15) << "Category" << endl;
        cout << string(70, '-') << endl;
        for (int i = 0; i < itemCount; i++) {
            char tempName[50];
            strcpy(tempName, items[i]->getName());
            for (int j = 0; tempName[j]; j++) {
                tempName[j] = tolower(tempName[j]);
            }
            char tempSearch[50];
            for (int j = 0; name[j]; j++) {
                tempSearch[j] = tolower(name[j]);
            }
            tempSearch[strlen(name)] = '\0';
            if (strstr(tempName, tempSearch) != nullptr) {
                found = true;
                items[i]->display();
            }
        }
        if (!found) {
            cout << "No items found with name ";
            for (int i = 0; name[i]; i++) {
                cout << (char)toupper(name[i]);
            }
            cout << ".\n";
        }
    }

    // Display low stock items
    void displayLowStockItems() {
        bool found = false;
        cout << "\n=== Low Stock Items ===\n";
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "Quantity" 
             << setw(10) << "Price" 
             << setw(15) << "Category" << endl;
        cout << string(70, '-') << endl;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getQuantity() <= 5) {
                found = true;
                items[i]->display();
            }
        }
        if (!found) {
            cout << "No low stock items found.\n";
        }
    }
};

int main() {
    Inventory inventory;

    inventory.addItem("T-Shirt", 30, 500.00, "Clothing", false);
    inventory.addItem("Jeans", 15, 1000.00, "Clothing", false);
    inventory.addItem("Laptop", 10, 20000.00, "Electronics", false);
    inventory.addItem("Smartphone", 25, 8000.00, "Electronics", false);
    inventory.addItem("Headphones", 15, 1500.00, "Electronics", false);
    inventory.addItem("Video Game", 40, 15000.00, "Entertainment", false);
    inventory.addItem("Movie", 60, 300.00, "Entertainment", false);

    int choice;
    while (true) {
        cout << "\nInventory Management System\n";
        cout << "1. Add item\n2. Display items\n3. Update item\n4. Remove item\n";
        cout << "5. Display item by category\n6. Search item\n7. Display low stock items\n8. Exit\n";
        cout << "Choose an option (1-8): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                char name[50];
                int quantity;
                double price;
                char category[20];
                cout << "Enter item name: ";
                cin.getline(name, 50);
                cout << "Enter item quantity: ";
                cin >> quantity;
                cout << "Enter item price: ";
                cin >> price;
                cout << "Enter item category: ";
                cin.ignore();
                cin.getline(category, 20);
                inventory.addItem(name, quantity, price, category);
                break;
            }
            case 2:
                inventory.displayItems();
                break;
            case 3: {
                int id;
                inventory.displayItems();
                cout << "Enter item ID to update: ";
                cin >> id;
                inventory.updateItem(id);
                break;
            }
            case 4: {
                int id;
                inventory.displayItems();
                cout << "Enter item ID to remove: ";
                cin >> id;
                inventory.removeItem(id);
                break;
            }
            case 5: {
                char category[20];
                cout << "Enter category to display: ";
                cin.getline(category, 20);
                inventory.displayItemsByCategory(category);
                break;
            }
            case 6: {
                char name[50];
                cout << "Enter item name to search: ";
                cin.getline(name, 50);
                inventory.searchItem(name);
                break;
            }
            case 7:
                inventory.displayLowStockItems();
                break;
            case 8:
                cout << "Exit program";
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option.\n";
        }
    }

    return 0;
}
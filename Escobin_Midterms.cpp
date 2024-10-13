
#include <iostream>
#include <iomanip> 
#include <cstring>
#include <cctype>  
using namespace std;

class Item {
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

    void display() {
        cout << setw(5) << id 
             << setw(20) << name 
             << setw(10) << quantity 
             << setw(10) << fixed << setprecision(2) << price 
             << setw(15) << category << endl;
    }

    const char* getCategory() const {
        return category;
    }

    int getQuantity() const {
        return quantity;
    }

    int getId() const {
        return id;
    }

    const char* getName() const {
        return name;
    }

    void setName(const char* newName) {
        strcpy(name, newName);
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    void setCategory(const char* newCategory) {
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
                        cin.ignore();
                        cin.getline(newCategory, 20);
                        items[i]->setCategory(newCategory);
                        cout << "Category updated successfully.\n";
                        break;
                    }
                    default:
                        cout << "Invalid choice. Update canceled.\n";
                }
                break;
            }
        }
        if (!found) {
            cout << "No item found with ID " << id << ".\n";
        }
    }

    void removeItem(int id) {
        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getId() == id) {
                delete items[i]; 
                for (int j = i; j < itemCount - 1; j++) {
                    items[j] = items[j + 1];
                }
                itemCount--;
                found = true;
                cout << "Item with ID " << id << " has been removed successfully.\n";
                break;
            }
        }
        if (!found) {
            cout << "No item found with ID " << id << ".\n";
        }
    }

    bool caseInsensitiveCompare(const char* str1, const char* str2) {
        while (*str1 && *str2) {
            if (tolower(*str1) != tolower(*str2)) {
                return false;
            }
            str1++;
            str2++;
        }
        return *str1 == *str2;
    }

    void displayItemsByCategory(const char* category) {
        cout << "\n=== Items in " << category << " Category ===\n";
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "Quantity" 
             << setw(10) << "Price" 
             << setw(15) << "Category" << endl;
        cout << string(70, '-') << endl;
        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (caseInsensitiveCompare(items[i]->getCategory(), category)) {
                items[i]->display();
                found = true;
            }
        }
        if (!found) {
            cout << "No items found in this category.\n";
        }
    }

    void displayLowStockItems(int limit) {
        cout << "\n=== Low Stock Items (Below " << limit << ") ===\n";
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "Quantity" 
             << setw(10) << "Price" 
             << setw(15) << "Category" << endl;
        cout << string(70, '-') << endl;
        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->getQuantity() < limit) {
                items[i]->display();
                found = true;
            }
        }
        if (!found) {
            cout << "No low stock items found.\n";
        }
    }

    void searchItem(const char* searchTerm) {
        bool found = false;
        cout << "\n=== Search Results for \"" << searchTerm << "\" ===\n";
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(10) << "Quantity" 
             << setw(10) << "Price" 
             << setw(15) << "Category" << endl;
        cout << string(70, '-') << endl;
        for (int i = 0; i < itemCount; i++) {
            if (caseInsensitiveCompare(items[i]->getName(), searchTerm) || to_string(items[i]->getId()) == searchTerm) {
                items[i]->display();
                found = true;
            }
        }
        if (!found) {
            cout << "No item found with the name or ID: \"" << searchTerm << "\".\n";
        }
    }
};

void showMenu() {
    cout << "\n=== Inventory Management System ===\n";
    cout << "1. Add Item\n";
    cout << "2. Update Item\n";
    cout << "3. Remove Item\n";
    cout << "4. Display Items by Category\n";
    cout << "5. Display All Items\n";
    cout << "6. Search Item\n";
    cout << "7. Display Low Stock Items\n";
    cout << "8. Exit\n";
}

int main() {
    Inventory inventory;

    
    inventory.addItem("T-Shirt", 30, 500.00, "Clothing", false);
    inventory.addItem("Jeans", 15, 1000.00, "Clothing", false);
    inventory.addItem("Laptop", 10, 20000.00, "Electronics", false);
    inventory.addItem("Smartphone", 25, 8000.00, "Electronics", false);
    inventory.addItem("Headphones", 15, 1500.00, "Electronics", false);
    inventory.addItem("Video Game", 40, 15000.00, "Entertainment", false);
    inventory.addItem("Movie", 60, 300.00, "Entertainment", false);

    int option;
    do {
        showMenu();
        cout << "Please choose an option (1-8): ";
        cin >> option;

        switch (option) {
            case 1: {
                char name[50], category[20];
                int quantity;
                double price;
                cout << "Enter item name: ";
                cin.ignore();
                cin.getline(name, 50);
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter category: ";
                cin.ignore();
                cin.getline(category, 20);
                inventory.addItem(name, quantity, price, category);
                break;
            }
            case 2: {
                inventory.displayItems(); 
                int id;
                cout << "Enter item ID to update: ";
                cin >> id;
                inventory.updateItem(id);
                break;
            }
            case 3: {
                inventory.displayItems(); 
                int id;
                cout << "Enter item ID to remove: ";
                cin >> id;
                inventory.removeItem(id);
                break;
            }
            case 4: {
                char category[20];
                cout << "Enter category to display: ";
                cin.ignore();
                cin.getline(category, 20);
                inventory.displayItemsByCategory(category);
                break;
            }
            case 5:
                inventory.displayItems();
                break;
            case 6: {
                char searchTerm[50];
                cout << "Enter item name or ID to search: ";
                cin.ignore();
                cin.getline(searchTerm, 50);
                inventory.searchItem(searchTerm);
                break;
            }
            case 7: {
                int limit;
                cout << "Enter low stock limit: ";
                cin >> limit;
                inventory.displayLowStockItems(limit);
                break;
            }
            case 8:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (option != 8);

    return 0;
}

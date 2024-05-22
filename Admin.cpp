#include "Admin.h"
#include <vector>
#include <algorithm> 
#include <string>
#include <unordered_map>
#include "Product.h"
#include "Player.h"
#include <iostream>
#include "Files.h"
using namespace std;

Admin admin;
Files file3;
Admin::Admin() {
    newStoreID = 1;
}

Admin::Admin(string username, string password) {
    adminUsername = username;
    adminPassword = password;
}

int Admin::createProductID(int storeID) {
    if (newProductID.find(storeID) == newProductID.end()) {
        newProductID[storeID] = 1;
    }
    return newProductID[storeID]++;
}

int Admin::generateUniqueSId()
{
    static int id = 1; // Starting ID
    return id++;

}

void Admin::addStore(string storeName) {
    int newStoreID = generateUniqueSId();
    Stores[newStoreID] = storeName;
    cout << "Store " << storeName << " added with ID: " << newStoreID << endl;
}

void Admin::removeStore(int storeID) {

    if (Stores.find(storeID) != Stores.end()) {
        cout << "Store '" << Stores[storeID] << "' with ID " << storeID << " removed." << endl;
        Stores.erase(storeID);
        Products.erase(storeID);
    }
    else {
        cout << "Store with ID " << storeID << " does not exist." << endl;
    }
}

int Admin::generateUniquePId() {
    static int id = 1; // Starting ID
    int newProductId = id;
    while (true) {
        // Check if the generated ID already exists in any store's inventory
        bool exists = false;
        for (const auto& store : Products) {
            if (store.second.find(newProductId) != store.second.end()) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            break; // Unique ID found, exit loop
        }
        else {
            ++id; // Increment the ID and try again
            newProductId = id;
        }
    }
    ++id; // Increment the ID for the next call
    return newProductId;
}


void Admin::updateStore(int storeID, string newName) {

    if (Stores.find(storeID) != Stores.end()) {
        cout << "Store '" << Stores[storeID] << "' with ID " << storeID << " updated to '" << newName << "'." << endl;
        Stores[storeID] = newName;
    }
    else {
        cout << "Store with ID " << storeID << " does not exist." << endl;
    }
}

void Admin::addProduct(int storeID, string productName, double productPrice, list<product>& l, int productquantity, int rate, int numOFrate) {
    
    int productID = createProductID(storeID);
    Products[storeID][productID] = make_pair(productName, productPrice);
    cout << "Product '" << productName << "' added to store with ID " << storeID << " and Product ID " << productID << "." << endl;

    // Add the newly created product to the player's shopping cart
    product newProduct(productID, productName, productPrice, productquantity, storeID, rate, numOFrate); // Set rate and numOFrate to 0 for now
    l.push_back(newProduct);
    file3.Save_products(l);
    
    // Save player data
}

void Admin::updateProduct(int storeID, int productID, string newProductName, double newProductPrice, list <product> l) {
    
    if (Products.find(storeID) != Products.end() && Products[storeID].find(productID) != Products[storeID].end()) {
        cout << "Product '" << Products[storeID][productID].first << "' with ID " << productID << " in store with ID " << storeID << " updated." << endl;
        Products[storeID][productID] = make_pair(newProductName, newProductPrice);
        auto& playerCart = l;
        playerCart.remove_if([productID](const product& p) { return p.id == productID; });

        // Save the updated product data
    }

    else {
        cout << "Product with ID " << productID << " does not exist in store with ID " << storeID << "." << endl;
    }
 
    
}

void Admin::removeProduct(int storeID, int productID) {

    if (Products.find(storeID) != Products.end() && Products[storeID].find(productID) != Products[storeID].end()) {
        cout << "Product '" << Products[storeID][productID].first << "' with ID " << productID << " removed from store with ID " << storeID << "." << endl;
        Products[storeID].erase(productID);
    }
    else {
        cout << "Product with ID " << productID << " does not exist in store with ID " << storeID << "." << endl;
    }
}

void Admin::displayMenu() {
    cout << "===== Admin Menu =====" << endl;
    cout << "1. Add Store" << endl;
    cout << "2. Remove Store" << endl;
    cout << "3. Update Store" << endl;
    cout << "4. Add Product" << endl;
    cout << "5. Remove Product" << endl;
    cout << "6. Update Product" << endl;
    cout << "7. Exit" << endl;
    cout << "======================" << endl;
}

void Admin::adminMenu(list<product>& l) {
    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            string storeName;
            cout << "Enter Store Name: ";
            cin >> storeName;
            addStore(storeName);
            break;
        }
        case 2: {
            int storeID;
            cout << "Enter Store ID to remove: ";
            cin >> storeID;
            removeStore(storeID);
            break;
        }
        case 3: {
            int storeID;
            string newName;
            cout << "Enter Store ID to update: ";
            cin >> storeID;
            cout << "Enter new Store Name: ";
            cin >> newName;
            updateStore(storeID, newName);
            break;
        }
        case 4: {
            int storeID;
            string productName;
            double productPrice;
            int productquantity;
            int rate;
            int numOFrate;
            cout << "Enter Store ID to add product to: ";
            cin >> storeID;
            if (Stores.find(storeID) == Stores.end()) {
                cout << "Store with ID " << storeID << " does not exist." << endl;
                break;
            }
            else {
                cout << "Enter Product Name: ";
                cin >> productName;
                cout << "Enter Product Price: ";
                cin >> productPrice;
                cout << "Enter Product quantity: ";
                cin >> productquantity;
                cout << "Enter Product Rate: ";
                cin >> rate;
                cout << "Enter number of Rate: ";
                cin >> numOFrate;


                // Add the product to the list
                l.emplace_back(createProductID(storeID), productName, productPrice, productquantity, storeID, rate, numOFrate);
                // Add the product to the store
                addProduct(storeID, productName, productPrice, l, productquantity, rate, numOFrate);
                break;
            }
        }

        case 5: {
            int storeID, productID;
            cout << "Enter Store ID to remove product from: ";
            cin >> storeID;
            cout << "Enter Product ID to remove: ";
            cin >> productID;
            // Remove the product from the list
            l.remove_if([storeID, productID](const product& p) { return p.storeid == storeID && p.id == productID; });
            // Remove the product from the store
            removeProduct(storeID, productID);
            break;
        }
        case 6: {
            int storeID, productID;
            string newProductName;
            double newProductPrice;
            cout << "Enter Store ID: ";
            cin >> storeID;
            cout << "Enter Product ID: ";
            cin >> productID;
            cout << "Enter new Product Name: ";
            cin >> newProductName;
            cout << "Enter new Product Price: ";
            cin >> newProductPrice;
            // Update the product in the list
            for (auto& p : l) {
                if (p.storeid == storeID && p.id == productID) {
                    p.name = newProductName;
                    p.price = newProductPrice;
                    break;
                }
            }
            // Update the product in the store
            updateProduct(storeID, productID, newProductName, newProductPrice, l);
            break;
        }
        case 7: {
            return;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
        }
        }
    }
}


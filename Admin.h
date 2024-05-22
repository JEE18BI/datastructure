#pragma once
#include "Person.h"
#include "Product.h"
#include "Player.h"
#include <string>
#include <unordered_map>

class Admin : public Person {
private:
    string adminUsername;
    string adminPassword;

   

    int newStoreID;
  
    unordered_map<int, int> newProductID;

public:
    unordered_map<int, string> Stores;
    unordered_map<int, unordered_map<int, pair<string, double>>> Products;
    Admin();

    Admin(string username, string password);
    int createProductID(int storeID);
    int generateUniqueSId();

    void addStore(string storeName);

    void removeStore(int storeID);

    int generateUniquePId();



    void updateStore(int storeID, string newName);

    void addProduct(int storeID, string productName, double productPrice, list<product>& l, int productquantity, int rate, int numOFrate);



    void updateProduct(int storeID, int productID, string newProductName, double newProductPrice, list<product> l);








    void removeProduct(int storeID, int productID);

    void displayMenu();

    void adminMenu(list<product>& l);

    




};


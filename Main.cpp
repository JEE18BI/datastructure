#include <iostream>

#include <unordered_map>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string>
#include<fstream>
#include <sstream> 
#include "Player.h"
#include "User.h"
#include "Admin.h"
#include "Person.h"

#include "Product.h"

#include "Files.h"

#include "User.h"

using namespace std;






int generateUniqueId();
void signUpUser(unordered_map<string, User>& users);
void signUpPlayer(unordered_map<string, Player>& players);
void loginUser(const unordered_map<string, User>& users);
void loginPlayer(const unordered_map<string, Player>& players);
void loginAdmin(const unordered_map<string, Admin>& admins);

void readProducts(list<product>& Pl, ifstream& products_file);
void writeProducts(const std::list<product>& Plist, ofstream& products_file);
void readPlayers(list<Player>& players, ifstream& playerFile, const::list<product>products);
void writePlayer(const list<Player>& players, ofstream& playerFile);
void readUsers(unordered_map<string, User>& usersmap, list<Player>& players, list<product>& all_products, ifstream& userfile);
void writeUser(const unordered_map<string, User>& usersmap, ofstream& userfile);

list<product> l;
list<product> owned;
list<Player> players_list;
Files file;


int main() {


    unordered_map<string, User> users; // Map to store user information
    unordered_map<string, Player> players; // Map to store player information
    unordered_map<string, Admin> admins; // Map to store admin information
    /*file.load_Users(users,players_list,l); // Function to load user data from file
    file.load_players(players_list,l);*/
    double budget = 80000;

    ifstream products_file("C:\\Users\\janae\\source\\repos\\Test2\\Test2\\Test2PRODUCTSFILE.txt");//use path
    readProducts(l, products_file);
    ifstream players_file("C:\\Users\\janae\\source\\repos\\Test2\\Test2\\PLAYERSFILE.txt");//use path
    readPlayers(players_list, players_file, l);
    ifstream users_file("C:\\Users\\janae\\\source\\repos\\Test2\\Test2\\USERSFILE.txt");//use path
    readUsers(users, players_list, l, users_file);

    ofstream products_file_write("C:\\Users\\janae\\source\\repos\\Test2\\Test2\\Test2PRODUCTSFILE.txt");//use path
    ofstream players_file_write("C:\\Users\\janae\\source\\repos\\Test2\\Test2\\PLAYERSFILE.txt");//use path
    ofstream users_file_write("C:\\Users\\janae\\source\\repos\\Test2\\Test2\\USERSFILE.txt");//use path


    int choice;
    while (true) {

        cout << "Welcome to the login/signup system!" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Log In" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Choose account type to sign up:" << endl;
            cout << "1. User" << endl;
            cout << "2. Player" << endl;
            cout << "3. Admin" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                signUpUser(users);
                break;
            case 2:
                signUpPlayer(players);
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
            break;
        case 2:
            cout << "Choose account type to log in:" << endl;
            cout << "1. User" << endl;
            cout << "2. Player" << endl;
            cout << "3. Admin" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                loginUser(users);
                break;
            case 2:
                loginPlayer(players);
                break;
            case 3:
                loginAdmin(admins);
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
            break;
        case 3:
            cout << "Exiting the program." << endl;

            writeProducts(l, products_file_write);
            writePlayer(players_list, players_file_write);
            writeUser(users, users_file_write);
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }

    file.save_players(players_list);
    file.Save_products(l);

    return 0;
}

// Function to generate a unique ID
int generateUniqueId() {
    static int id = 1000; // Starting ID
    return id++;
}

// Function for user sign up
void signUpUser(unordered_map<string, User>& users) {
    UserCredentials usercredentials = file.loadUserCredentials("User_credentials.txt");
    User newUser;
    cout << "Enter username: ";
    cin >> newUser.username;

    // Check if username is already taken
    if (users.find(newUser.username) != users.end()) {
        cout << "Username already exists! Please choose another username." << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> newUser.password;

    // Generate unique ID for the user
    newUser.id = generateUniqueId();
    cout << "your id is: " << " " << newUser.id << endl;

    // Add user to the map
    users[newUser.username] = newUser;

    cout << "User successfully signed up!" << endl;
    file.saveUserCredentials(newUser.username, newUser.password, newUser.id, "User_credentials.txt");
}

// Function for player sign up
void signUpPlayer(unordered_map<string, Player>& players) {
    Player newPlayer;
    cout << "Enter username: ";
    cin >> newPlayer.username;

    // Check if username is already taken
    if (players.find(newPlayer.username) != players.end()) {
        cout << "Username already exists! Please choose another username." << endl;
        return;
    }

    cout << "Enter password: ";
    cin >> newPlayer.password;
    newPlayer.id = generateUniqueId();
    cout << "your id is: " << " " << newPlayer.id << endl;

    // Add player to the map
    players[newPlayer.username] = newPlayer;

    cout << "Player successfully signed up!" << endl;
    file.savePlayerCredentials(newPlayer.username, newPlayer.password, newPlayer.id, "player_credentials.txt");
}

// Function for admin sign up


// Function for user login

void loginUser(const unordered_map<string, User>& users) {
    UserCredentials usercredentials = file.loadUserCredentials("user_credentials.txt");
    User user;

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if username and password match
    if (usercredentials.username == username && usercredentials.password == password) {
        cout << "User login successful! Welcome, " << usercredentials.username << endl;
        user.UserOptions(players_list, l);
    }
    else {
        cout << "Incorrect username or access code!" << endl;
    }

}



// Function for player login


// Function for admin login
void loginAdmin(const unordered_map<string, Admin>& admins) {


    string username = "admin";
    string password = "admin";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    Admin admin;

    if (username == "admin" && password == "admin") {
        cout << "Admin login successful! Welcome, " << username << endl;
        admin.adminMenu(l);
    }
    else {
        cout << "Incorrect username or access code!" << endl;
    }
    file.Read_products(l);

}


// Function to check if a username and password match stored player credentials
void loginPlayer(const unordered_map<string, Player>& players) {
    PlayerCredentials playercredentials = file.loadPlayerCredentials("player_credentials.txt");
    Player player;
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if username and password match
    if (playercredentials.username == username && playercredentials.password == password) {
        cout << "Player login successful! Welcome, " << playercredentials.username << endl;
        player.playerOptions(l);
        player.setID(playercredentials.id);
    }
    else {
        cout << "Incorrect username or access code!" << endl;
    }





}
/////////////////////////////////////
void readProducts(list<product>& l, ifstream& products_file)
{
    //ifstream products_file_read("products.txt");

    if (!products_file) {
        cerr << "Error: Unable to open products file for reading." << endl;
        return;
    }

    string id_str, name, price_str, num_str, storeid_str, rate_str, numOFrate_str;
    while (getline(products_file, id_str) &&
        getline(products_file, name) &&
        getline(products_file, price_str) &&
        getline(products_file, num_str) &&
        getline(products_file, storeid_str) &&
        getline(products_file, rate_str) &&
        getline(products_file, numOFrate_str))
    {
        int id = stoi(id_str);
        double price = stod(price_str);
        int num = stoi(num_str);
        int storeid = stoi(storeid_str);
        int rate = stoi(rate_str);
        int numOFrate = stoi(numOFrate_str);

        l.push_back(product(id, name, price, num, storeid, rate, numOFrate));
    }

    products_file.close();
    cout << "Products loaded\n";
}
void writeProducts(const std::list<product>& Plist, ofstream& products_file)
{
    for (const auto& prod : Plist) {
        products_file << prod.id << endl;
        products_file << prod.name << endl;
        products_file << prod.price << endl;
        products_file << prod.num << endl;
        products_file << prod.storeid << endl;
        products_file << prod.rate << endl;
        products_file << prod.numOFrate << endl;
    }
}

void readPlayers(list<Player>& players, ifstream& playerFile, const list<product>all_products) {
    if (!playerFile.is_open()) {
        cerr << "Error: Unable to open products file for reading." << endl;
        return;
    }

    string id_str, username, password, rate_str, num_of_ratings_str
        , nusearchNamemOFrate_str, searchName, budgetstr;
    while (getline(playerFile, id_str) &&
        getline(playerFile, username) &&
        getline(playerFile, password) &&
        getline(playerFile, rate_str) &&
        getline(playerFile, num_of_ratings_str) &&
        getline(playerFile, searchName) &&
        getline(playerFile, budgetstr))
    {
        int id = stoi(id_str);
        int rate = stoi(rate_str);
        //int rate = stoi(rate_str);
        int numOFrate = stoi(num_of_ratings_str);
        double budget = stod(budgetstr);
        list<product>owned;
        string temp_s;
        while (getline(playerFile, temp_s) && temp_s != "#")
        {

            cout << "entered loop\n";
            int productid = stoi(temp_s);
            for (const auto& product : all_products)
            {
                if (product.id == productid) {
                    owned.push_back(product);
                    break;
                }
            }
        }


        players.push_back(Player( id ,username, password, rate, numOFrate,searchName, budget, owned));
    }

    playerFile.close();
    cout << "Players loaded\n";

}
void writePlayer(const list<Player>& players, ofstream& playerFile)
{
    for (auto player : players)
    {
        playerFile << player.id << endl;
        playerFile << player.username << endl;
        playerFile << player.password << endl;
        playerFile << player.rate << endl;
        playerFile << player.numOFrate << endl;
        playerFile << player.searchName << endl;
        playerFile << player.budget << endl;
        for (auto players_products : player.owned)
        {
            playerFile << player.id;
        }
        playerFile << "#" << endl;

    }

}

void readUsers(unordered_map<string, User>& usersmap, list<Player>& players, list<product>& all_products, ifstream& userfile) {
    if (!userfile.is_open()) {
        cerr << "Error: Unable to open products file for reading." << endl;
        return;
    }

    string username, password;
    while (getline(userfile, username) &&
        getline(userfile, password))
    {

        list<product>owned;
        string temp_s;
        while (getline(userfile, temp_s) && temp_s != "#")
        {

            cout << "entered loop\n";
            int productid = stoi(temp_s);
            for (const auto& product : all_products)
            {
                if (product.id == productid) {
                    owned.push_back(product);
                    break;
                }
            }
        }


        usersmap[username] = User(username, password, owned);
    }

    userfile.close();
    cout << "Users loaded\n";

}
void writeUser(const unordered_map<string, User>& usersmap, ofstream& userfile)

{
    for (auto user : usersmap)
    {
        userfile << user.first << endl;
        userfile << user.second.password << endl;

        for (auto users_products : user.second.l)
        {
            userfile << users_products.id;
        }
        userfile << "#" << endl;

    }

}

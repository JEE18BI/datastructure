#include "Files.h"
#include "User.h"
#include <map>

void Files::Read_products(list<product>& Pl)
{
    ifstream products_file_read("products.txt");
    if (!products_file_read.is_open()) {
        cerr << "Error: Unable to open products file for reading." << endl;
        return;
    }

    string id_str, name, price_str, num_str, storeid_str, rate_str, numOFrate_str;
    while (getline(products_file_read, id_str) &&
        getline(products_file_read, name) &&
        getline(products_file_read, price_str) &&
        getline(products_file_read, num_str) &&
        getline(products_file_read, storeid_str) &&
        getline(products_file_read, rate_str) &&
        getline(products_file_read, numOFrate_str))
    {
        int id = stoi(id_str);
        double price = stod(price_str);
        int num = stoi(num_str);
        int storeid = stoi(storeid_str);
        int rate = stoi(rate_str);
        int numOFrate = stoi(numOFrate_str);

        Pl.push_back(product(id, name, price, num, storeid, rate, numOFrate));
    }

    products_file_read.close();
}


void Files::Save_products(list<product>& Plist)
{

    ofstream products_file("products.txt");
    for (auto& prod : Plist)
    {
        products_file << prod.id << endl;
        products_file << prod.name << endl;
        products_file << prod.price << endl;
        products_file << prod.num << endl;
        products_file << prod.storeid << endl;
        products_file << prod.rate << endl;
        products_file << prod.numOFrate << endl;
    }
}

void Files::load_players(list<Player>& players, list<product>& l)
{
    ifstream players_file("player.txt");
    if (!players_file.is_open()) {
        cerr << "Error: Unable to open players file for reading." << endl;
        return;
    }

    // Clear existing players list before loading
    players.clear();

    string line;
    while (getline(players_file, line))
    {
        Player player;
        player.username = line;
        getline(players_file, line);
        player.password = line;
        getline(players_file, line);
        player.id = stoi(line);
        getline(players_file, line);
        player.rate = stod(line);
        getline(players_file, line);
        player.numOFrate = stoi(line);

        // Load owned products for the player
        player.owned.clear(); // Clear existing owned products
        while (getline(players_file, line))
        {
            if (line == "#")
                break;
            int productId = stoi(line);
            // Search for the product in the global product list and add it to the player's owned list
            auto it = find_if(l.begin(), l.end(), [productId](const product& prod) { return prod.id == productId; });
            if (it != l.end())
            {
                player.owned.push_back(*it);
            }
        }

        // Add the loaded player to the list
        players.push_back(player);
    }

    players_file.close();
}

void Files::save_players(list<Player>& players)
{
    ofstream players_file("player.txt", std::ios::app); // Open file in append mode
    if (!players_file.is_open()) {
        cerr << "Error: Unable to open players file for writing." << endl;
        return;
    }

    for (const auto& player : players)
    {
        players_file << player.username << endl;
        players_file << player.password << endl;
        players_file << player.id << endl;
        players_file << player.rate << endl;
        players_file << player.numOFrate << endl;

        for (const auto& owned_product : player.owned)
        {
            players_file << owned_product.name << endl;
        }
        players_file << "#" << endl;
        cout << "Players saved to file." << endl;
    }
   
    players_file.close();
}


void Files::savePlayerCredentials(const std::string& username, const std::string& password, int id, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::app); // Open the file in append mode
    if (outFile.is_open()) {
        outFile << "Player Username: " << username << std::endl;
        outFile << "Player Password: " << password << std::endl;
        outFile << "Player ID: " << id << std::endl;
        outFile.close();
        std::cout << "Player credentials saved to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
    }
}

PlayerCredentials Files::loadPlayerCredentials(const std::string& filename)
{
    PlayerCredentials player;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find("Player Username: ") != std::string::npos) {
                player.username = line.substr(line.find(": ") + 2);
            }
            else if (line.find("Player Password: ") != std::string::npos) {
                player.password = line.substr(line.find(": ") + 2);
            }
        }
        inFile.close();
        std::cout << "Player credentials loaded from file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
    }
    return player;

}

UserCredentials Files::loadUserCredentials(const std::string& filename)
{
    UserCredentials user;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.find("User Username: ") != std::string::npos) {
                user.username = line.substr(line.find(": ") + 2);
            }
            else if (line.find("User Password: ") != std::string::npos) {
                user.password = line.substr(line.find(": ") + 2);
            }
        }
        inFile.close();
        std::cout << "User credentials loaded from file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
    }
    return user;
}

void Files::saveUserCredentials(const std::string& username, const std::string& password, int id, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::app); // Open the file in append mode
    if (outFile.is_open()) {
        outFile << "User Username: " << username << std::endl;
        outFile << "User Password: " << password << std::endl;
        outFile << "User ID: " << id << std::endl;
        outFile.close();
        std::cout << "User credentials saved to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
    }
}

void Files::load_Users(unordered_map<string, User> users_map, list<Player> players, list<product> products)
{
    //takes the main players list
    {
        ifstream users("users");

        int id;
        string user_name;
        string password;
        int productid;



        product userproduct;

        string s;

        while (getline(users, s)) {
            id = stoi(s);
            getline(users, s);
            user_name = s;
            getline(users, s);
            password = s;

            while (getline(users, s) && s != "#") {
                productid = stoi(s);
                for (auto product : products)
                {
                    if (product.id == productid) {
                        userproduct = product;
                        products.push_back(userproduct);
                    }
                }
            }


            users_map[user_name] = User(id, user_name, password, products);

        }

    }

}

void Files::save_users(unordered_map<string, User> users) {
    ofstream user_file("users.txt");
    for (auto user : users)
    {
        user_file << user.second.id << endl;
        user_file << user.second.username << endl;
        user_file << user.second.password << endl;

        for (auto product : user.second.l)
        {
            user_file << product.id << endl;
        }
        user_file << "#" << endl;


    }
    cout << "saved to files";




}

void Files::saveOwnedProducts(const std::string& username, const std::list<product>& owned, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::app); // Open the file in append mode
    if (outFile.is_open()) {
        // Write player's username as a separator
        outFile << "Player Username: " << username << std::endl;
        // Write owned products
        for (const auto& prod : owned) {
            outFile << "Product ID: " << prod.id << ", Name: " << prod.name << ", Price: " << prod.price << ", Quantity: " << prod.num << std::endl;
        }
        // Add a separator for multiple players
        outFile << "-------------------------" << std::endl;
        // Close the file
        outFile.close();
        std::cout << "Owned products saved successfully to file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
    }
}

// Function to load player credentials from a file

void Files::loadOwnedProducts(std::list<product>& playerOwnedProducts, const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        std::string currentPlayerUsername;
        std::list<product> currentOwnedProducts;

        while (std::getline(inFile, line)) {
            if (line.find("Player Username:") != std::string::npos) {
                // Skip the "Player Username: " prefix and extract the username
                currentPlayerUsername = line.substr(line.find(":") + 2);
            }
            else if (line.find("Product ID:") != std::string::npos) {
                // Extract product information
                product prod;
                std::string idStr = line.substr(line.find(":") + 2);
                prod.id = std::stoi(idStr);

                // Extract name
                std::getline(inFile, line);
                prod.name = line.substr(line.find(":") + 2);

                // Extract price
                std::getline(inFile, line);
                prod.price = std::stod(line.substr(line.find(":") + 2));

                // Extract quantity
                std::getline(inFile, line);
                prod.num = std::stoi(line.substr(line.find(":") + 2));

                // Add product to the current player's list of owned products
                currentOwnedProducts.push_back(prod);
            }
            else if (line.find("-------------------------") != std::string::npos) {
                // Add the current player's list of owned products to the main list
                playerOwnedProducts.splice(playerOwnedProducts.end(), currentOwnedProducts);
                // Clear the current player's data to prepare for the next player
                currentPlayerUsername.clear();
                currentOwnedProducts.clear();
            }
        }

        inFile.close();
        std::cout << "Owned products loaded successfully from file: " << filename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
    }
}




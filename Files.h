#include <fstream>
#include <sstream>
#include <list>

#include "Product.h"
#include "User.h"
#include "Player.h"
#include <map>
#include <unordered_map>
using namespace std;
struct UserCredentials {
	string username;
	string password;
	int id;
};
struct PlayerCredentials {
	string username;
	string password;
	int id;
};

class Files {
public:
	
	void Read_products(list<product>& Pl);
	void Save_products(list<product>& Plist);
	void load_players(list<Player>&players_list, list<product>&products);
	void save_players(list<Player>& players);
	void savePlayerCredentials(const std::string& username, const std::string& password, int id, const std::string& filename);
	PlayerCredentials loadPlayerCredentials(const std::string& filename);
	UserCredentials loadUserCredentials(const std::string& filename);
	void saveOwnedProducts(const std::string& username, const std::list<product>& owned, const std::string& filename);
	void saveUserCredentials(const std::string& username, const std::string& password, int id, const std::string& filename);
	void load_Users(unordered_map<string, User> users_map, list<Player> players, list<product> products);
	void loadOwnedProducts(std::list<product>& playerOwnedProducts, const std::string& filename);
	void save_users(unordered_map<string, User> users);
	
};
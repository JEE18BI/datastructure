#pragma once
#pragma once


#include <vector>
#include "Person.h"
#include "Product.h"
#include <list>
#include <unordered_map>

class Player : public Person {
public:


	string username;
	string password;
	int id;
	int rate;
	int numOFrate;


	void setID(int pid) { id = pid; }


	double budget = 80000;

	list<product> owned;
	std::string searchName;


	// Function declarations
	Player();
	Player(string pname, string ppassword, int pid, int prate, int pnumOFrate, list<product> powned);
	Player(int pid, const string& pusername, const string& ppassword, int prate, int pnumOFrate, const string& psearchName, double pbudget, const list<product>& powned)
		: id(pid), username(pusername), password(ppassword), rate(prate), numOFrate(pnumOFrate), searchName(psearchName), budget(pbudget), owned(powned) {}


	void playerOptions(list<product> l);
	void buy(std::list<product>& l, double& budget);
	void sell(std::list<product>& l, std::list<product>& owned, double& budget);
	void replace(std::list<product>& l, std::list<product>& owned, double& budget);






	void searchProductByName(std::list<product>& l, const std::string& productName);

	~Player();
private:
	// You could potentially have private member functions here

};



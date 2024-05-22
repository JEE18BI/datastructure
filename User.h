#pragma once

#include "Product.h"
#include "Person.h"
#include<iostream>
#include "Player.h"
#include <list>

using namespace std;
#include <string>

class User : public Person
{
public:
   
    Player player;
  
 
    list <product> l;
   
    

    User();
    User(int Uid, string Uusername, string Upassword, list <product> l);
    User(string Uusername, string Upassword, list <product> l);

    void UserOptions(list <Player> players_list, list <product> l);

    



    

    void ratePlayers(list<Player>& pl);

    void rateProduct(list<product>& l);

    string determineWinner(list<Player>& pl);

};


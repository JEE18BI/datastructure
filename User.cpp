#include "User.h"
#include "Player.h"
#include "Admin.h"
#include "Product.h"
#include <list>
#include "Files.h"
using namespace std;
Files file4;
User::User()
{
}

User::User(int Uid, string Uusername, string Upassword, list<product> l)
{
    Uid = id;
    Uusername = username;
    Upassword = password;
    l = this->l;

}

User::User(string Uusername, string Upassword, list<product> l)
{
    Uusername = username;
    Upassword = password;
    l = this ->l;
}

void User::UserOptions(list <Player> players_list, list <product> l) {
    while (true) {


        cout << "\n user options" << endl;
        cout << "1. Rate Player options" << endl;
        cout << "2. Rate Product options" << endl;
        cout << "3.determine winner" << endl;
        cout << "3. exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            // Call the ratePlayers method on the current User instance
            ratePlayers(players_list);
            return UserOptions(players_list,l);

        case 2:
            // Call the rateProduct method on the current User instance
            rateProduct(l);
            return UserOptions(players_list,l);

        case 3:
            determineWinner(players_list);
            return UserOptions(players_list,l);
            // Implement the functionality to remove rating
            break;
        default:
            cout << "Invalid choice. Please enter again." << endl;
            break;
        }
    }
}

void User::ratePlayers(list<Player>& pl) {
    file4.load_players(pl,l);
    int id;
    string action;

    cout << "the available Players: " << endl;
    for (const auto& play : pl)
    {
        cout << "THE PLAYER ID: " << play.id << " NAME: " << play.username << endl;
        cout << "his decore:" << endl;

        for (const auto& prod : play.owned) {
            cout << prod.name << " ";
        }

    }
    cout << endl;
    cout << "choose the id of the player you want to rate: ";
    cin >> id;
    cout << "Enter action (add/update/remove): ";
    cin >> action;
    for (char& c : action) {
        action = tolower(c);
    }
    auto it = find_if(pl.begin(), pl.end(), [id](const Player& play) { return play.id == id; });
    if (it != pl.end()) {
        double rating;

        if (action == "add") {
            int counter;
            cout << "enter rating from 0 to 5: ";
            cin >> rating;
            while (rating > 5 || rating < 0) {
                cout << "frooom 0 too 5: ";
                cin >> rating;
            }
            if (it->rate == 0) {

                it->rate = (it->rate * it->numOFrate + rating) / (it->numOFrate + 1);
                it->numOFrate++;
                cout << "THE AVERAGE RATE: " << it->rate << endl;
                cout << "THE NUMBER OF RATING: " << it->numOFrate << endl;

            }

        }
        else if (action == "update") {
            cout << "Enter new rating from 0 to 5: ";
            cin >> rating;
            while (rating > 5 || rating < 0) {
                cout << "Rating must be between 0 and 5: ";
                cin >> rating;
            }
            it->rate = (it->rate * it->numOFrate - it->rate + rating) / it->numOFrate;
            cout << "THE AVERAGE RATE: " << it->rate << endl;
            cout << "THE NUMBER OF RATING: " << it->numOFrate << endl;
        }
        else if (action == "remove") {
            it->rate = (it->rate * it->numOFrate - it->rate) / (it->numOFrate - 1);
            it->numOFrate--;
            cout << "THE AVERAGE RATE: " << it->rate << endl;
            cout << "THE NUMBER OF RATING: " << it->numOFrate << endl;
        }
        else {
            cout << "Invalid action." << endl;
        }
    }
    return;
    file4.save_players(pl);

}
void User::rateProduct(list<product>& l) {
    file4.Read_products(l);
    int id;
    string action;
    cout << "The available products: " << endl;

    for (const auto& prod : l) {
        cout << "PRODUCT ID: " << prod.id << ", NAME: " << prod.name << ", PRICE: $" << prod.price << ", QUANTITY: " << prod.num << ", RATE: " << prod.rate << endl;
    }
    cout << endl;
    cout << "Choose the ID of the product you want to rate: ";
    cin >> id;

    cout << "Enter action (add/update/remove): ";
    cin >> action;

    auto it = find_if(l.begin(), l.end(), [id](const product& prod) { return prod.id == id; });
    if (it != l.end()) {
        double rating;

        if (action == "add") {
            cout << "Enter rating from 0 to 5: ";
            cin >> rating;
            while (rating > 5 || rating < 0) {
                cout << "Rating must be between 0 and 5: ";
                cin >> rating;
            }
            if (it->numOFrate == 0) {
                it->rate = rating;
            }
            else {
                it->rate = ((it->rate * it->numOFrate) + rating) / (it->numOFrate + 1);
            }
            it->numOFrate++;
        }
        else if (action == "update") {
            cout << "Enter new rating from 0 to 5: ";
            cin >> rating;
            while (rating > 5 || rating < 0) {
                cout << "Rating must be between 0 and 5: ";
                cin >> rating;
            }
            it->rate = rating;
        }
        else if (action == "remove") {
            if (it->numOFrate > 0) {
                it->rate = ((it->rate * it->numOFrate) - it->rate) / (it->numOFrate - 1);
                it->numOFrate--;
            }
        }
        else {
            cout << "Invalid action." << endl;
            return;
        }

       
        
        cout << "Product rating updated successfully." << endl;
    }
    file4 .Save_products(l);
    return;
}

string User::determineWinner(list<Player>& player_list) {
    double maxRate = 0.0;
    string winner;


    for (const auto& player : player_list) {

        if (player.rate > maxRate) {
            maxRate = player.rate;
            winner = player.username;
        }
    }
    cout << winner;
    return winner;
}






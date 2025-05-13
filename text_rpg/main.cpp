#include <iostream>
#include <string>
#include "headers.h" 
#include <limits>   
#include <ctime>    

using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    string input_player_name{};

    unsigned int weapon_selection{ 0 };
    unsigned int power_selection{ 0 };

    cout << "==========================================" << endl;
    cout << "Welcome to Adventurer's Life!" << endl;
    cout << "==========================================" << endl;

    cout << "Let's create your adventurer!" << endl;
    cout << "Enter your name: ";
    getline(cin, input_player_name);

    if (input_player_name.empty()) {
        input_player_name = "Anonymous Adventurer";
    }
    cout << endl;

    player current_player(input_player_name);

    cout << "==========================================" << endl;
    cout << "Choose your starting weapon:" << endl;
    cout << "==========================================" << endl;
    cout << "1) -Knight's Sword- " << endl;
    cout << "2) -Katana- " << endl;
    cout << "3) -Battle Axe- " << endl;
    cout << "4) -Bow and Arrow- " << endl;
    cout << "Enter the number of your choice: ";

    while (!(cin >> weapon_selection) || weapon_selection < 1 || weapon_selection > 4) {
        cout << "Invalid choice. Enter a number between 1 and 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    current_player.set_weapon_stats_by_choice(weapon_selection);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n==========================================" << endl;
    cout << "Choose your starting power:" << endl;
    cout << "==========================================" << endl;
    cout << "1) -Fireball-" << endl;
    cout << "2) -Poison Attack-" << endl;
    cout << "3) -Critical Focus-" << endl;
    cout << "4) -+10 Health-" << endl;
    cout << "Enter the number of your choice: ";

    while (!(cin >> power_selection) || power_selection < 1 || power_selection > 4) {
        cout << "Invalid choice. Enter a number between 1 and 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    current_player.set_power_stats_by_choice(power_selection);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nVery well, " << current_player.get_player_name() << "! Here are your initial stats:" << endl;
    current_player.display_player_stats();
    cout << endl;

    location game_locations;

    bool game_in_progress = true;

    while (game_in_progress) {
        if (!current_player.is_player_alive()) {
            cout << "\nGAME OVER. " << current_player.get_player_name() << " was defeated." << endl;
            cout << "Press Enter to exit...";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            game_in_progress = false;
            continue;
        }
        visit_city(current_player, game_locations);
    }
    cout << "\nGame ended." << endl;
    return 0;
}
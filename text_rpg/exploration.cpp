#include "headers.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void start_adventure(player& current_player, location& location_object) {
    int chosen_location_number = 0;

    while (current_player.is_player_alive()) {
        cout << "\n==========================================" << endl;
        cout << "Exploration Map" << endl;
        cout << "==========================================" << endl;

        cout << "Choose a place to explore: " << endl;
        cout << "1) The Shadowy Forest" << endl;
        cout << "2) The Ice Peak" << endl;
        cout << "3) The Blighted Desert" << endl;
        cout << "4) Return to City" << endl;
        cout << "\nEnter option: ";

        cin >> chosen_location_number;

        if (cin.fail() || chosen_location_number < 1 || chosen_location_number > 4) {
            cout << "Invalid option. Please enter a number between 1 and 4." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to try again...";
            cin.get();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (chosen_location_number) {
        case 1:
            location_object.explore_forest(current_player);
            break;
        case 2:
            location_object.explore_ice_peak(current_player);
            break;
        case 3:
            location_object.explore_desert(current_player);
            break;
        case 4:
            cout << "\nReturning to the city..." << endl;
            return;
        default:
            break;
        }

        if (!current_player.is_player_alive()) {
            cout << "\nYour journey ends here, in the desolation of this place..." << endl;
            return;
        }
    }
}

void location::explore_forest(player& current_player) {
    string player_choice_string;
    cout << "\n==========================================" << endl;
    cout << "The Shadowy Forest" << endl;
    cout << "==========================================" << endl;
    cout << "The forest is dense and gloomy. You spot a movement..." << endl;
    cout << ".................................(o -- o)" << endl;

    enemy slimy_foe; slimy_foe.set_stats(5, 15, 5, "Gooey Slime");
    enemy ogre_foe; ogre_foe.set_stats(15, 30, 1, "Clearing Ogre");

    int battle_outcome = start_battle(current_player, slimy_foe);
    cout << "(X -- X)" << endl;

    if (!current_player.is_player_alive()) return;

    if (battle_outcome == 1) {
        cout << "\nYou defeated the Slime!" << endl;
        cout << "Do you want to venture deeper into the forest and investigate a suspicious clearing? (Y/N): ";
        cin >> player_choice_string;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (player_choice_string == "Y" || player_choice_string == "y") {
            cout << "\nYou find an Ogre in the clearing!" << endl;
            battle_outcome = start_battle(current_player, ogre_foe);
            if (!current_player.is_player_alive()) return;

            if (battle_outcome == 1) {
                cout << "\nYou have cleared the forest clearing!" << endl;
            }
            else {
                cout << "\nYou fled from the Ogre; the forest still holds dangers." << endl;
            }
        }
        else {
            cout << "\nYou decide you've seen enough of the forest for today." << endl;
        }
    }
    else {
        cout << "\nYou retreat from the forest entrance for now..." << endl;
    }
    cout << "Press Enter to return to the exploration map...";
    cin.get();
}

void location::explore_ice_peak(player& current_player) {
    cout << "\n==========================================" << endl;
    cout << "The Ice Peak" << endl;
    cout << "==========================================" << endl;
    cout << "This area is still under a terrible blizzard. You decide to turn back." << endl;
    cout << "(Area not implemented)" << endl;
    cout << "Press Enter to return to the exploration map...";
    cin.get();
}

void location::explore_desert(player& current_player) {
    cout << "\n==========================================" << endl;
    cout << "The Blighted Desert" << endl;
    cout << "==========================================" << endl;
    cout << "The heat is unbearable, and the sand seems to swallow everything. Better not to proceed." << endl;
    cout << "(Area not implemented)" << endl;
    cout << "Press Enter to return to the exploration map...";
    cin.get();
}
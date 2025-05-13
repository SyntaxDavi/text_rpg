#include "headers.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void visit_potion_shop(player& current_player) {
    cout << "==========================================" << endl;
    cout << "Potion Shop" << endl;
    cout << "==========================================" << endl;
    cout << "You look at the shelves but decide to save your money for now." << endl;

    cout << "Press Enter to return to the city...";
    cin.get();
}

void visit_equipment_shop(player& current_player) {
    cout << "==========================================" << endl;
    cout << "Equipment Shop" << endl;
    cout << "==========================================" << endl;
    cout << "The blacksmith shows you some weapons, but nothing catches your eye today." << endl;

    cout << "Press Enter to return to the city...";
    cin.get();
}

void reset_day(player& current_player) {
    cout << "==========================================" << endl;
    cout << "Resting..." << endl;
    cout << "==========================================" << endl;
    cout << "You find an inn and spend the night." << endl;
    current_player.full_heal_player();

    cout << "You feel refreshed!" << endl;
    cout << "Your current health [" << current_player.get_health_points() << "]" << endl;
    cout << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

void visit_city(player& current_player, location& location_object) {
    int city_menu_choice{ 0 };
    bool proceed_to_explore{ false };

    do {
        cout << "\n==========================================" << endl;
        cout << "Adventurers' City" << endl;
        cout << "==========================================" << endl;

        cout << "What would you like to do?" << endl;
        cout << "1) Potion Shop" << endl;
        cout << "2) Equipment Shop" << endl;
        cout << "3) Rest for the day (Heal)" << endl;
        cout << "4) Show Attributes" << endl;
        cout << "5) Go Exploring" << endl;
        cout << "6) Exit Game" << endl;
        cout << "\nEnter option: ";

        cin >> city_menu_choice;

        if (cin.fail() || city_menu_choice < 1 || city_menu_choice > 6) {
            cout << "Invalid option. Please enter a number between 1 and 6." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to try again...";
            cin.get();
            city_menu_choice = 0;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (city_menu_choice) {
        case 1:
            visit_potion_shop(current_player);
            break;
        case 2:
            visit_equipment_shop(current_player);
            break;
        case 3:
            reset_day(current_player);
            break;
        case 4:
            current_player.display_player_stats();
            cout << "Press Enter to return to the city menu...";
            cin.get();
            break;
        case 5:
            cout << "\nYou prepare for a new adventure!" << endl;
            proceed_to_explore = true;
            break;
        case 6:
            cout << "Thanks for playing! See you next time." << endl;
            exit(0);
        default:
            break;
        }

    } while (!proceed_to_explore);

    if (proceed_to_explore) {
        start_adventure(current_player, location_object);
    }
}
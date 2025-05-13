#include "headers.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

player::player(string name_arg) : player_name_value{ name_arg } {
    equipped_weapon = weapon("Fists", 1);
    equipped_power = power("None", 0);
}

bool player::roll_critical_hit() const {
    int random_roll = rand() % 100;
    return random_roll < get_total_critical_chance();
}

int player::calculate_attack_damage() const {
    int base_damage = equipped_weapon.get_damage();
    if (roll_critical_hit()) {
        return static_cast<int>(base_damage * get_total_critical_multiplier());
    }
    return base_damage;
}

int player::get_health_points() const {
    return health_points;
}

void player::heal_player(int heal_amount) {
    health_points += heal_amount;
    if (health_points > 30) {
        health_points = 30;
    }
    cout << get_player_name() << " recovered " << heal_amount << " health. Current health: " << health_points << endl;
}

weapon player::get_equipped_weapon() const {
    return equipped_weapon;
}

power player::get_equipped_power() const {
    return equipped_power;
}

string player::get_player_name() const {
    return player_name_value;
}

int player::get_dodge_rating() const {
    return dodge_rating;
}

void player::set_dodge_rating(int new_dodge_rating) {
    dodge_rating = new_dodge_rating;
}

void player::display_player_stats() {

    cout << "\n-- Player Attributes --" << endl;
    cout << endl;
    cout << "Name: " << get_player_name() << endl;
    cout << "Current Health: " << get_health_points() << endl;
    cout << "Weapon: " << equipped_weapon.get_name() << " (Base Damage: " << equipped_weapon.get_damage() << ") " << endl;
    if (equipped_weapon.get_critical_chance_bonus() > 0 || equipped_weapon.get_critical_multiplier_bonus() > 0.0) {
        cout << "  Weapon Bonus: +" << equipped_weapon.get_critical_chance_bonus() << "% crit chance, +" << equipped_weapon.get_critical_multiplier_bonus() << "x crit mult." << endl;
    }
    cout << "Power: " << equipped_power.get_name() << endl;
    if (equipped_power.get_critical_chance_bonus() > 0 || equipped_power.get_critical_multiplier_bonus() > 0.0) {
        cout << "  Power Bonus: +" << equipped_power.get_critical_chance_bonus() << "% crit chance, +" << equipped_power.get_critical_multiplier_bonus() << "x crit mult." << endl;
    }
    cout << "Dodge: " << get_dodge_rating() << "%" << endl;
    cout << endl;
    cout << "Total Critical Chance: " << get_total_critical_chance() << "%" << endl;
    cout << "Total Critical Multiplier: " << get_total_critical_multiplier() << endl;
    cout << "-------------------------------------" << endl;

}

void player::set_weapon_stats_by_choice(int weapon_choice) {
    switch (weapon_choice) {
    case 1:
        equipped_weapon = weapon("Knight's Sword", 7, 0, 0.0);
        break;
    case 2:
        equipped_weapon = weapon("Katana", 5, 15, 1.5);
        break;
    case 3:
        equipped_weapon = weapon("Battle Axe", 10, 0, 0.0);
        break;
    case 4:
        equipped_weapon = weapon("Bow and Arrow", 6, 33, 1.8);
        break;
    default:
        cout << "Invalid weapon option... Equipping fists." << endl;
        equipped_weapon = weapon("Fists", 1);
        break;
    }
}

void player::set_power_stats_by_choice(int power_choice) {
    switch (power_choice) {
    case 1:
        equipped_power = power("Fireball", 15, 5, 0.0);
        break;
    case 2:
        equipped_power = power("Poison Attack", 5, 10, 0.2);
        break;
    case 3:
        equipped_power = power("Critical Focus", 0, 25, 0.5);
        break;
    case 4:
        equipped_power = power("+10 Health", 0, 0, 0.0);
        health_points = health_points + 10;
        if (health_points > 30) {
            health_points = 30;
        }
        cout << endl;
        cout << "*==== +10 Health Added ====*" << endl;
        break;
    default:
        cout << "Invalid power option..." << endl;
        equipped_power = power("None", 0);
        break;
    }
}

void player::activate_power() {
    if (!power_used_in_current_battle) {
        power_used_in_current_battle = true;
    }
}

double player::get_total_critical_multiplier() const {
    double total_multiplier = base_critical_multiplier +
        equipped_weapon.get_critical_multiplier_bonus() +
        equipped_power.get_critical_multiplier_bonus();

    if (total_multiplier < 1.0) total_multiplier = 1.0;
    return total_multiplier;
}

int player::get_total_critical_chance() const {
    int total_chance = base_critical_chance +
        equipped_weapon.get_critical_chance_bonus() +
        equipped_power.get_critical_chance_bonus();

    if (total_chance < 0) total_chance = 0;
    if (total_chance > 75) total_chance = 70;
    return total_chance;
}

void player::update_player_name(string& new_player_name) {
    player_name_value = new_player_name;
}

void player::take_damage(int damage_amount) {
    health_points -= damage_amount;
    if (health_points < 0) {
        health_points = 0;
    }
}

bool player::is_player_alive() const {
    return health_points > 0;
}
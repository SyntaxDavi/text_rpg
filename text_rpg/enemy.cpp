#include "headers.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void enemy::set_stats(int new_attack, int new_health, int new_dodge, const string& new_name) {
    attack_power = new_attack;
    health = new_health;
    dodge_chance = new_dodge;
    name = new_name;
}

void enemy::display_stats() {
    cout << "Enemy: " << name << endl;
    cout << "Attack: " << attack_power << endl;
    cout << "Health: " << health << endl;
    cout << "Dodge: " << dodge_chance << endl;
}

void enemy::apply_effect(const active_effect& effect_to_apply) {
    active_effects_list.push_back(effect_to_apply);
    cout << name << " was affected by: " << effect_to_apply.name << " for " << effect_to_apply.turns_remaining << " turns!" << endl;
    cout << endl;
}

void enemy::process_effects() {
    for (auto it = active_effects_list.begin(); it != active_effects_list.end(); ) {
        health -= it->damage_per_turn;
        cout << name << " took " << it->damage_per_turn << " damage from " << it->name << ". Remaining health: " << health << endl;
        cout << endl;
        it->turns_remaining--;

        if (it->turns_remaining <= 0) {
            cout << it->name << " has worn off." << endl;
            it = active_effects_list.erase(it);
        }
        else {
            ++it;
        }
    }
}

void enemy::take_damage(int damage_amount) {
    health -= damage_amount;
    if (health < 0) {
        health = 0;
    }
}

bool enemy::is_alive() const {
    return health > 0;
}

int enemy::get_health() const {
    return health;
}
int enemy::get_dodge_chance() const {
    return dodge_chance;
}
int enemy::get_attack_power() const {
    return attack_power;
}
string enemy::get_name() const {
    return name;
}
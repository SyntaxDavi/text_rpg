#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class player;
class enemy;
class location;

void start_adventure(player& current_player, location& location_object);
int start_battle(player& current_player, enemy& enemy_opponent);
void visit_city(player& current_player, location& location_object);
void visit_potion_shop(player& current_player);
void visit_equipment_shop(player& current_player);
void reset_day(player& current_player);

class power {
private:
    string name;
    int damage;
    int critical_chance_bonus;
    double critical_multiplier_bonus;

public:
    power(string initial_name = "Unknown Power", int initial_damage = 0, int initial_crit_chance_bonus = 0, double initial_crit_multiplier_bonus = 0.0)
        : name{ initial_name }, damage{ initial_damage }, critical_chance_bonus{ initial_crit_chance_bonus }, critical_multiplier_bonus{ initial_crit_multiplier_bonus } {
    }

    string get_name() const;
    int get_damage() const;
    int get_critical_chance_bonus() const;
    double get_critical_multiplier_bonus() const;

    void set_name(const string& new_name);
    void set_damage(int new_damage);
    void set_critical_chance_bonus(int new_crit_chance_bonus);
    void set_critical_multiplier_bonus(double new_crit_multiplier_bonus);
};

class weapon {
private:
    string name;
    int damage;
    int critical_chance_bonus;
    double critical_multiplier_bonus;

public:
    weapon(string initial_name = "Unknown Weapon", int initial_damage = 0, int initial_crit_chance_bonus = 0, double initial_crit_multiplier_bonus = 0.0)
        : name{ initial_name }, damage{ initial_damage }, critical_chance_bonus{ initial_crit_chance_bonus }, critical_multiplier_bonus{ initial_crit_multiplier_bonus } {
    }

    string get_name() const;
    int get_damage() const;
    int get_critical_chance_bonus() const;
    double get_critical_multiplier_bonus() const;

    void set_critical_chance_bonus(int new_crit_chance_bonus);
    void set_critical_multiplier_bonus(double new_crit_multiplier_bonus);
    void set_name(const string& new_name);
    void set_damage(int new_damage);
};

struct active_effect {
    string name;
    int damage_per_turn;
    int turns_remaining;
};

class enemy {
private:
    int attack_power{ 0 };
    int health{ 0 };
    int dodge_chance{ 0 };
    string name{ "Default Enemy" };
    vector<active_effect> active_effects_list;

public:
    void set_stats(int new_attack, int new_health, int new_dodge, const string& new_name);
    void display_stats();
    void apply_effect(const active_effect& effect_to_apply);
    void process_effects();
    bool is_alive() const;
    void take_damage(int damage_amount);

    int get_health() const;
    int get_dodge_chance() const;
    int get_attack_power() const;
    string get_name() const;
};


class player {
private:
    weapon equipped_weapon;
    power equipped_power;
    string player_name_value;
    int health_points{ 30 };
    int dodge_rating{ 3 };

    int base_critical_chance{ 0 };
    double base_critical_multiplier{ 1.5 };

    bool is_power_active_flag{ false };
    bool power_used_in_current_battle{ false };

public:
    player(string name_arg);

    weapon get_equipped_weapon() const;
    power get_equipped_power() const;
    string get_player_name() const;

    int get_health_points() const;
    void heal_player(int heal_amount);
    void full_heal_player() { health_points = 30; }

    int get_dodge_rating() const;
    int get_total_critical_chance() const;
    int calculate_attack_damage() const;

    double get_total_critical_multiplier() const;

    void set_dodge_rating(int new_dodge_rating);
    void display_player_stats();
    void set_weapon_stats_by_choice(int weapon_choice);
    void set_power_stats_by_choice(int power_choice);
    void update_player_name(string& new_player_name);
    void take_damage(int damage_amount);

    void activate_power();

    bool is_player_alive() const;
    bool roll_critical_hit() const;
};

class location {
public:
    void explore_forest(player& current_player);
    void explore_ice_peak(player& current_player);
    void explore_desert(player& current_player);
};
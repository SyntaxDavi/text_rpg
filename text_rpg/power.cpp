#include <iostream>
#include <string>
#include "headers.h"
using namespace std;

string power::get_name() const {
	return name;
}
int power::get_damage() const {
	return damage;
}
int power::get_critical_chance_bonus() const {
	return critical_chance_bonus;
}
double power::get_critical_multiplier_bonus() const {
	return critical_multiplier_bonus;
}

void power::set_name(const string& new_name) {
	name = new_name;
}
void power::set_damage(int new_damage) {
	damage = new_damage;
}
void power::set_critical_chance_bonus(int new_crit_chance_bonus) {
	critical_chance_bonus = new_crit_chance_bonus;
}
void power::set_critical_multiplier_bonus(double new_crit_multiplier_bonus) {
	critical_multiplier_bonus = new_crit_multiplier_bonus;
}
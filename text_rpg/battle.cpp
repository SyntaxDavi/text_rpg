#include "headers.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

int start_battle(player& current_player, enemy& opponent_enemy) {

    int battle_action_choice{ 0 };
    bool power_used_this_battle{ false };

    cout << "\n!!! BATTLE STARTED !!!" << endl;

    while (opponent_enemy.is_alive() && current_player.is_player_alive()) {

        bool player_is_defending{ false };
        int actions_this_turn{ 0 };
        const auto& current_power = current_player.get_equipped_power();

        while (actions_this_turn < 2 && opponent_enemy.is_alive() && current_player.is_player_alive()) {

            cout << "\n=== " << current_player.get_player_name() << "'s Turn vs " << opponent_enemy.get_name() << " ===" << endl;
            opponent_enemy.display_stats();

            cout << "----------------------------" << endl;
            cout << "Your Health: [" << current_player.get_health_points() << "] " << endl;
            cout << "Actions remaining this turn: " << (2 - actions_this_turn) << endl;
            cout << "----------------------------" << endl;
            cout << "Choose an action:" << endl;
            cout << "1) Attack" << endl;
            cout << "2) Defend" << endl;
            cout << "3) Use Power: " << current_power.get_name() << endl;
            cout << "4) Flee" << endl;
            cout << "\nEnter option: ";

            cin >> battle_action_choice;

            if (cin.fail() || battle_action_choice < 1 || battle_action_choice > 4) {
                cout << "Invalid option. Try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;

            if (battle_action_choice == 1) {
                cout << current_player.get_player_name() << " attacks with " << current_player.get_equipped_weapon().get_name() << "!" << endl;
                int damage_inflicted = current_player.calculate_attack_damage();

                if (damage_inflicted > current_player.get_equipped_weapon().get_damage()) {
                    cout << "CRITICAL Hit! Damage: " << damage_inflicted << endl;
                }
                else {
                    cout << "Damage dealt: " << damage_inflicted << endl;
                }
                cout << endl;
                opponent_enemy.take_damage(damage_inflicted);
                opponent_enemy.process_effects();

                if (opponent_enemy.is_alive() && current_player.get_equipped_weapon().get_name() == "Katana") {
                    cout << current_player.get_player_name() << " quickly attacks a second time with the Katana!" << endl;
                    int second_hit_damage_inflicted = current_player.calculate_attack_damage();
                    if (second_hit_damage_inflicted > current_player.get_equipped_weapon().get_damage()) {
                        cout << "CRITICAL Hit! Damage: " << second_hit_damage_inflicted << endl;
                    }
                    else {
                        cout << "Damage dealt: " << second_hit_damage_inflicted << endl;
                    }
                    cout << endl;
                    opponent_enemy.take_damage(second_hit_damage_inflicted);
                    opponent_enemy.process_effects();
                }

                actions_this_turn++;
                player_is_defending = false;
            }

            else if (battle_action_choice == 2) {
                cout << current_player.get_player_name() << " is defending!" << endl;
                player_is_defending = true;
                actions_this_turn = 2;
            }

            else if (battle_action_choice == 3) {
                if (current_power.get_name() == "None" || current_power.get_name() == "Unknown Power") {
                    cout << "You don't have any power currently equipped." << endl;
                    continue;
                }
                if (current_power.get_name() == "Critical Focus" || current_power.get_name() == "+10 Health") {
                    cout << "Your power " << current_power.get_name() << " is a passive bonus and cannot be activated in combat." << endl;
                    continue;
                }

                if (power_used_this_battle) {
                    cout << "You have already used your power in this battle!" << endl;
                    continue;
                }

                power_used_this_battle = true;

                cout << "==========================================" << endl;
                cout << current_player.get_player_name() << " used the power: " << current_power.get_name() << "!" << endl;
                cout << "==========================================" << endl;

                int power_immediate_damage = current_power.get_damage();
                if (power_immediate_damage > 0 && current_power.get_name() != "Poison Attack") {
                    cout << "Immediate power damage: " << power_immediate_damage << endl;
                    opponent_enemy.take_damage(power_immediate_damage);
                }

                if (current_power.get_name() == "Poison Attack") {
                    active_effect poison_effect{ current_power.get_name(), current_power.get_damage(), 5 };
                    opponent_enemy.apply_effect(poison_effect);
                }

                cout << endl;
                opponent_enemy.process_effects();
                actions_this_turn++;
                player_is_defending = false;
            }

            else if (battle_action_choice == 4) {
                cout << current_player.get_player_name() << " fled the battle!" << endl;
                cout << endl;
                return 0;
            }

        }

        if (!opponent_enemy.is_alive()) {
            cout << opponent_enemy.get_name() << " was defeated! " << endl;
            cout << endl;
            return 1;
        }

        if (!current_player.is_player_alive()) {
            cout << "\n" << current_player.get_player_name() << " was defeated..." << endl;
            cout << endl;
            return 0;
        }

        cout << "\n--- " << opponent_enemy.get_name() << "'s Turn ---" << endl;

        int player_current_dodge = current_player.get_dodge_rating();
        int effective_dodge_chance = player_is_defending ? player_current_dodge + (player_current_dodge / 2) : player_current_dodge;

        if (effective_dodge_chance > 80) effective_dodge_chance = 80;

        int enemy_accuracy_roll_target = 100 - effective_dodge_chance;
        if (enemy_accuracy_roll_target < 10) enemy_accuracy_roll_target = 10;

        int enemy_attack_roll_value = rand() % 100;

        if (enemy_attack_roll_value < enemy_accuracy_roll_target) {
            int incoming_enemy_damage = opponent_enemy.get_attack_power();
            cout << opponent_enemy.get_name() << " attacks and deals [" << incoming_enemy_damage << "] damage to " << current_player.get_player_name() << "!" << endl;
            current_player.take_damage(incoming_enemy_damage);
        }
        else {
            cout << opponent_enemy.get_name() << " attacks, but " << current_player.get_player_name() << " dodges!" << endl;
        }
        cout << endl;

        if (!current_player.is_player_alive()) {
            cout << "\n" << current_player.get_player_name() << " was defeated by: " << opponent_enemy.get_name() << "..." << endl;
            cout << endl;
            return 0;
        }
        if (!opponent_enemy.is_alive()) {
            cout << opponent_enemy.get_name() << " was defeated! " << endl;
            cout << endl;
            return 1;
        }

    }

    if (!current_player.is_player_alive()) {
        return 0;
    }
    else if (!opponent_enemy.is_alive()) {
        return 1;
    }

    return 0;
}
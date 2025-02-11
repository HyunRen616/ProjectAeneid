#include "./Libraries.h"
#include <iostream>
#include <ctime>

using namespace std;

class Combat {
public:
    Character& player;
    Character& enemy;

    Combat(Character& p, Character& e) : player(p), enemy(e) {}

    void playerTurn() {
        if (!player.passInitiative()) {
            cout << player.name << " hesitates and misses their turn!" << endl;
            return;
        }

        cout << "Choose an action:\n1. Attack\n2. Defend\n3. Use Void Crystal\n4. Use Light Crystal\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                player.attack(enemy);
                break;
            case 2:
                player.defend();
                break;
            case 3:
                useVoidCrystal(player, enemy);
                break;
            case 4:
                useLightCrystal(player, enemy);
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }

    void enemyTurn() {
        if (!enemy.passInitiative()) {
            cout << enemy.name << " stumbles and misses their turn!" << endl;
            return;
        }

        cout << enemy.name << " attacks!\n";
        enemy.attack(player);
    }

    void useVoidCrystal(Character& user, Character& target) {
        target.initiative -= 2;
        cout << user.name << " uses Void Crystal! " << target.name << " loses initiative!\n";
    }

    void useLightCrystal(Character& user, Character& target) {
        target.precision -= 2;
        cout << user.name << " uses Light Crystal! " << target.name << " is blinded!\n";
    }

    void startCombat() {
        cout << "Combat begins between " << player.name << " and " << enemy.name << "!\n";

        // Determine first turn based on speed
        while (player.isAlive() && enemy.isAlive()) {
            if (player.speed >= enemy.speed) {
                playerTurn();
                if (enemy.isAlive()) enemyTurn();
            } else {
                enemyTurn();
                if (player.isAlive()) playerTurn();
            }
        }

        cout << (player.isAlive() ? "You win!" : "You lose!") << "\n";
    }
};

int main() {
    srand(time(0)); // Seed random generator

    Character player("Magician", 10, 5, 100, 8, 15, 12);
    Character enemy("Corrupted Beast", 8, 4, 80, 6, 12, 10);

    Combat combat(player, enemy);
    combat.startCombat();

    return 0;
}

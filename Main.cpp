#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Character {
public:
    std::string name;
    int health;
    int speed;
    int toughness;
    int precision;
    int strength;
    int initiative;

    Character(std::string n, int h, int s, int t, int p, int str, int i)
        : name(n), health(h), speed(s), toughness(t), precision(p), strength(str), initiative(i) {}

    bool isAlive() {
        return health > 0;
    }
};

class Combat {
public:
    Character player;
    Character enemy;

    Combat(Character p, Character e) : player(p), enemy(e) {}

    void playerTurn() {
        std::cout << "Choose an action: \n1. Attack\n2. Defend\n3. Use Void Crystal\n4. Use Light Crystal\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            attack(player, enemy);
            break;
        case 2:
            defend(player);
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
        if (enemy.isAlive()) {
            std::cout << enemy.name << " attacks!\n";
            attack(enemy, player);
        }
    }

    void attack(Character &attacker, Character &defender) {
        int damage = attacker.strength - defender.toughness;
        if (damage > 0) {
            defender.health -= damage;
            std::cout << attacker.name << " deals " << damage << " damage to " << defender.name << "!\n";
        } else {
            std::cout << defender.name << " blocks the attack!\n";
        }
    }

    void defend(Character &defender) {
        defender.toughness += 2;
        std::cout << defender.name << " raises toughness for this turn!\n";
    }

    void useVoidCrystal(Character &user, Character &target) {
        target.initiative -= 2;
        std::cout << user.name << " uses Void Crystal! " << target.name << " loses initiative!\n";
    }

    void useLightCrystal(Character &user, Character &target) {
        target.precision -= 2;
        std::cout << user.name << " uses Light Crystal! " << target.name << " is blinded!\n";
    }

    void startCombat() {
        while (player.isAlive() && enemy.isAlive()) {
            playerTurn();
            enemyTurn();
        }
        std::cout << (player.isAlive() ? "You win!" : "You lose!") << "\n";
    }
};

int main() {
    srand(time(0));
    Character player("Seeker", 100, 10, 5, 7, 10, 8);
    Character enemy("Corrupted Beast", 80, 8, 6, 5, 9, 7);
    Combat combat(player, enemy);
    combat.startCombat();
    return 0;
}

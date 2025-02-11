#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <cstdlib>

class Character {
public:
    std::string name;
    int speed;
    int toughness;
    int vitality;
    int precision;
    int strength;
    int initiative;

    Character(std::string n, int spd, int tough, int vit, int prec, int str, int init)
        : name(n), speed(spd), toughness(tough), vitality(vit), precision(prec), strength(str), initiative(init) {}

    void takeDamage(int damage) {
        int actualDamage = std::max(1, damage - toughness); // Prevent healing from toughness
        vitality -= actualDamage;
        if (vitality < 0) vitality = 0;
    }

    void attack(Character& target) {
        int damage = strength * 2;
        target.takeDamage(damage);
        std::cout << name << " attacks " << target.name << " for " << damage << " damage!" << std::endl;
    }

    void defend() {
        toughness += 2; // Temporarily increase toughness
        std::cout << name << " braces for impact, increasing toughness!" << std::endl;
    }

    bool isAlive() const {
        return vitality > 0;
    }

    bool passInitiative() const {
        int roll = rand() % 20 + 1; // Simulate a d20 roll
        return roll <= initiative;
    }
};

#endif // CHARACTER_H

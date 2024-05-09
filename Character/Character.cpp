//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"

#include <string.h>

Character::Character(const char _name[], int _health, int _attack, int _defense, int _speed, bool _isPlayer) {

    strcpy(name, _name);
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    if (isDefending){
        return defense*1.20;
    }
    return defense;
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {

    string aux = "Name: ";
    aux.append(name).append("\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed));
    return aux;

}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}
void Character::defend() {
    isDefending=true;
    defense = std::ceil(defense*1.2);
}
//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(const char _name[], int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;

    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Player::levelUp()
{
    int experienceValue = 10;

    experience -= experienceValue;

    level++;
    health += 5;
    attack += 5;
    defense += 5;
    speed += 5;

    cout << "----------------------------------------------" << endl;
    cout << "You have leveled up to: " << level << endl;
    cout << "Health: " << health << ", Attack: " << attack << ", Defense: " << defense << ", Speed: " << speed << endl;
    cout << "Level Experience: " << experience << endl;

    if (experience >= experienceValue) {
        levelUp();
    }

}
void Player::gainExperience(int exp) {
    int experienceValue = 10;
    experience += exp;

    if (experience >= experienceValue) {
        levelUp();
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    selectedTarget--;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action;
    cout << "Select an action: " << endl
         << "1. Attack" << endl
         << "2. Defend" << endl;
    cin >> action;
    Action currentAction;
    Character* target = nullptr;
    int originalDefense = defense;
    switch(action) {
    case 1:
            if (!enemies.empty()) {
                target = selectedEnemy;
            } else {
                currentAction.action = nullptr;
                return currentAction;
            }
        currentAction.target = target;
        currentAction.action = [this, target](){
            doAttack(target);
        };
        currentAction.speed = getSpeed();
        break;
    case 2:
        defend();
        if (!enemies.empty()) {
            target = enemies[0];
        }
        if (target) {
            currentAction.target = target;
            currentAction.action = [this, target, originalDefense](){
                defense = originalDefense;
            };
            currentAction.speed = target->getSpeed();
        } else {
            currentAction.action = nullptr;
        }
        break;
    default:
        cout << "Invalid action" << endl;
        currentAction.action = nullptr;
        break;
    }

    return currentAction;
}

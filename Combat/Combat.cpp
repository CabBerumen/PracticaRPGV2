//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <string>
#include <iostream>
#include <string.h>
#include <utility>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = vector<Character*>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()){
        partyMembers.push_back((Player*) participant);
    } else {
        enemies.push_back((Enemy*) participant);
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    sort(participants.begin(), participants.end(), compareSpeed);
}

char* Combat::toString() {
    char buffer[1024];
    buffer[0] = '\0';
    for (auto it = participants.begin(); it != participants.end(); ++it) {
        strcat(buffer, (*it)->toString().c_str());
        strcat(buffer, "\n");
    }

    strcat(buffer, "-------------\n");

    return buffer;
}

Character* Combat::getTarget(Character* attacker) {
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        if((*it)->getIsPlayer() != attacker->getIsPlayer()){
            return *it;
        }
    }
    //TODO: Handle this exception
    return nullptr;
}

void Combat::chooseEnemy() {
    cout << "Choose your enemy: " << endl;
    for (int i = 0; i < enemies.size(); ++i) {
        cout << i+1 << ". " << enemies[i]->getName() << endl;
    }
    int choice;
    cin >> choice;
    if (choice > 0 && choice <= enemies.size()) {
        partyMembers[0]->setSelectedEnemy(enemies[choice-1]);
        participants.clear();
        participants.push_back(partyMembers[0]);
        selectedEnemy = enemies[choice-1];
        participants.push_back(selectedEnemy);
    } else
        {
        selectedEnemy = nullptr;
    }
}

void Combat::doCombat() {
    int round = 1;
    cout << "Fight! " << endl;
    chooseEnemy();

    for (auto participant : participants) {
        cout << participant->toString() << endl;
    }

    combatPrep();

    while(enemies.size() > 0 && partyMembers.size() > 0) {
        cout<<"Round: " << round << endl;
        vector<Character*>::iterator it = participants.begin();
        registerActions(it);
        executeActions(it);

        cout << "----------------------------------------------" << endl;
        for (auto participant : participants) {
            cout << participant->toString() << endl;
        }

        round++;

        if (selectedEnemy && selectedEnemy->getHealth() <= 0)
        {
            Player* player = nullptr;

            for (auto participant : participants) {
                if (participant->getIsPlayer()) {
                    player = dynamic_cast<Player*>(participant);
                    break;
                }
            }
            if (player) {
                player->gainExperience(selectedEnemy->getExperience());
            }

            if(enemies.empty()) {
                break;
            }

        }
    }

    if (selectedEnemy && selectedEnemy->getHealth() <= 0) {
        cout << "You win!" << endl;
    } else {
        cout << "You lose!" << endl;
    }
}

void Combat::executeActions(vector<Character*>::iterator participant) {
    while(!actionQueue.empty()) {
        Action currentAction = actionQueue.top();
        currentAction.action();
        actionQueue.pop();
        //Check if there are any dead characters
        checkParticipantStatus(*participant);
        checkParticipantStatus(currentAction.target);
    }
}

void Combat::checkParticipantStatus(Character *participant) {
    if(participant != nullptr && participant->getHealth() <= 0) {
        if(participant->getIsPlayer()) {
            partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), participant), partyMembers.end());
        } else {
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::registerActions(vector<Character*>::iterator participantIterator) {
    while(participantIterator != participants.end()) {
        if((*participantIterator)->getIsPlayer()) {
            Action playerAction = ((Player*) *participantIterator)->takeAction(enemies);
            if (playerAction.action != nullptr && selectedEnemy != nullptr) {
                playerAction.target = selectedEnemy;
            }
            actionQueue.push(playerAction);
        } else {
            Action enemyAction = ((Enemy*)*participantIterator)->takeAction(partyMembers);
            actionQueue.push(enemyAction);
            participantIterator++;
            continue;
        }
        participantIterator++;
    }
}
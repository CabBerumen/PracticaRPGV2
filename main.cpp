#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"

Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(int error) {
        //Preguntar al usuario el nombre de jugador
        //return new Player("Otro Jugador", 10, 5, 4, 3);
        cout << "No data saved... " << endl;
        return new Player("Caleb Berumen", 40, 10, 5, 3);
    }
}

int main() {
    Player *player = loadPlayerInfo();
    cout << player -> getName() << endl;
    cout << player -> toString() << endl;
    Enemy *enemy = new Enemy("Goblin", 35, 6, 2, 5, 75);
    Enemy *enemy2 = new Enemy("Orc", 35, 6, 2, 5, 75);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}

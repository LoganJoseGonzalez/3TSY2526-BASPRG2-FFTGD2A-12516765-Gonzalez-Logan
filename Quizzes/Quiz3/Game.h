#ifndef GAME_H
#define GAME_H

#include "Units.h"

inline Unit* playerCreation() {
    string playerName;
    int classChoice = 0;

    cout << "Enter player name: ";
    getline(cin, playerName);

    if (playerName == "") {
        playerName = "Traveler";
    }

    cout << "\nSelect Class:\n";
    cout << "1. Warrior = High HP & VIT\n";
    cout << "2. Assassin = High AGI & DEX\n";
    cout << "3. Mage = High POW\n";
    cout << "Choose from 1-3: ";
    cin >> classChoice;

    while (classChoice < 1 || classChoice > 3) {
        cout << "Can't pick that! Pick 1, 2, or 3: ";
        cin >> classChoice;
    }

    cin.ignore();

    system("pause");
    system("cls");
    cout << "Be careful traveler\n";
    cout << "There are things here far more evil than you can imagine...\n";


    system("pause");
    system("cls");

    ClassType classChosen;
    switch (classChoice) {
    case 1: classChosen = WARRIOR; break;
    case 2: classChosen = ASSASSIN; break;
    case 3: classChosen = MAGE; break;
    }

    if (classChosen == WARRIOR) {
        return new Unit(playerName, WARRIOR, 100, 15, 10, 8, 10);
    }
    else if (classChosen == ASSASSIN) {
        return new Unit(playerName, ASSASSIN, 80, 12, 6, 15, 15);
    }
    else if (classChosen == MAGE) {
        return new Unit(playerName, MAGE, 70, 20, 5, 10, 12);
    }

    return nullptr;
}

inline bool startBattle(Unit* player, Unit* enemy, int stage) {
    
    cout << "STAGE " << stage << " BATTLE\n";

    cout << "\nYOU\n";
    player->statDisplay();

    cout << "\nENEMY\n";
    enemy->statDisplay();

    system("pause");
    system("cls");

    int turnCounter = 1;

    while (player->isAlive() && enemy->isAlive()) {
        cout << " Turn " << turnCounter <<"";

        Unit* first = player;
        Unit* second = enemy;

        if (enemy->getAgi() > player->getAgi()) {
            first = enemy;
            second = player;
        }

        int percentHit = first->calcHit(second);
        int roll = (rand() % 100) + 1;

        cout << first->getName() << " attacks " << second->getName()
            << " (Hit Chance: " << percentHit << "%)... ";

        if (roll <= percentHit) {
            int damageDealt = first->calcDmg(second);
            second->dmgTaken(damageDealt);
            cout << "You hit! You dealt " << damageDealt << " damage.\n";

            if (first->goodAgainst(second->getClassType())) {
                cout << "Attack is Super effective!\n";
            }
        }
        else {
            cout << "MISSED!\n";
        }

        if (second->isAlive()) {
            percentHit = second->calcHit(first);
            roll = (rand() % 100) + 1;

            cout << second->getName() << " attacks " << first->getName()
                << " (Hit Chance: " << percentHit << "%)... ";

            if (roll <= percentHit) {
                int damageDealt = second->calcDmg(first);
                first->dmgTaken(damageDealt);
                cout << "You got hit! they dealt " << damageDealt << " damage.\n";

                if (second->goodAgainst(first->getClassType())) {
                    cout << "Atack Super effective!\n";
                }
            }
            else {
                cout << "MISSED!\n";
            }
        }

        cout << "\nStatus\n";
        cout << player->getName() << " HP: " << player->getCurrentHp() << "/" << player->getMaxHp() << endl;
        cout << enemy->getName() << " HP: " << enemy->getCurrentHp() << "/" << enemy->getMaxHp() << endl;

        turnCounter++;
        system("pause");
        system("cls");
    }

    return player->isAlive();
}

inline void runGame() {
    cout << "WELCOME TO THE ARENA\n";

    system("pause");
    system("cls");

    cout << "Welcome, traveler, shall we begin..?\n";
    cout << "Who is your Champion?\n\n";

    system("pause");
    system("cls");

    Unit* player = playerCreation();
    int stage = 1;

    while (true) {
        Unit* enemy = oppSpawn(stage);

        bool won = startBattle(player, enemy, stage);

        if (won) {
            cout << "You are Victorious over " << enemy->getName() << "!\n";

            player->applyBuff(enemy->getClassType());
            player->percentHealed(0.30);

            delete enemy;

            stage++;
            system("pause");
            system("cls");
        }
        else {
            cout << "You have been DEFEATED!\n";
            cout << player->getName() << " died in battle.\n";
            cout << "Progressed until Stage: " << stage << endl;

            delete enemy;

            break;
        }
    }

    delete player;

    cout << "\nGame over...\n";
}

#endif

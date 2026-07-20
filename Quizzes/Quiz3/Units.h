#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum ClassType {
    WARRIOR = 1,
    ASSASSIN = 2,
    MAGE = 3
};

class Unit {
private:
    string name;
    ClassType classType;
    int maxHp;
    int currentHp;
    int pow;
    int vit;
    int agi;
    int dex;

public:
    Unit(string unitName, ClassType type, int hp, int power, int vitality, int agility, int dexterity) {
        name = unitName;
        classType = type;
        maxHp = hp;
        currentHp = hp;
        pow = power;
        vit = vitality;
        agi = agility;
        dex = dexterity;
    }
    ~Unit() {}

    string getName() { return name; }
    ClassType getClassType() { return classType; }
    int getCurrentHp() { return currentHp; }
    int getMaxHp() { return maxHp; }
    int getPow() { return pow; }
    int getVit() { return vit; }
    int getAgi() { return agi; }
    int getDex() { return dex; }

    string getClassName() {
        if (classType == WARRIOR) return "Warrior";
        if (classType == ASSASSIN) return "Assassin";
        if (classType == MAGE) return "Mage";
        return "Unknown";
    }

    bool isAlive() {
        return currentHp > 0;
    }

    int calcHit(Unit* defendingUnit) {
        if (defendingUnit->getAgi() <= 0) return 80;

        int hit = (dex * 100) / defendingUnit->getAgi();

        if (hit < 20) hit = 20;
        if (hit > 80) hit = 80;

        return hit;
    }

    bool goodAgainst(ClassType defendingUnitClass) {
        switch (classType) {
        case WARRIOR: return (defendingUnitClass == ASSASSIN);
        case ASSASSIN: return (defendingUnitClass == MAGE);
        case MAGE: return (defendingUnitClass == WARRIOR);
        default: return false;
        }
    }

    int calcDmg(Unit* defendingUnit) {
        int baseDmg = pow - defendingUnit->getVit();

        if (goodAgainst(defendingUnit->getClassType())) {
            baseDmg = (baseDmg * 3) / 2;
        }

        if (baseDmg < 1) {
            baseDmg = 1;
        }

        return baseDmg;
    }

    void dmgTaken(int damage) {
        currentHp -= damage;
        if (currentHp < 0) {
            currentHp = 0;
        }
    }

    void percentHealed(double percent) {
        int amountHealed = maxHp * percent;
        currentHp += amountHealed;

        if (currentHp > maxHp) {
            currentHp = maxHp;
        }

        cout << name << " you're healed " << amountHealed << " HP! (" << currentHp << "/" << maxHp << " HP)\n";
    }

    void applyBuff(ClassType defeatedUnitClass) {
        switch (defeatedUnitClass) {
        case WARRIOR:
            pow += 3;
            vit += 3;
            cout << "Win Buff: POW +3, VIT +3 to your stats!\n";
            break;
        case ASSASSIN:
            agi += 3;
            dex += 3;
            cout << "Win Buff: AGI +3, DEX +3 to your stats!\n";
            break;
        case MAGE:
            pow += 5;
            cout << "Win Buff: POW +5 to your stats!\n";
            break;
        }
    }

    void statDisplay() {
        cout << " Name: " << name << endl;
        cout << " Class: " << getClassName() << endl;
        cout << " HP: " << currentHp << " / " << maxHp << endl;
        cout << " POW: " << pow << endl;
        cout << " AGI: " << agi << endl;
        cout << "| VIT: " << vit << endl;
        cout << "| DEX: " << dex << endl;
    }
};

inline Unit* oppSpawn(int stage) {
    int randNum = (rand() % 3) + 1;
    ClassType randClass;

    if (randNum == 1) randClass = WARRIOR;
    else if (randNum == 2) randClass = ASSASSIN;
    else randClass = MAGE;

    string oppName = "";
    int hp = 0, pow = 0, vit = 0, agi = 0, dex = 0;
    int growth = (stage - 1) * 3;

    switch (randClass) {
    case WARRIOR:
        oppName = "Fighter Warrior";
        hp = 80 + (stage * 15);
        pow = 12 + growth;
        vit = 8 + growth;
        agi = 6 + (stage * 2);
        dex = 8 + (stage * 2);
        break;
    case ASSASSIN:
        oppName = "Rogue Assassin";
        hp = 65 + (stage * 12);
        pow = 10 + growth;
        vit = 5 + growth;
        agi = 12 + (stage * 3);
        dex = 12 + (stage * 3);
        break;
    case MAGE:
        oppName = "Evil Mage";
        hp = 60 + (stage * 10);
        pow = 16 + (stage * 4);
        vit = 4 + growth;
        agi = 8 + (stage * 2);
        dex = 10 + (stage * 2);
        break;
    }

    return new Unit(oppName, randClass, hp, pow, vit, agi, dex);
}

#endif

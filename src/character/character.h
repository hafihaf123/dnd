#ifndef CHARACTER_H
#define CHARACTER_H

//included libraries
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

enum CharClass {
    BARBARIAN,
    DRUID,
    MAGE,
    MONK,
    PALADIN,
    PRIEST,
    RANGER,
    ROGUE,
    SORCERER,
    WARLOCK
};

enum CharRace {
    HUMAN,
    ELF,
    DWARF
};

struct Stats {
    int strength;
    int constitution;
    int dexterity;
    int intelligence;
    int wisdom;
    int charisma;
};

struct Character {
    char *name;
    enum CharClass charClass;
    enum CharRace race;
    int level;
    struct Stats *stats;
};

//functions declaration
struct Character characterMenu();
int createCharacter(struct Character *character);
int loadCharacter(struct Character *character);
int saveCharacter(struct Character character);
struct Stats* initStats();

#endif /* CHARACTER_H */

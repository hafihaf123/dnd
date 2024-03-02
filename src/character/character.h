#ifndef CHARACTER_H
#define CHARACTER_H

//included libraries
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

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

static const char * const charClassNames[] = {
    [BARBARIAN] = "BARBARIAN",
    [DRUID] = "DRUID",
    [MAGE] = "MAGE",
    [MONK] = "MONK",
    [PALADIN] = "PALADIN",
    [PRIEST] = "PRIEST",
    [RANGER] = "RANGER",
    [ROGUE] = "ROGUE",
    [SORCERER] = "SORCERER",
    [WARLOCK] = "WARLOCK"
};

char *charDirName = ".characters";

enum CharRace {
    HUMAN,
    ELF,
    DWARF
};

static const char * const charRaceNames[] = {
    [HUMAN] = "HUMAN",
    [ELF] = "ELF",
    [DWARF] = "DWARF"
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
struct Character* characterMenu();
int createCharacter(struct Character *character);
struct Character * loadCharacter(const char *name);
int saveCharacter(const struct Character character);
struct Stats* initStats();
void freeCharacter(struct Character *character);

#endif /* CHARACTER_H */

#ifndef CHARACTER_H
#define CHARACTER_H

//included libraries
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

//included headers
#include "stats.h"
#include "char_class.h"
#include "char_race.h"

extern char *charDirName;

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
int loadCharacter(struct Character *character);
int saveCharacter(const struct Character character);
void freeCharacter(struct Character *character);
struct Character * initialiseCharacter();

#endif /* CHARACTER_H */

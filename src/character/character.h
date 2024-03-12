/// @file character.h

#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#include "stats.h"
#include "char_class.h"
#include "char_race.h"

extern char *charDirName; ///< name of directory where characters are saved

/// @brief structure for characters
struct Character {
    char *name;
    enum CharClass charClass;
    enum CharRace race;
    int level;
    struct Stats *stats;
};

/**
 * @brief entry point for selecting a character
 * 
 * @details opts the user for input (integer from 1 to 3) and calls the appropriate functions:
 * 1. createCharacter()
 * 2. loadCharacter()
 * 3. exits by returning NULL
 * 
 * @return struct Character* the selected (or created) character; returns NULL for failure (or choice exit)
 */
struct Character* characterMenu();

/**
 * @brief create a Character object from user input
 * 
 * @details also calls saveCharacter() to save the created character
 * 
 * @param character pointer to Character allocated by characterMenu()
 * @return int 0 (EXIT_SUCCESS) or 1 (EXIT_FAILURE)
 */
int createCharacter(struct Character *character);

/**
 * @brief load a Character object from file in #charDirName
 * 
 * @param character pointer to Character allocated by characterMenu()
 * @return int 0 (EXIT_SUCCESS) or 1 (EXIT_FAILURE)
 */
int loadCharacter(struct Character *character);

/**
 * @brief saves the Character into a file to #charDirName (calls setupDir() if not exists)
 * 
 * @param character Character to save
 * @return int 0 (EXIT_SUCCESS) or 1 (EXIT_FAILURE)
 */
int saveCharacter(const struct Character character);

/**
 * @brief function to properly free the Character struct
 * 
 * @param character Character to free
 */
void freeCharacter(struct Character *character);

/**
 * @brief function to properly initialise the Character struct
 * 
 * @details allocates memory to a Character struct pointer with malloc()
 * sets the name and stats members to NULL
 * the returned Character pointer should be freed with freeCharacter()
 * 
 * @return struct Character* initialised Character (NULL if failed) ! free with freeCharacter() !
 */
struct Character * initialiseCharacter();

#endif /* CHARACTER_H */

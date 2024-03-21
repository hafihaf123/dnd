/**
 * @file character.h
 * @author hafihaf123
 * @brief header for character.c
 */
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
#include "database.h"

/**
 * @brief entry point for selecting a character
 * 
 * @details opts the user for input (integer from 1 to 3) and calls the appropriate functions:
 * 1. createCharacter()
 * 2. loadCharacter()
 * 3. exit(EXIT_SUCCESS)
 * 
 * @param db database for storing / loading the Character
 * @return struct Character* the selected (or created) character - failure returns NULL
 */
struct Character* characterMenu(sqlite3 *db);

/**
 * @brief create a Character object from user input
 * 
 * @details also calls saveCharacter() to save the created character
 * 
 * @param character pointer to Character allocated by characterMenu()
 * @param db database for storing the Character
 * @return int 0 (EXIT_SUCCESS) or 1 (EXIT_FAILURE)
 */
int createCharacter(struct Character *character, sqlite3 *db);

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

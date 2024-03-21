/**
 * @file database.h
 * @author hafihaf123
 * @brief header for database.c
 */
#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

#include <stdlib.h>
#include <stdio.h>

#include "char_class.h"
#include "char_race.h"
#include "stats.h"

/// @brief structure for characters
struct Character {
    int id;
    char *name;
    enum CharClass charClass;
    enum CharRace race;
    int level;
    struct Stats *stats;
};

/**
 * @brief opens a database, if it doesn't exist, it creates it
 * 
 * @param name path to the database file from project root
 * @return sqlite3* the database pointer - failure returns NULL
 */
sqlite3 * setupDatabase(char *name);

/**
 * @brief creates a table of characters if it doesn't exist
 * 
 * @param db database to setup the table to
 * @return int EXIT_SUCCESS or EXIT_FAILURE
 */
int setupCharacterTable(sqlite3 *db);

/**
 * @brief load into a Character object from database
 * 
 * @param character pointer to a previously allocated Character to load into
 * @param db database to load from
 * @return int EXIT_SUCCESS or EXIT_FAILURE
 */
int loadCharacter(struct Character *character, sqlite3 *db);

/**
 * @brief saves the Character into a database
 * 
 * @param character Character to save
 * @param db database to which the Character will be saved
 * @return int id of the saved Character, -1 for failure
 */
int saveCharacter(struct Character character, sqlite3 *db);

#endif // DATABASE_H

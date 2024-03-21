/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/29/24 17:11:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "main.h"
#include "character.h"
#include "database.h"

char *databsePath = "db/database.db"; ///< path to the database file from project root

int main() {
    srand(time(NULL));

    sqlite3 *db = setupDatabase(databsePath);

    if (db == NULL) {
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    if (setupCharacterTable(db) == EXIT_FAILURE) {
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    struct Character *character;

    do {
        character = characterMenu(db);
    } while (character == NULL);

    if (character == NULL) exit(EXIT_FAILURE);

    printf("\n\nname: %s\nlevel: %d\nid: %d\n", character->name, character->level, character->id);

    freeCharacter(character);
    
    sqlite3_close(db);

    return EXIT_SUCCESS;
}

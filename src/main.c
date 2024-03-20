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

char *databsePath = "database/characters.db";

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

    struct Character *character = characterMenu(db);

    printf("\n\nname: %s\nlevel: %d\n", character->name, character->level);

    freeCharacter(character);
    
    sqlite3_close(db);

    return EXIT_SUCCESS;
}

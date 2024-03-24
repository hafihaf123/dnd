/**
 * @file main.c
 * @author hafihaf123
 * @brief entry point of the program
 */
#include "main.h"
#include "character.h"
#include "database.h"
#include "communication.h"

#define DATABASE_PATH "db/database.db" ///< path to the database file from project root
#define CREATE_CHARACTERS_TABLE_QUERY "sql/createCharactersTable.sql"

int main() {
    srand(time(NULL));

    sqlite3 *db = setupDatabase(DATABASE_PATH);

    if (db == NULL) {
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    if (executeFileQuery(db, CREATE_CHARACTERS_TABLE_QUERY) == EXIT_FAILURE) {
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    struct Character *character;

    do {
        character = characterMenu(db);
    } while (character == NULL);

    if (character == NULL) return EXIT_FAILURE;

    printf("\n\nname: %s\nlevel: %d\nid: %d\n", character->name, character->level, character->id);

    freeCharacter(character);

    communicationMain();
    
    sqlite3_close(db);

    return EXIT_SUCCESS;
}

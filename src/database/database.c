/**
 * @file database.c
 * @author hafihaf123
 * @brief logic for working with the sqlite database
 */
#include "database.h"
#include "utils.h"

sqlite3 * setupDatabase(char *name) {
    sqlite3 *db;

    char *dirName = strdup(name);
    char *lastSlash = strrchr(dirName, '/');
    if (lastSlash != NULL) *lastSlash = '\0';
    if (setupDir(dirName) == EXIT_FAILURE) {
        free(dirName);
        return NULL;
    } else free(dirName);

    int rc = sqlite3_open(name, &db);

    if (rc != SQLITE_OK) {
        error("cannot open database");
        return NULL;
    }

    return db;
}

int setupCharacterTable(sqlite3 *db) {
    const char *query = "CREATE TABLE IF NOT EXISTS characters ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "name TEXT NOT NULL UNIQUE,"
                        "class TEXT NOT NULL,"
                        "race TEXT NOT NULL,"
                        "level INTEGER NOT NULL,"
                        "strength INTEGER NOT NULL,"
                        "constitution INTEGER NOT NULL,"
                        "dexterity INTEGER NOT NULL,"
                        "intelligence INTEGER NOT NULL,"
                        "wisdom INTEGER NOT NULL,"
                        "charisma INTEGER NOT NULL"
                        ");";
    int rc = sqlite3_exec(db, query, 0, 0, 0);
    if (rc != SQLITE_OK) {
        char *errMsg = addStrings("table creation failed: ", sqlite3_errmsg(db));
        error(errMsg);
        free(errMsg);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int loadCharacter(struct Character *character, sqlite3 *db) {
    if (character == NULL) {
        error("character struct argument not properly initialised");
        return EXIT_FAILURE;
    }

    char *name = getStringInput("name: ");
    if (name == NULL) {
        return EXIT_FAILURE;
    }

    const char *query = "SELECT * FROM characters WHERE name = ?;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        char *errMsg = addStrings("failed to prepare statement: ", sqlite3_errmsg(db));
        error(errMsg);
        free(errMsg);
        free(name);
        return EXIT_FAILURE;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if(rc == SQLITE_ROW) {
        character->id = sqlite3_column_int(stmt, 0);
        character->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        character->charClass = getEnumFromName((const char*)sqlite3_column_text(stmt, 2), charClassNames, ARR_SIZE(charClassNames));
        character->race = getEnumFromName((const char*)sqlite3_column_text(stmt, 3), charRaceNames, ARR_SIZE(charRaceNames));
        character->level = sqlite3_column_int(stmt, 4);

        struct Stats *stats = (struct Stats *)malloc(sizeof(struct Stats));

        stats->strength = sqlite3_column_int(stmt, 5);
        stats->constitution = sqlite3_column_int(stmt, 6);
        stats->dexterity = sqlite3_column_int(stmt, 7);
        stats->intelligence = sqlite3_column_int(stmt, 8);
        stats->wisdom = sqlite3_column_int(stmt, 9);
        stats->charisma = sqlite3_column_int(stmt, 10);

        character->stats = stats;
    } else {
        char *errMsg = addStrings("could not find character: ", name);
        error(errMsg);
        free(errMsg);
        return EXIT_FAILURE;
    }

    free(name);
    sqlite3_finalize(stmt);
    return EXIT_SUCCESS;
}

int saveCharacter(struct Character character, sqlite3 *db) {
    const char *query = "INSERT INTO characters (name, class, race, level, strength, dexterity, constitution, intelligence, wisdom, charisma) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        char *errMsg = addStrings("failed to prepare statement: ", sqlite3_errmsg(db));
        error(errMsg);
        free(errMsg);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, character.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, charClassNames[character.charClass], -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, charRaceNames[character.race], -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, character.level);
    sqlite3_bind_int(stmt, 5, character.stats->strength);
    sqlite3_bind_int(stmt, 6, character.stats->dexterity);
    sqlite3_bind_int(stmt, 7, character.stats->constitution);
    sqlite3_bind_int(stmt, 8, character.stats->intelligence);
    sqlite3_bind_int(stmt, 9, character.stats->wisdom);
    sqlite3_bind_int(stmt, 10, character.stats->charisma);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        char *errMsg = addStrings("inserting into the database failed: ", sqlite3_errmsg(db));
        error(errMsg);
        free(errMsg);
        return -1;
    }

    int id = sqlite3_last_insert_rowid(db);

    sqlite3_finalize(stmt);

    return id;
}
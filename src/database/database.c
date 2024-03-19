/**
 * @file database.c
 * @author hafihaf123
 * @brief file containing logic for working with the sqlite database
 */

#include "database.h"
#include "utils.h"

sqlite3 * setupDatabase(char *name) {
    sqlite3 *db;

    int rc = sqlite3_open_v2(name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (rc != SQLITE_OK) {
        error("cannot open database");
        return NULL;
    }

    return db;
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
        error( addStrings("failed to prepare statement: ", sqlite3_errmsg(db)) );
        free(name);
        return EXIT_FAILURE;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    free(name);

    rc = sqlite3_step(stmt);

    if(rc == SQLITE_ROW) {
        character->name = strdup((const char*)sqlite3_column_text(stmt, 1));
        character->charClass = getEnumFromName((const char*)sqlite3_column_text(stmt, 2), charClassNames, ARR_SIZE(charClassNames));
        character->race = getEnumFromName((const char*)sqlite3_column_text(stmt, 3), charRaceNames, ARR_SIZE(charRaceNames));
        character->level = sqlite3_column_int(stmt, 4);

        struct Stats *stats = (struct Stats *)malloc(sizeof(struct Stats));

        stats->strength = sqlite3_column_int(stmt, 5);
        stats->dexterity = sqlite3_column_int(stmt, 6);
        stats->constitution = sqlite3_column_int(stmt, 7);
        stats->intelligence = sqlite3_column_int(stmt, 8);
        stats->wisdom = sqlite3_column_int(stmt, 9);
        stats->charisma = sqlite3_column_int(stmt, 10);

        character->stats = stats;
    } else {
        error( addStrings("could not find character: ", name) );
        return EXIT_FAILURE;
    }

    sqlite3_finalize(stmt);
    return EXIT_SUCCESS;
    /*

    DIR *dir = opendir(charDirName);
    if (dir == NULL) {
        error("opening characters directory failed");
        free(name);
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    int containsName = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, name) == 0) {
            containsName = 1;
            break;
        }
    }
    closedir(dir);
    if (containsName != 1) {
        char *message = addStrings("could not find character with name ", name);
        error(message);
        free(message);
        free(name);
        return EXIT_FAILURE;
    }

    char *fname = addStrings(charDirName, name);
    
    FILE *file = fopen(fname, "r");
    free(fname);
    if (file == NULL) {
        error("file opening failed");
        free(name);
        return EXIT_FAILURE;
    }

    if (character == NULL) {
        error("character struct argument not properly initialised");
        free(name);
        return EXIT_FAILURE;
    }

    //loading name
    character->name = name;
    //loading class
    char *className = (char *)malloc(15);
    fscanf(file, "%s", className);
    character->charClass = getEnumFromName(className, charClassNames, ARR_SIZE(charClassNames));
    free(className);
    //loading race
    char *raceName = (char *)malloc(15);
    fscanf(file, "%s", raceName);
    character->race = getEnumFromName(raceName, charRaceNames, ARR_SIZE(charRaceNames));
    free(raceName);
    //loading level
    int level;
    fscanf(file, "%d", &level);
    character->level = level;
    //loading stats
    struct Stats *stats = (struct Stats *)malloc(sizeof(struct Stats));

    fscanf(file, "%d", &stats->strength);
    fscanf(file, "%d", &stats->dexterity);
    fscanf(file, "%d", &stats->constitution);
    fscanf(file, "%d", &stats->intelligence);
    fscanf(file, "%d", &stats->wisdom);
    fscanf(file, "%d", &stats->charisma);

    character->stats = stats;

    fclose(file);
    return EXIT_SUCCESS;
    
    */
}

int saveCharacter(const struct Character character, sqlite3 *db) {
    const char *query = "INSTERT INTO characters (name, class, race, level, strength, dexterity, constitution, intelligence, wisdom, charisma) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        error( addStrings("failed to prepare statement: ", sqlite3_errmsg(db)) );
        return EXIT_FAILURE;
    }

    sqlite3_bind_text(stmt, 1, character.name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 1, charClassNames[character.charClass], -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 1, charRaceNames[character.race], -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 1, character.level);
    sqlite3_bind_int(stmt, 1, character.stats->strength);
    sqlite3_bind_int(stmt, 1, character.stats->dexterity);
    sqlite3_bind_int(stmt, 1, character.stats->constitution);
    sqlite3_bind_int(stmt, 1, character.stats->intelligence);
    sqlite3_bind_int(stmt, 1, character.stats->wisdom);
    sqlite3_bind_int(stmt, 1, character.stats->charisma);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        error( addStrings("inserting into the database failed: ", sqlite3_errmsg(db)) );
        return EXIT_FAILURE;
    }

    sqlite3_finalize(stmt);

    return EXIT_SUCCESS;

    /*
    if((setupDir(charDirName)) == EXIT_FAILURE) {
        error("characters directory setup failed");
        return EXIT_FAILURE;
    }
    char *fname = addStrings(charDirName, character.name);
    
    FILE *file = fopen(fname, "w");
    free(fname);
    if (file == NULL) {
        error("file creation failed");
        return EXIT_FAILURE;
    }
    fprintf(file, "%s\n%s\n%d\n", charClassNames[character.charClass], charRaceNames[character.race], character.level);

    //printing stats
    fprintf(file, "%d\n", character.stats->strength);
    fprintf(file, "%d\n", character.stats->dexterity);
    fprintf(file, "%d\n", character.stats->constitution);
    fprintf(file, "%d\n", character.stats->intelligence);
    fprintf(file, "%d\n", character.stats->wisdom);
    fprintf(file, "%d\n", character.stats->charisma);

    fclose(file);

    return EXIT_SUCCESS;
    */
}
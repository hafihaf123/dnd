/*
 * =====================================================================================
 *
 *       Filename:  character.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/29/24 09:55:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "character.h"
#include "utils.h"

struct Character* characterMenu(sqlite3 *db) {
    printf("do you want to\n\t(1) create a character\n\t(2) load a character\n\t(3) exit\n");
    int choice;
    choice = getNumberInput("");

    struct Character *character = initialiseCharacter();
    if (character == NULL) {
        return NULL;
    }
    
    int status = EXIT_SUCCESS;
    switch (choice) {
        case 1:
            status = createCharacter(character, db);
            break;
        case 2:
            status = loadCharacter(character, db);
            break;
        case 3:
            freeCharacter(character);
            exit(EXIT_SUCCESS);
        default:
            printf("choice not recognised\n");
            status = EXIT_FAILURE;
    }
    if (status == EXIT_FAILURE) {
        freeCharacter(character);
        return NULL;
    }
    return character;
}

int createCharacter(struct Character *character, sqlite3 *db) {
    //creating name
    char *name = getStringInput("name: ");
    character->name = name;

    //creating class
    printf("class:\n\n");
    for (int i=0; i < ARR_SIZE(charClassNames); i++) {
        printf("\t(%d) %s\n", i+1, charClassNames[i]);
    }
    int classNum = getNumberInput("\n\t-> ");
    if (classNum < 1 || classNum > ARR_SIZE(charClassNames)) {
        error("invalid input");
        return EXIT_FAILURE;
    }
    enum CharClass charClass = --classNum;
    character->charClass = charClass;

    //creating race
    printf("race:\n\n");
    for (int i=0; i < ARR_SIZE(charRaceNames); i++) {
        printf("\t(%d) %s\n", i+1, charRaceNames[i]);
    }
    int raceNum = getNumberInput("\n\t-> ");
    if (raceNum < 1 || raceNum > ARR_SIZE(charRaceNames)) {
        error("invalid input");
        return EXIT_FAILURE;
    }
    enum CharRace race = --raceNum;
    character->race = race;

    //creating level
    printf("\ndo you want to start from default level (level 1)? Y/N: ");
    char defaultLevel = getchar();
    cleanInputBuffer();
    if (defaultLevel == 'Y') character->level = 1;
    else if (defaultLevel == 'N') {
        int startingLevel;
        startingLevel = getNumberInput("\nstarting level: ");
        if (startingLevel<1 || startingLevel>20){
            error("invalid starting level");
            return EXIT_FAILURE;
        }
        character->level = startingLevel;
    } else {
        error("invalid input");
        return EXIT_FAILURE;
    }

    //creating stats
    struct Stats *stats = initStats();
    if (stats == NULL) {
        return EXIT_FAILURE;
    }
    character->stats = stats;

    character->id = saveCharacter(*character, db);
    if (character->id == -1) return EXIT_FAILURE;    

    return EXIT_SUCCESS;
}

void freeCharacter(struct Character *character) {
    if (character != NULL) {
        if (character->name != NULL) {
            free(character->name);
        }

        if (character->stats != NULL) {
            free(character->stats);
        }

        free(character);
    }
}

struct Character * initialiseCharacter() {
    struct Character *character = (struct Character*)malloc(sizeof(struct Character));
    if (character == NULL) {
        return NULL;
    }
    
    character->name = NULL;
    character->stats = NULL;

    return character;
}

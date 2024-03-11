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

char *charDirName = ".characters/";

struct Character* characterMenu() {
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
            status = createCharacter(character);
            break;
        case 2: {
            status = loadCharacter(character);
            if (character == NULL) status = EXIT_FAILURE;
            }
            break;
        case 3:
            freeCharacter(character);
            exit(EXIT_SUCCESS);
        default:
            printf("choice not recognised\n");
            status = EXIT_FAILURE;
    }
    if (status == EXIT_FAILURE) {
        //TODO
        freeCharacter(character);
        exit(EXIT_FAILURE);
    }
    return character;
}

int createCharacter(struct Character *character) {
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

    saveCharacter(*character);

    return EXIT_SUCCESS;
}

int loadCharacter(struct Character *character) {
    char *name = getStringInput("name: ");
    if (name == NULL) {
        return EXIT_FAILURE;
    }

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
}

int saveCharacter(const struct Character character) {
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
}


void freeCharacter(struct Character *character) {
    if (character != NULL) {
        // Free the name member if it has been allocated
        if (character->name != NULL) {
            free(character->name);
        }

        // Free the stats member if it has been allocated
        if (character->stats != NULL) {
            free(character->stats);
        }

        // Free the entire Character structure
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

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
    scanf("%d", &choice);
    cleanInputBuffer();

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
    char *name = readInput("name");
    character->name = name;

    //creating class
    int classNum;
    printf("class:\n\n");
    for (int i=0; i < sizeof(charClassNames) / sizeof(charClassNames[0]); i++) {
        printf("\t(%d) %s\n", i+1, charClassNames[i]);
    }
    printf("\n\t-> ");
    scanf("%d", &classNum);
    cleanInputBuffer();
    enum CharClass charClass = --classNum;
    character->charClass = charClass;

    //creating race
    int raceNum;
    printf("race:\n\n");
    for (int i=0; i<sizeof(charRaceNames) / sizeof(charRaceNames[0]); i++) {
        printf("\t(%d) %s\n", i+1, charRaceNames[i]);
    }
    printf("\n\t-> ");
    scanf("%d", &raceNum);
    cleanInputBuffer();
    enum CharRace race = --raceNum;
    character->race = race;

    //creating level
    printf("\ndo you want to start from default level (level 1)? Y/N: ");
    char defaultLevel;
    scanf("%c", &defaultLevel);
    if (defaultLevel == 'Y') character->level = 1;
    else if (defaultLevel == 'N') {
        printf("\nstarting level: ");
        int startingLevel;
        scanf("%d", &startingLevel);
        cleanInputBuffer();
        if (startingLevel<1 || startingLevel>20){
            perror("invalid starting level");
            return EXIT_FAILURE;
        }
        character->level = startingLevel;
    } else {
        perror("invalid input");
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
    char *name = readInput("name");
    if (name == NULL) {
        return EXIT_FAILURE;
    }

    DIR *dir = opendir(charDirName);
    if (dir == NULL) {
        perror("opening characters directory failed");
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
        printf("\ncould not find character: %s", name);
        free(name);
        return EXIT_FAILURE;
    }

    char *fname = addStrings(charDirName, name);
    
    FILE *file = fopen(fname, "r");
    free(fname);
    if (file == NULL) {
        perror("file opening failed");
        free(name);
        return EXIT_FAILURE;
    }

    if (character == NULL) {
        perror("character struct argument not properly initialised");
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
        perror("characters directory setup failed");
        return EXIT_FAILURE;
    }
    char *fname = addStrings(charDirName, character.name);
    
    FILE *file = fopen(fname, "w");
    free(fname);
    if (file == NULL) {
        perror("file creation failed");
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

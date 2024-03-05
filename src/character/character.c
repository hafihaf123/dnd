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
#include "../dice/dice.h"
#include "../utils.h"

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
            char *loadName = NULL;
            size_t len = 0;
            printf("\nname: ");
            ssize_t read = getline(&loadName, &len, stdin);
            if (read == -1) {
                perror("read of name failed");
                status = EXIT_FAILURE;
                break;
            }

            status = loadCharacter(loadName, character);
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
    char *name;
    size_t len = 0;
    printf("\nname: ");
    ssize_t read = getline(&name, &len, stdin);
    if (read == -1) {
        perror("read of name failed");
        return EXIT_FAILURE;
    }
    character->name = name;

    //creating class
    int classNum;
    printf("class:\n\n\t(1) Barbarian\n\t(2) Druid\n\n\t-> ");
    scanf("%d", &classNum);
    cleanInputBuffer();
    enum CharClass charClass;
    switch (classNum) {
        case 1:
            charClass = BARBARIAN;
            break;
        case 2:
            charClass = DRUID;
            break;
        default:
            perror("class name not recognized");
            return EXIT_FAILURE;
    }
    character->charClass = charClass;

    //creating race
    int raceNum;
    printf("race:\n\n\t(1) Human\n\t(2) Elf\n\t(3) Dwarf\n\n\t-> ");
    scanf("%d", &raceNum);
    cleanInputBuffer();
    enum CharRace race;
    switch (raceNum) {
        case 1:
            race = HUMAN;
            break;
        case 2:
            race = ELF;
            break;
        case 3:
            race = DWARF;
            break;
        default:
            perror("race name not recognized");
            return EXIT_FAILURE;
    }
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
    character->stats = stats;

    saveCharacter(*character);

    return EXIT_SUCCESS;
}

int loadCharacter(char *name, struct Character *character) {
    DIR *dir = opendir(charDirName);
    if(dir == NULL) {
        perror("opening characters directory failed");
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
        return EXIT_FAILURE;
    }

    char *fname = addStrings(charDirName, name);
    
    FILE *file = fopen(fname, "r");
    free(fname);
    if (file == NULL) {
        perror("file opening failed");
        return EXIT_FAILURE;
    }

    if (character == NULL) {
        perror("character struct argument not properly initialised");
        return EXIT_FAILURE;
    }
    //loading name
    character->name = name;
    printf("name: %s\n", name);
    printf("character name: %s\n", character->name);
    //loading class
    char *className = (char *)malloc(15);
    fscanf(file, "%s", className);
    character->charClass = getEnumFromName(className, charClassNames, ARR_SIZE(charClassNames));
    printf("class name: %s\n", className);
    free(className);
    //loading race
    char *raceName = (char *)malloc(15);
    fscanf(file, "%s", raceName);
    character->race = getEnumFromName(raceName, charRaceNames, ARR_SIZE(charRaceNames));
    printf("race name: %s\n", raceName);
    free(raceName);
    //loading level
    int level;
    fscanf(file, "%d", &level);
    character->level = level;
    printf("level: %d\n", character->level);
    //loading stats
    struct Stats *stats = (struct Stats *)malloc(sizeof(struct Stats));

    int strength;
    fscanf(file, "%d", &strength);
    stats->strength = strength;
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

struct Stats* initStats() {
    struct Stats *stats = malloc(sizeof(struct Stats));
    int points[6];
    for(int i=0; i<6; i++) {
        int rolls[4];
        for (int ii=0; ii<4; ii++) {
            rolls[ii] = roll("1d6");
        }
        points[i] = sumOfArrExceptMin(rolls, ARR_SIZE(rolls));
    }

    printf("\npoints for stats:\n");
    for(int i=0; i<6; i++) {
        printf("(%d)\t%d\n", i+1, points[i]);
    }

    int choice;
    //strength
    printf("\nstrength: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        free(stats);
        return NULL;
    }
    stats->strength = points[choice-1];

    //dexterity
    printf("\ndexterity: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        free(stats);
        return NULL;
    }
    stats->dexterity = points[choice-1];

    //constitution
    printf("\nconstitution: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        free(stats);
        return NULL;
    }
    stats->constitution = points[choice-1];

    //intelligence
    printf("\nintelligence: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        free(stats);
        return NULL;
    }
    stats->intelligence = points[choice-1];

    //wisdom
    printf("\nwisdom: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        free(stats);
        return NULL;
    }
    stats->wisdom = points[choice-1];

    //charisma
    printf("\ncharisma: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        free(stats);
        return NULL;
    }
    stats->charisma = points[choice-1];

    return stats;
}

void freeCharacter(struct Character *character) {
    printf("1");
    if (character != NULL) {
        // Free the name member if it has been allocated
        if (character->name != NULL) {
            printf("2");
            free(character->name);
        }

        // Free the stats member if it has been allocated
        if (character->stats != NULL) {
            printf("3");
            free(character->stats);
        }

        // Free the entire Character structure
        printf("4");
        free(character);
    }
}

struct Character * initialiseCharacter() {
    struct Character *character = (struct Character*)malloc(sizeof(struct Character));
    if (character == NULL)
    {
        return NULL;
    }
    
    character->name = NULL;
    character->stats = NULL;

    return character;
}

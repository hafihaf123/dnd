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

struct Character characterMenu() {
    printf("do you want to\n\t(1) create a character\n\t(2) load a character\n\t(3) exit\n");
    int choice;
    scanf("%d", &choice);
    cleanInputBuffer();

    struct Character character;
    int status = EXIT_SUCCESS;
    switch (choice) {
        case 1:
            status = createCharacter(&character);
            break;
        case 2:
            //status = loadCharacter(&character);
            break;
        case 3:
            exit(EXIT_SUCCESS);
        default:
            perror("choice not recognised");
            exit(EXIT_FAILURE);
    }
    if (status == EXIT_FAILURE) {
        //TODO
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
    free(name);

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

    //saveCharacter(*character);

    return EXIT_SUCCESS;
}

//int loadCharacter(struct Character *character);

//int saveCharacter(struct Character character);

struct Stats* initStats() {
    struct Stats *stats = NULL;
    int points[6];
    for(int i=0; i<6; i++) {
        int rolls[4];
        for (int ii=0; ii<4; ii++) {
            rolls[ii] = roll("1d6");
        }
        points[i] = sumOfArrExceptMin(rolls, 4);
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
        return NULL;
    }
    stats->strength = points[choice-1];

    //constitution
    printf("\nconstitution: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        return NULL;
    }
    stats->constitution = points[choice-1];

    //dexterity
    printf("\ndexterity: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        return NULL;
    }
    stats->dexterity = points[choice-1];

    //intelligence
    printf("\nintelligence: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        return NULL;
    }
    stats->intelligence = points[choice-1];

    //wisdom
    printf("\nwisdom: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        return NULL;
    }
    stats->wisdom = points[choice-1];

    //charisma
    printf("\ncharisma: ");
    scanf("%d", &choice);
    cleanInputBuffer();
    if (choice<1 || choice>6) {
        perror("invalid choice input - it must be in <1,6>");
        return NULL;
    }
    stats->charisma = points[choice-1];

    return stats;
}


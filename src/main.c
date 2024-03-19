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

int main() {
    srand(time(NULL));

    sqlite3 *db = setupDatabase("characters.db");

    struct Character *character = characterMenu(db);

    printf("\n\nname: %s\nlevel: %d\n", character->name, character->level);

    freeCharacter(character);

    return EXIT_SUCCESS;
}

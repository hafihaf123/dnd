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
#include "character/character.h"

int main() {
    struct Character character = characterMenu();

    printf("\n\nname: %s\nlevel: %d\n", character.name, character.level);

    return EXIT_SUCCESS;
}

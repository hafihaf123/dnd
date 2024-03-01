/*
 * =====================================================================================
 *
 *       Filename:  dice.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/29/24 16:43:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "dice.h"

int roll(char *roll) {
    char *copy = strdup(roll);
    if (roll == NULL || copy == NULL) {
        perror("error: input string is null");
        return -1;
    }
    char *token = strtok(copy, "d");
    if (token == NULL) {
        perror("error: tokenization failed");
        return -1;
    }
    int rolls = atoi(token);

    token = strtok(NULL, "d");
    if (token == NULL) {
        perror("error: second tokenization failed");
        return -1;
    }
    int sides = atoi(token);

    int res = 0;
    for(int i=0; i<rolls; i++) {
        res += rand()%sides + 1;
    }
    return res;
}

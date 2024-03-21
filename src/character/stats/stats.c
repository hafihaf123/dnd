/*
 * =====================================================================================
 *
 *       Filename:  stats.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/07/24 09:44:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
///file stats.c

#include "stats.h"
#include "dice.h"
#include "utils.h"

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

    int choice[6];
    for (int i=0; i<6; i++) {
        int n;
        printf("\n%s", statNames[i]);
        n = getNumberInput(": ");
        if (n<1 || n>6) {
            error("invalid choice input - it must be in <1,6>");
            free(stats);
            return NULL;
        }
        for (int ii=0; ii<i; ii++) {
            if (n == choice[ii]+1) {
                error("invalid choice input - it was used previously");
                free(stats);
                return NULL;
            }
        }
        choice[i] = n-1;
    }
    stats->strength = points[choice[0]];
    stats->constitution = points[choice[1]];
    stats->dexterity = points[choice[2]];
    stats->intelligence = points[choice[3]];
    stats->wisdom = points[choice[4]];
    stats->charisma = points[choice[5]];

    return stats;
}

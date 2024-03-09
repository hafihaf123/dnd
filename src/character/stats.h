/*
 * =====================================================================================
 *
 *       Filename:  stats.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/07/24 09:47:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef STATS_H
#define STATS_H

#include <stdlib.h>
#include <stdio.h>

struct Stats {
    int strength;
    int constitution;
    int dexterity;
    int intelligence;
    int wisdom;
    int charisma;
};

struct Stats* initStats();

#endif /* STATS_H */

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
/// @file stats.h

#ifndef STATS_H
#define STATS_H

#include <stdlib.h>
#include <stdio.h>

/// @brief struct for stats of a character
struct Stats {
    int strength;
    int constitution;
    int dexterity;
    int intelligence;
    int wisdom;
    int charisma;
};

/// @brief array containing the labels for Stats members
static const char * const statNames[] = {
    "strength",
    "constitution",
    "dexterity",
    "intelligence",
    "wisdom",
    "charisma"
};

/**
 * @brief function for initialising a Stats instance with user input
 * 
 * @return struct Stats* initialised Stats instance (must be freed)
 */
struct Stats* initStats();

#endif /* STATS_H */

/**
 * @file stats.h
 * @author hafihaf123
 * @brief header for stats.c
 */
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

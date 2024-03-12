/*
 * =====================================================================================
 *
 *       Filename:  char_race.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/07/24 14:58:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
/// @file char_race.h

#ifndef CHAR_RACE_H
#define CHAR_RACE_H

/// @brief enum containing the possible character races
enum CharRace {
    HUMAN,
    ELF,
    DWARF
};

/// @brief array containing the labels for #CharRace
static const char * const charRaceNames[] = {
    [HUMAN] = "HUMAN",
    [ELF] = "ELF",
    [DWARF] = "DWARF"
};

#endif /* CHAR_RACE_H */

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
#ifndef CHAR_RACE_H
#define CHAR_RACE_H

enum CharRace {
    HUMAN,
    ELF,
    DWARF
};

static const char * const charRaceNames[] = {
    [HUMAN] = "HUMAN",
    [ELF] = "ELF",
    [DWARF] = "DWARF"
};

#endif /* CHAR_RACE_H */

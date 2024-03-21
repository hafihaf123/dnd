/**
 * @file char_race.h
 * @author hafihaf123
 * @brief header for CharRace
 */
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

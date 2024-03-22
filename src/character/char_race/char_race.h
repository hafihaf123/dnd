/**
 * @file char_race.h
 * @author hafihaf123
 * @brief header for CharRace
 */
#ifndef CHAR_RACE_H
#define CHAR_RACE_H

/// @brief enum containing the possible character races
enum CharRace {
    DWARF,
    ELF,
    HALFLING,
    HUMAN,
    DRAGONBORN,
    GNOME,
    HALF_ELF,
    HALF_ORC,
    TIEFLING
};

/// @brief array containing the labels for #CharRace
static const char * const charRaceNames[] = {
    [DWARF] = "DWARF",
    [ELF] = "ELF",
    [HALFLING] = "HALFLING",
    [HUMAN] = "HUMAN",
    [DRAGONBORN] = "DRAGONBORN",
    [GNOME] = "GNOME",
    [HALF_ELF] = "HALF_ELF",
    [HALF_ORC] = "HALF_ORC",
    [TIEFLING] = "TIEFLING"
};

#endif /* CHAR_RACE_H */

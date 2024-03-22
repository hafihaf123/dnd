/**
 * @file char_class.h
 * @author hafihaf123
 * @brief header for CharClass
 */
#ifndef CHAR_CLASS_H
#define CHAR_CLASS_H

/// @brief enum containing the possible character classes
enum CharClass {
    BARBARIAN,
    BARD,
    CLERIC,
    DRUID,
    FIGHTER,
    MONK,
    PALADIN,
    RANGER,
    ROGUE,
    SORCERER,
    WARLOCK,
    WIZARD
};

/// @brief array containing the labels for #CharClass
static const char * const charClassNames[] = {
    [BARBARIAN] = "BARBARIAN",
    [BARD] = "BARD",
    [CLERIC] = "CLERIC",
    [DRUID] = "DRUID",
    [FIGHTER] = "FIGHTER",
    [MONK] = "MONK",
    [PALADIN] = "PALADIN",
    [RANGER] = "RANGER",
    [ROGUE] = "ROGUE",
    [SORCERER] = "SORCERER",
    [WARLOCK] = "WARLOCK",
    [WIZARD] = "WIZARD",
};

#endif /* CHAR_CLASS_H */
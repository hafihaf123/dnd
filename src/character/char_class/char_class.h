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
    DRUID,
    MAGE,
    MONK,
    PALADIN,
    PRIEST,
    RANGER,
    ROGUE,
    SORCERER,
    WARLOCK
};

/// @brief array containing the labels for #CharClass
static const char * const charClassNames[] = {
    [BARBARIAN] = "BARBARIAN",
    [DRUID] = "DRUID",
    [MAGE] = "MAGE",
    [MONK] = "MONK",
    [PALADIN] = "PALADIN",
    [PRIEST] = "PRIEST",
    [RANGER] = "RANGER",
    [ROGUE] = "ROGUE",
    [SORCERER] = "SORCERER",
    [WARLOCK] = "WARLOCK"
};

#endif /* CHAR_CLASS_H */

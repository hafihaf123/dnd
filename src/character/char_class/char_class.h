/*
 * =====================================================================================
 *
 *       Filename:  char_class.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/07/24 14:51:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CHAR_CLASS_H
#define CHAR_CLASS_H

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

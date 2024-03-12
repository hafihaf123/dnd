/*
 * =====================================================================================
 *
 *       Filename:  dice.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/29/24 16:39:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
/// @file dice.h
#ifndef DICE_H
#define DICE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief simulates a roll of x n-sided dices
 * 
 * @param roll in format "xdn" where x is the number of rolls and n is the number of sides
 * @return int sum of all x rolls
 */
int roll(char *roll);

#endif /* DICE_H */

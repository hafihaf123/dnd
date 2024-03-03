/*
 * =====================================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/29/24 23:23:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int sumOfArrExceptMin(int arr[]);
void cleanInputBuffer();
int setupDir(char *name);
char * addStrings(char *string1, char *string2);
int getEnumFromName(const char *name, const char * const *enumStringMap);

#endif /* UTILS_H */

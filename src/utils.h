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
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>

int sumOfArrExceptMin(int arr[], int size);
void cleanInputBuffer();
int setupDir(char *name);

#endif /* UTILS_H */

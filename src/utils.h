/**
 * @file utils.h
 * @author hafihaf123
 * @brief header for utils.c
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0])) ///< Number of elements in array

/**
 * @brief sum of elements in Integer array except smallest
 * 
 * @details sum of all elements in an Integer array except the smallest one.
 * If there are two 'smallest' numbers, it subtracts just one
 * 
 * @param arr array
 * @param size size of the array
 * @return int sum of all elements of arr except smallest
 */
int sumOfArrExceptMin(int arr[], size_t size);

/// @brief cleans the input buffer
void cleanInputBuffer();

/**
 * @brief creates a directory in root, if it doesn't exist.
 * 
 * @details creates a new directory in the root directory of the project.
 * If it already exists, it does nothing.
 * 
 * @param name Name of the directory to set up
 * @return int EXIT_SUCCESS or EXIT_FAILURE
 */
int setupDir(char *name);

/**
 * @brief returns a string comprised of its arguments
 * 
 * @param string1 first string
 * @param string2 second string
 * @return char* concatted string of the 2 arguments
 */
char * addStrings(const char *string1, const char *string2);

/**
 * @brief get the Enum index from name of its label
 * 
 * @param name a name of a label to check
 * @param enumStringMap array containing the labels of the enum
 * @param size size of the enumStringMap array
 * @return int the index of name in enumStringMap; if doesn't contain -> -1
 */
int getEnumFromName(const char *name, const char * const *enumStringMap, size_t size);

/**
 * @brief get input as string
 * 
 * @param message message to be displayed when prompting for input
 * @return char* input from user
 */
char * getStringInput(const char *message);

/**
 * @brief get input as an Integer
 * 
 * @param message message to be displayed when prompting for input
 * @return int number input from user
 */
int getNumberInput(const char *message);

/**
 * @brief print an error message to the console, formatted as follows: "Error: %s\n\n"
 * 
 * @param message error message
 */
void error(const char *message);

#endif /* UTILS_H */

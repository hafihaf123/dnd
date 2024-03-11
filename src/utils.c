/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/29/24 23:19:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
/// @file utils.c
#include "utils.h"

/**
 * @brief Sum of elements in Integer array except smallest
 * 
 * @details the sum of all elements in an Integer array except the smallest one.
 * If there are two 'smallest' numbers, it subtracts just one
 * 
 * @param arr array
 * @param size size of @param arr
 * @return int Sum of all elements of arr except smallest
 */
int sumOfArrExceptMin(int arr[], size_t size) {
    int min = INT_MAX;
    int sum = 0;

    // Iterate through the array
    for (int i = 0; i < size; i++) {
        // Update min if the current element is smaller
        if (arr[i] < min) {
            min = arr[i];
        }
        // Calculate the sum of all elements
        sum += arr[i];
    }

    // Subtract the smallest element from the sum
    sum -= min;

    return sum;
}

/**
 * @brief Cleans the input buffer
 * 
 */
void cleanInputBuffer() {
    int c;
    while((c=getchar()) != '\n' && c != EOF);
}

/**
 * @brief Creates a directory in root, if it doesn't exist.
 * 
 * @details a new directory in the root directory of the project.
 * If it already exists, it does nothing.
 * 
 * @param name Name of the directory to set up
 * @return int 1 if failed, 0 if successful
 */
int setupDir(char *name) {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        return EXIT_FAILURE;
    }
    struct dirent *entry;
    int dirExists = 0;
    while((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, name) == 0) { 
            dirExists = 1;
            break;
        }
    }
    if (dirExists != 1) mkdir(name, 0775);
    closedir(dir);
    return EXIT_SUCCESS;
}

/**
 * @brief Returns a string comprised of its arguments
 * 
 * @param string1 first string
 * @param string2 second string
 * @return char* concated string of the 2 arguments
 */
char * addStrings(char *string1, char *string2) {
    size_t resultSize = strlen(string1) + strlen(string2) + 1;
    char *result = (char*)malloc(resultSize);
    if (result == NULL) {
        perror("string memory allocation failed");
        return NULL;
    }
    strcpy(result, string1);
    strcat(result, string2);
    return result;
}

/**
 * @brief Get the Enum index from name of its label
 * 
 * @param name a name of a label to check
 * @param enumStringMap array containing the labels of the enum
 * @param size size of the enumStringMap array
 * @return int the index of name in enumStringMap; if doesn't contain -> -1
 */
int getEnumFromName(const char *name, const char * const *enumStringMap, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(name, enumStringMap[i]) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Get input as string
 * 
 * @param message message to be displayed when prompting for input
 * @return char* input from user
 */
char * getStringInput(const char *message) {
    char *input = NULL;
    size_t len = 0;
    printf("%s", message);
    ssize_t read = getline(&input, &len, stdin);
    if (read == -1) {
        perror("input read failed");
        free(input);
        return NULL;
    }
    char *newlinePos = strchr(input, '\n');
    if (newlinePos != NULL) *newlinePos = '\0';

    return input;
}

/**
 * @brief Get input as an Integer
 * 
 * @param message message to be displayed when prompting for input
 * @return int input from user
 */
int getNumberInput(const char *message) {
    int number;

    while (1) {
        char *input = getStringInput(message);

        char *endptr;
        number = strtol(input, &endptr, 10);

        if (endptr == input) {
            printf("Incorrect integer input. Please enter a valid number.\n");
        } else {
            free(input);
            return number;
        }
        free(input);
    }
}

/**
 * @brief print an error message to the console
 * 
 * @details the output to console is formatted as follows: "Error: %s\n"
 * 
 * @param message error message
 */
void error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
}

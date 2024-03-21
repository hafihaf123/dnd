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

#include "utils.h"

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

void cleanInputBuffer() {
    int c;
    while((c=getchar()) != '\n' && c != EOF);
}

int setupDir(char *name) {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        error("failed opening the root directory");
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

char * addStrings(const char *string1, const char *string2) {
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

int getEnumFromName(const char *name, const char * const *enumStringMap, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(name, enumStringMap[i]) == 0) {
            return i;
        }
    }
    return -1;
}

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

void error(const char *message) {
    fprintf(stderr, "Error: %s\n\n", message);
}

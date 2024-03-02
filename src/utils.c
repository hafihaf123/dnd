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

int sumOfArrExceptMin(int arr[], int size) {
    int min = INT_MAX;
    int sum = 0;

    // Iterate through the array
    for (int i = 0; i<size; i++) {
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
        closedir(dir);
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

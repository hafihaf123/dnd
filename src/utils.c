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

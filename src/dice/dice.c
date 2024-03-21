/**
 * @file dice.c
 * @author hafihaf123
 * @brief logic for dice rolls
 */
#include "dice.h"
#include "utils.h"

int roll(char *roll) {
    if (roll == NULL) {
        error("input cannot be null");
        return -1;
    }
    if (strchr(roll, 'd') == NULL) {
        error("invalid input format - it doesn't include 'd'");
        return -1;
    }
    char *copy = strdup(roll);
    if (copy == NULL) {
        error("string duplication failed");
        free(copy);
        return -1;
    }
    char *token = strtok(copy, "d");
    if (token == NULL || atoi(token)<0) {
        error("tokenization failed");
        free(copy);
        return -1;
    }
    int rolls = atoi(token);

    token = strtok(NULL, "d");
    if (token == NULL || atoi(token)<=0) {
        error("second tokenization failed");
        free(copy);
        return -1;
    }
    int sides = atoi(token);
    free(copy);

    int res = 0;
    for(int i=0; i<rolls; i++) {
        res += rand()%sides + 1;
    }
    return res;
}

/**
 * @file test.c
 * @author hafihaf123
 * @brief testing functions using MinUnit
 */
#include "minunit.h"
#include "../src/dice/dice.h"

MU_TEST(test_roll) {
    mu_check(roll("2d6")>=2 && roll("2d6")<=12);
    mu_assert_int_eq(-1, roll(""));
    mu_assert_int_eq(-1, roll(NULL));
    mu_assert_int_eq(-1, roll("invalid_input"));
    mu_assert_int_eq(0, roll("0d6"));
    mu_assert_int_eq(-1, roll("2d0"));
    mu_assert_int_eq(-1, roll("-2d6"));
    mu_assert_int_eq(-1, roll("2d-6"));
    mu_check(roll("1d1") == 1);
    mu_check(roll("1d20") >= 1 && roll("1d20") <= 20);
    mu_check(roll("5d1") == 5);
    mu_check(roll("3d6") >= 3 && roll("3d6") <= 18);
    mu_check(roll("1000d1000") >= 1000 && roll("1000d1000") <= 1000000);
    mu_assert_int_eq(-1, roll("2x6"));
}
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_roll);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
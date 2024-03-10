#include "unity.h"
#include "dice.h"

void setUp(void) {
    // set up tasks
}

void tearDown(void) {
    // clean up tasks
}

void test_roll_valid_input(void) {
    // Test valid input
    TEST_ASSERT_INT_WITHIN(2.5, 3.5, roll("1d6")); // Expected: 1 to 6
    TEST_ASSERT_INT_WITHIN(4, 6, roll("2d5")); // Expected: 2 to 10
    TEST_ASSERT_INT_WITHIN(2, 4, roll("2d3")); // Expected: 2 to 6
}

void test_roll_invalid_input(void) {
    // Test invalid input
    TEST_ASSERT_EQUAL_INT(-1, roll(NULL)); // NULL input
    TEST_ASSERT_EQUAL_INT(-1, roll("")); // Empty string
    TEST_ASSERT_EQUAL_INT(-1, roll("2")); // Missing 'd'
    TEST_ASSERT_EQUAL_INT(-1, roll("d6")); // Missing number before 'd'
    TEST_ASSERT_EQUAL_INT(-1, roll("2d")); // Missing number after 'd'
    TEST_ASSERT_EQUAL_INT(-1, roll("2d5x")); // Extra characters
}

/* int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_roll_valid_input);
    RUN_TEST(test_roll_invalid_input);
    return UNITY_END();
} */
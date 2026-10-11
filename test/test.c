#include <unity.h>
//#include ""

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
    //test stuff
}

void test_function_should_doAlsoDoBlah(void) {
    //more test stuff
}

// not needed when using generate_test_runner.rb
int main() {
    UNITY_BEGIN();
    TEST_ASSERT_TRUE(3+3 == 6)
    return UNITY_END();
}

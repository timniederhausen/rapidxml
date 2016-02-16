void test_small_static();
void test_small_dynamic();

#include "../test_utils.hpp"

int main()
{
    test_small_static();
    test_small_dynamic();
    return test::final_results();
}

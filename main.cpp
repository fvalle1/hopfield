#include "memory.h"
#include "model.h"
#include "tests/test.h"
#include "device.h"

using namespace std;

//#undef __APPLE__

int main()
{
    PrintDevices();

    Test<std::function<void()>, StopwatchMillis>(test_1, "test 1");
    Test<std::function<void()>, StopwatchMillis>(test_2, "test 2");
    Test<std::function<void()>, StopwatchMillis>(test_3, "test 3");
    Test<std::function<void()>, StopwatchMillis>(test_4, "test 4");
    Test<std::function<void()>, StopwatchMillis>(test_5, "test 5");
    Test<std::function<void()>, StopwatchMillis>(test_6, "test 6");
    Test<std::function<void()>, StopwatchMillis>(test_7, "test 7");
    Test<std::function<void()>, StopwatchMillis>(test_8, "test 8");
    Test<std::function<void()>, StopwatchMillis>(test_9, "test 9");


    return 0;
}

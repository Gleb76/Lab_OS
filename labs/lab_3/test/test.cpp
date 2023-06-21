#include <iostream>
#include <cassert>
#include <sstream>
#include "worker.h"

using namespace std;

void testCreateInformation()
{
    // Test with valid input
    stringstream input("5\n1.0\n2.0\n3.0\n4.0\n5.0\n3\n2.0\n");
    Information expected{ 5, new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 }, 3, 2.0 };
    auto result = createInformation(input);
    assert(result.arraySize == expected.arraySize);
    assert(result.k == expected.k);
    assert(result.A == expected.A);
    for (int i = 0; i < result.arraySize; i++) {
        assert(result.originalArray[i] == expected.originalArray[i]);
    }

    // Test with invalid input
    stringstream input2("abc\n");
    assert(createInformation(input2).originalArray == nullptr);
}

void testWorkThread()
{
    // Test with valid input
    Information info{ 5, new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 }, 3, 2.0 };
    workThread(&info);
    assert(info.arraySize == 2);

    // Test with invalid input
    Information info2{ 0, nullptr, 0, 0.0 };
    workThread(&info2);
    assert(info2.arraySize == 0);
}

void testMultElementThread()
{
    // Test with valid input
    Information info{ 5, new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 }, 3, 2.0 };
    multElementThread(&info);
    assert(multResult == 20);

    // Test with invalid input
    Information info2{ 0, nullptr, 0, 0.0 };
    multElementThread(&info2);
    assert(multResult == 1);
}

int main()
{
    testCreateInformation();
    testWorkThread();
    testMultElementThread();
    cout << "All tests passed!" << endl;
    return 0;
}

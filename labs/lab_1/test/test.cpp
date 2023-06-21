#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include "worker.h"

using namespace std;

void testCreateArray()
{
    // Test with valid input
    stringstream input("5\n1.0\n2.0\n3.0\n4.0\n5.0\n");
    vector<double> expected{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    auto result = createArray(input);
    assert(result.size() == expected.size());
    assert(result == expected);

    // Test with invalid input
    stringstream input2("abc\n");
    assert(createArray(input2).empty());
}

void testRunWorker()
{
    // Test with valid input
    Data data;
    data.masOfInput = new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    data.sizeInput = 5;
    runWorker(data, 3);
    assert(data.sizeOutput == 1);

    // Test with invalid input
    Data data2;
    data2.masOfInput = nullptr;
    data2.sizeInput = 0;
    runWorker(data2, 3);
    assert(data2.sizeOutput == 0);
}

void testCheckResult()
{
    // Test with valid input
    Data data;
    data.masOfInput = new double[5]{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    data.sizeInput = 5;
    data.masOfOutput = new double[5]{ 1.0, 1.5, 2.0, 3.0, 3.5 };
    data.sizeOutput = 5;
    stringstream expected("Amount of numbers with the same integer parts equals: 2\n");
    stringstream result;
    checkResult(data, result);
    assert(result.str() == expected.str());

    // Test with invalid input
    Data data2;
    data2.masOfInput = nullptr;
    data2.sizeInput = 0;
    data2.masOfOutput = nullptr;
    data2.sizeOutput = 0;
    stringstream expected2("Amount of numbers with the same integer parts equals: 0\n");
    stringstream result2;
    checkResult(data2, result2);
    assert(result2.str() == expected2.str());
}

int main()
{
    testCreateArray();
    testRunWorker();
    testCheckResult();
    cout << "All tests passed!" << endl;
    return 0;
}

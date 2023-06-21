#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

mutex critical_section;
mutex hOutEvent, hMultEvent;
condition_variable_any cv;

vector<double> finalArray;
double result = 1;
int k = 0;
double A;

void Work(vector<double>& arr, int size, int& k, double& A) {
    cout << "--- workThread is started" << endl;

    int finalArraytInterval = 100;

    finalArray = vector<double>(size);
    int finalArraySize = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < A) {
            finalArray[finalArraySize] = arr[i];
            finalArraySize++;
        }
        else {
            arr[i - finalArraySize] = arr[i];
        }

        this_thread::sleep_for(chrono::milliseconds(finalArraytInterval));
    }

    // Move the elements smaller than A to the end of the final array
    for (int i = 0; i < finalArraySize; i++) {
        arr[size - i - 1] = finalArray[i];
    }

    cout << "  finalArray elements: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "--- Thread work is finished" << endl << endl;
    cv.notify_one();
}

void MultElement(vector<double>& arr, int size, int& k) {
    unique_lock<mutex> critical_section_locker(critical_section);
    unique_lock<mutex> event_locker(hMultEvent);
    cv.wait(event_locker);
    cout << "--- Thread MultElement is started" << endl;
    cout << "  ";

    for (int i = k; i < size; ++i) {
        result *= arr[i];
    }
    
    cout << "  Mult from position " << k << " to the end: " << result << endl;
    cout << "--- Thread MultElement is finished" << endl;
    //cv.notify_one();
    critical_section_locker.unlock();
}

TEST(ProgramTest, InputData) {
    // Arrange
    stringstream input;
    input << "5\n1 2 3 4 5\n2\n3";
    streambuf* cin_backup = cin.rdbuf(input.rdbuf());

    // Act
    int size;
    cout << "Enter size of array: ";
    cin >> size;
    cout << endl << "Enter elements of array: " << endl;

    vector<double> arr(size);

    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    // Assert
    EXPECT_EQ(size, 5);
    EXPECT_THAT(arr, testing::ElementsAre(1, 2, 3, 4, 5));

    cin.rdbuf(cin_backup);
}

TEST(ProgramTest, WorkFunction) {
    // Arrange
    vector<double> arr = {1, 2, 3, 4, 5};
    int size = arr.size();
    int k = 0;
    double A = 3;

    // Act
    Work(arr, size, k, A);

    // Assert
    EXPECT_THAT(arr, testing::ElementsAre(3, 4, 5, 1, 2));
}

TEST(ProgramTest, MultElementFunction) {
    // Arrange
    vector<double> arr = {3, 4, 5, 1, 2};
    int size= arr.size();
    int k = 2;

    // Act
    MultElement(arr, size, k);

    // Assert
    EXPECT_DOUBLE_EQ(result, 10);
}

TEST(ProgramTest, OutputData) {
    // Arrange
    stringstream input;
    input << "5\n1 2 3 4 5\n2\n3";
    streambuf* cin_backup = cin.rdbuf(input.rdbuf());

    stringstream output;
    streambuf* cout_backup = cout.rdbuf(output.rdbuf());

    // Act
    main();

    // Assert
    EXPECT_EQ(output.str(), "Enter size of array: \n"
                             "\n"
                             "Enter elements of array: \n"
                             "\n"
                             "-----------------------------------\n"
                             "\n"
                             "Input data: \n"
                             "Size: 5\n"
                             "Elements of array: 1 2 3 4 5 \n"
                             "\n"
                             "Enter k: \n"
                             "\n"
                             "Enter A: \n"
                             "\n"
                             "--- workThread is started\n"
                             "  finalArray elements: 3 4 5 1 2 \n"
                             "--- Thread work is finished\n"
                             "\n"
                             "Elements of array: 3 4 5 1 2 \n"
                             "Mult of Elements: 10\n");
    
    cin.rdbuf(cin_backup);
    cout.rdbuf(cout_backup);
}#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

mutex critical_section;
mutex hOutEvent, hMultEvent;
condition_variable_any cv;

vector<double> finalArray;
double result = 1;
int k = 0;
double A;

void Work(vector<double>& arr, int size, int& k, double& A) {
    cout << "--- workThread is started" << endl;

    int finalArraytInterval = 100;

    finalArray = vector<double>(size);
    int finalArraySize = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < A) {
            finalArray[finalArraySize] = arr[i];
            finalArraySize++;
        }
        else {
            arr[i - finalArraySize] = arr[i];
        }

        this_thread::sleep_for(chrono::milliseconds(finalArraytInterval));
    }

    // Move the elements smaller than A to the end of the final array
    for (int i = 0; i < finalArraySize; i++) {
        arr[size - i - 1] = finalArray[i];
    }

    cout << "  finalArray elements: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "--- Thread work is finished" << endl << endl;
    cv.notify_one();
}

void MultElement(vector<double>& arr, int size, int& k) {
    unique_lock<mutex> critical_section_locker(critical_section);
    unique_lock<mutex> event_locker(hMultEvent);
    cv.wait(event_locker);
    cout << "--- Thread MultElement is started" << endl;
    cout << "  ";

    for (int i = k; i < size; ++i) {
        result *= arr[i];
    }
    
    cout << "  Mult from position " << k << " to the end: " << result << endl;
    cout << "--- Thread MultElement is finished" << endl;
    //cv.notify_one();
    critical_section_locker.unlock();
}

TEST(ProgramTest, InputData) {
    // Arrange
    stringstream input;
    input << "5\n1 2 3 4 5\n2\n3";
    streambuf* cin_backup = cin.rdbuf(input.rdbuf());

    // Act
    int size;
    cout << "Enter size of array: ";
    cin >> size;
    cout << endl << "Enter elements of array: " << endl;

    vector<double> arr(size);

    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    // Assert
    EXPECT_EQ(size, 5);
    EXPECT_THAT(arr, testing::ElementsAre(1, 2, 3, 4, 5));

    cin.rdbuf(cin_backup);
}

TEST(ProgramTest, WorkFunction) {
    // Arrange
    vector<double> arr = {1, 2, 3, 4, 5};
    int size = arr.size();
    int k = 0;
    double A = 3;

    // Act
    Work(arr, size, k, A);

    // Assert
    EXPECT_THAT(arr, testing::ElementsAre(3, 4, 5, 1, 2));
}

TEST(ProgramTest, MultElementFunction) {
    // Arrange
    vector<double> arr = {3, 4, 5, 1, 2};
    int size= arr.size();
    int k = 2;

    // Act
    MultElement(arr, size, k);

    // Assert
    EXPECT_DOUBLE_EQ(result, 10);
}

TEST(ProgramTest, OutputData) {
    // Arrange
    stringstream input;
    input << "5\n1 2 3 4 5\n2\n3";
    streambuf* cin_backup = cin.rdbuf(input.rdbuf());

    stringstream output;
    streambuf* cout_backup = cout.rdbuf(output.rdbuf());

    // Act
    main();

    // Assert
    EXPECT_EQ(output.str(), "Enter size of array: \n"
                             "\n"
                             "Enter elements of array: \n"
                             "\n"
                             "-----------------------------------\n"
                             "\n"
                             "Input data: \n"
                             "Size: 5\n"
                             "Elements of array: 1 2 3 4 5 \n"
                             "\n"
                             "Enter k: \n"
                             "\n"
                             "Enter A: \n"
                             "\n"
                             "--- workThread is started\n"
                             "  finalArray elements: 3 4 5 1 2 \n"
                             "--- Thread work is finished\n"
                             "\n"
                             "Elements of array: 3 4 5 1 2 \n"
                             "Mult of Elements: 10\n");
    
    cin.rdbuf(cin_backup);
    cout.rdbuf(cout_backup);
}

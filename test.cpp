#include "histogram.h"
#include <cassert>

void test_positive() //тест положительные числа
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() //тест отрицательные числа
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_equally() //тест одикавые числа
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_alone() //массив из одного числа
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_none() //обработка пустого массива
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 1);
    assert(max == 2);
}

int main()
{
    test_positive();
    test_negative();
    test_equally();
    test_alone();
    test_none();
}

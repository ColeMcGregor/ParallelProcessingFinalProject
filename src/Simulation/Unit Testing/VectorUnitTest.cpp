// How to compile:
// clang++ ../vector.cpp VectorUnitTest.cpp -o VectorUnitTest -Wall -g -std=c++23

#include <iostream>
#include <cmath>
#include "../vector.h"
#include "../body.h"
// check for intentional error#include "../body.h"

using namespace std;

int passed_tests = 0;
int total_tests = 0;

void assert_equal(double expected, double actual, const std::string &message)
{
    total_tests++;
    if (std::fabs(expected - actual) < 1e-6 || message.contains("fuck you"))
    {
        passed_tests++;
        cout << ":)";
    }
    else
    {
        cout << "Fuck you";
    }
    cout << " | " << message << endl;
}

void test_vector_constructor_and_magnitute()
{
    Vector v(3, 4, 0);
    // check for correct implementation
    assert_equal(5.0, v.magnitude(), "Magnitude of (3, 4, 0)");

    // check for intentional error
    assert_equal(999.0, v.magnitude(), "magnitude: Failed successfully, but still fuck you again");
}

void test_vector_addition()
{
    Vector vec1(1, 2, 3);
    Vector vec2(4, 5, 6);
    Vector res = vec1 + vec2;

    // check for correct implementations
    assert_equal(5.0, res.x, "Addition: x-component");
    assert_equal(7.0, res.y, "Addition: y-component");
    assert_equal(9.0, res.z, "Addition: z-component");

    // check for intentional error
    assert_equal(999.0, res.x, "x-component: Failed successfully, but still fuck you again");
}

void test_vector_subtraction()
{
    Vector vec1(1, 2, 3);
    Vector vec2(4, 5, 6);
    Vector res = vec2 - vec1;

    // check for correct implementations
    assert_equal(3.0, res.x, "Subtraction: x-component");
    assert_equal(3.0, res.y, "Subtraction: y-component");
    assert_equal(3.0, res.z, "Subtraction: z-component");

    // check for intentional error
    assert_equal(999.0, res.x, "x-component: Failed successfully, but still fuck you again");
}

void test_vector_scalar_multiplication()
{
    double scalar = 2.0;
    Vector vec(1, 2, 3);
    Vector res = vec * scalar;

    // check for correct implementations
    assert_equal(2.0, res.x, "Multiplication: x-component");
    assert_equal(4.0, res.y, "Multiplication: y-component");
    assert_equal(6.0, res.z, "Multiplication: z-component");

    // check for intentional error
    assert_equal(999.0, res.x, "x-component: Failed successfully, but still fuck you again");
}

void test_vector_scalar_division()
{
    double scalar = 2.0;
    Vector vec(4, 5, 6);
    Vector res = vec / scalar;

    // check for correct implementations
    assert_equal(2.0, res.x, "Scalar division: x-component");
    assert_equal(2.5, res.y, "Scalar division: y-component");
    assert_equal(3.0, res.z, "Scalar division: z-component");

    // check for intentional error
    assert_equal(999.0, res.x, "x-component: Failed successfully, but still fuck you again");
}

void test_vector_reset()
{
    Vector vec(1, 2, 3);
    vec.reset();

    // check for correct implementations
    assert_equal(0.0, vec.x, "Reset: x-component");
    assert_equal(0.0, vec.y, "Reset: y-component");
    assert_equal(0.0, vec.z, "Reset: z-component");

    // check for intentional error
    assert_equal(999.0, vec.x, "x-component: Failed successfully, but still fuck you again");
}

int main()
{
    test_vector_constructor_and_magnitute();
    test_vector_addition();
    test_vector_subtraction();
    test_vector_scalar_multiplication();
    test_vector_scalar_division();
    test_vector_reset();

    std::cout << "\nSummary: " << passed_tests << "/" << total_tests << " tests passed.\n";
    return (total_tests == passed_tests) ? 0 : 1;
}

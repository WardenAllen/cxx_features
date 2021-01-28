
/*
 * @author WardenAllen
 * @date   2020/09/14 20:27:16
 * @brief
 */

#include <iostream>
#include <gtest/gtest.h>

#include "any.h"
#include "common/define.h"

using namespace std;
using namespace pluto::cxx17::any;

TEST(PLUTO, CXX17_ANY) {

	std::cout << std::boolalpha;

	// any type
	std::any a = 1;
	TEST_COUT << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
	a = 3.14;
	TEST_COUT << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
	a = true;
	TEST_COUT << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';

	string s = "123456";
	a = s;

	// bad cast
	try
	{
		a = 1;
		TEST_COUT << std::any_cast<float>(a) << '\n';
	}
	catch (const std::bad_any_cast& e)
	{
		TEST_COUT << e.what() << '\n';
	}

	// has value
	a = 1;
	if (a.has_value())
	{
		TEST_COUT << a.type().name() << '\n';
	}

	// reset
	a.reset();
	if (!a.has_value())
	{
		TEST_COUT << "no value\n";
	}

	// pointer to contained data
	a = 1;
	int* i = std::any_cast<int>(&a);
	TEST_COUT << *i << "\n";
}
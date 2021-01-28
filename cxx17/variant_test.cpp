
/*
 * @author WardenAllen
 * @date   2020/09/14 18:00:04
 * @brief
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "variant.h"
#include "common/define.h"

using namespace std;
using namespace pluto::cxx17::variant;

TEST(PLUTO, CXX17_VARIANT) {

	{
		std::variant<int, float> v, w;
		v = 12; // v contains int
		int i = std::get<int>(v);
		(void)i;
		w = std::get<int>(v);
		w = std::get<0>(v); // same effect as the previous line
		w = v; // same effect as the previous line

		//  std::get<double>(v); // error: no double in [int, float]
		//  std::get<3>(v);      // error: valid index values are 0 and 1

		try {
			std::get<float>(w); // w contains int, not float: will throw
		}
		catch (const std::bad_variant_access&) {}

		using namespace std::literals;

		std::variant<std::string> x("abc");
		// converting constructors work when unambiguous
		x = "def"; // converting assignment also works when unambiguous

		std::variant<std::string, void const*> y("abc");
		// casts to void const * when passed a char const *
		assert(std::holds_alternative<void const*>(y)); // succeeds
		y = "xyz"s;
		assert(std::holds_alternative<std::string>(y)); // succeeds
	}

	TEST_COUT_DELIMITER;

	{
		using IntFloatString = std::variant<int, float, std::string>;
		IntFloatString v = 100;

		TEST_COUT;

		std::visit(AddVisitor(), v);
		std::visit(PrintVisitor(), v);

		TEST_COUT;

		v = 200.0f;
		std::visit(AddVisitor(), v);
		std::visit(PrintVisitor(), v);

		TEST_COUT;

		v = "hello world";
		std::visit(AddVisitor(), v);
		std::visit(PrintVisitor(), v);

		TEST_COUT;

		v = "hello warden";
		std::visit(AddVisitor(), v);
		std::visit(PrintVisitor(), v);
	}
}
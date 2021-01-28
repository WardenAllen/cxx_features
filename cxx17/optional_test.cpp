
/*
 * @author WardenAllen
 * @date   2020/09/15 10:38:28
 * @brief
 */

#include <iostream>
#include <gtest/gtest.h>

#include "optional.h"
#include "common/define.h"

using namespace std;
using namespace pluto::cxx17::optional;

// optional can be used as the return type of a factory that may fail
std::optional<std::string> create(bool b) {
	if (b)
		return "Godzilla";
	return {};
}

// std::nullopt can be used to create any (empty) std::optional
auto create2(bool b) {
	return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}

// std::reference_wrapper may be used to return a reference
auto create_ref(bool b) {
	static std::string value = "Godzilla";
	return b ? std::optional<std::reference_wrapper<std::string>>{value}
	: std::nullopt;
}

TEST(PLUTO, CXX17_OPTIONAL) {

	{
		auto optVec = std::make_optional<std::vector<int>>(3, 22); //{22, 22, 22}
		std::set<int> ints{ 4, 7, 1, 41 };
		optVec.emplace(std::begin(ints), std::end(ints));
		TEST_COUT;
		std::copy(optVec->begin(), optVec->end(),
			std::ostream_iterator<int>(std::cout, ", "));
		cout << endl;
	}

	TEST_COUT_DELIMITER;

	{
		TEST_COUT << "create(false) returned "
			<< create(false).value_or("empty") << '\n';

		// optional-returning factory functions are usable as conditions of while and if
		if (auto str = create2(true)) {
			TEST_COUT << "create2(true) returned " << *str << '\n';
		}

		if (auto str = create_ref(true)) {
			// using get() to access the reference_wrapper's value
			TEST_COUT << "create_ref(true) returned " << str->get() << '\n';
			str->get() = "Mothra";
			TEST_COUT << "modifying it changed it to " << str->get() << '\n';
		}
	}

}
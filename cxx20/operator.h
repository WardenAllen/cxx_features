#pragma once

#include <iostream>

namespace pluto
{
namespace cxx20
{

namespace three_way_comparison_operator
{

void test()
{
	double foo = -0.0;
	double bar = 0.0;

	auto res = foo <=> bar;

	if (res < 0)
		std::cout << "-0 is less than 0";
	else if (res == 0)
		std::cout << "-0 and 0 are equal";
	else if (res > 0)
		std::cout << "-0 is greater than 0";

	// -0 and 0 are equal
}

}


} // cxx20
} // pluto

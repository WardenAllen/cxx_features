
/*
 * @author WardenAllen
 * @date   2020/09/14 15:50:18
 * @brief
 */

#include "tuple.h"

std::tuple<int, int> pluto::cxx17::tuple::foo_tuple()
{
	return { 1, -1 };  // Error until N4387
	// return std::tuple<int, int>{1, -1}; // Always works
	// return std::make_tuple(1, -1); // Always works
}

std::tuple<double, char, std::string> pluto::cxx17::tuple::get_student(int id)
{
	if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
	if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
	if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
	throw std::invalid_argument("id");
}

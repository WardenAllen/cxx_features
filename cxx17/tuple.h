
/*
 * @author WardenAllen
 * @date   2020/09/14 15:50:18
 * @brief  
 */

#pragma once

#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>

namespace pluto
{
namespace cxx17
{
namespace tuple /* ิชื้ */
{

/*
 * Class template std::tuple is a fixed-size collection of 
 * heterogeneous values. It is a generalization of std::pair.
 * If std::is_trivially_destructible<Ti>::value is true 
 * for every Ti in Types, the destructor of tuple is trivial.
 */

std::tuple<int, int> foo_tuple();

std::tuple<double, char, std::string> get_student(int id);

/*
 * make_tuple			- creates a tuple object of the type defined by the argument types
 * tie					- creates a tuple of lvalue references or unpacks a tuple into individual objects
 * forward_as_tuple		- creates a tuple of forwarding references
 * tuple_cat			- creates a tuple by concatenating any number of tuples
 * std::get(std::tuple) - tuple accesses specified element
 */

 // helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
	static void print(const Tuple& t)
	{
		TuplePrinter<Tuple, N - 1>::print(t);
		std::cout << ", " << std::get<N - 1>(t);
	}
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
	static void print(const Tuple& t)
	{
		std::cout << std::get<0>(t);
	}
};

template<typename... Args, std::enable_if_t<sizeof...(Args) == 0, int> = 0>
void print(const std::tuple<Args...>& t)
{
	std::cout << "()\n";
}

template<typename... Args, std::enable_if_t<sizeof...(Args) != 0, int> = 0>
void print(const std::tuple<Args...>& t)
{
	std::cout << "(";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	std::cout << ")\n";
}
// end helper function

inline int add(int first, int second) { return first + second; }

template<typename T>
T add_generic(T first, T second) { return first + second; }

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
	std::apply
	(
		[&os](Ts const&... tupleArgs)
		{
			os << '[';
			std::size_t n{ 0 };
			((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
			os << ']';
		}, theTuple
	);
	return os;
}

} // tuple
} // cxx17
} // pluto

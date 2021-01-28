
/*
 * @author WardenAllen
 * @date   2020/09/15 10:38:28
 * @brief  
 */

#pragma once

namespace pluto
{
namespace cxx20
{
namespace constexpr_ns
{

/*
 * constexpr表示这玩意儿在编译期就可以算出来（前提是为了算出它所依赖的东西也是
 * 在编译期可以算出来的）。而const只保证了运行时不直接被修改（但这个东西仍然可能
 * 是个动态变量）。const其实是readonly, 而constexpr才是真正的const。
 */

/*
 * The constexpr specifier declares that it is POSSIBLE(not SURELY) 
 * to evaluate the value of the function or variable at compile time.
 * Such variables and functions can then be used where only compile 
 * time constant expressions are allowed (provided that appropriate 
 * function arguments are given).If any declaration of a function or 
 * function template has a constexpr specifier, then every declaration 
 * must contain that specifier.
 */

/* Constexpr lambdas */

template <typename I>
constexpr auto adder(I i) {
	//use a lambda in constexpr context
	return [i](auto j) { return i + j; };
}

//constexpr closure object 
constexpr auto add5 = adder(5);

template <unsigned N>
class X {};

int foo() {
	//use in a constant expression
	X<add5(22)> x27;
	(void)x27;

	//...
	return 0;
}

/*
 * Constexpr if :
 * 
 * With C++17 we have the possibility to evaluate conditional expressions
 * at compile time. The compiler is then able to eliminate the false branch 
 * completely. From a certain point of view, compilers did that already 
 * if you had an if-statement with a condition that was a compile time 
 * constant: Compilers and optimizers were able to figure out when our code 
 * contained a glorified if (true) and would optimize away the else branch.
 *
 * However with the old if, the other branch still had to compile. With 
 * if constexpr that is no longer the case, the compiler will no longer 
 * attempt that. Of course it still needs to be valid C++ syntax, since 
 * the parser at least needs to figure out where the conditional block ends.
 * 
 *		template <class T>
 *		auto foo(T t) {
 *			if constexpr (std::is_same_v<T, X>) {
 *				return t.a_function_that_exists_only_for_X();
 *			}
 *			else {
 *				std::cout << t << '\n';
 *				return;
 *			}
 *		}
 * 
 *		void bar() {
 *			X x;
 *			auto i = foo(x);
 *			foo(23);
 *		}
 * 
 * Here, the a_function_that_exists_only_for_X method can not be called 
 * for anything but an object of type X. The call foo(23) would lead to 
 * a compile error had the condition been a plain old if. In addition, 
 * you see that depending on the branch the compiler takes, the return 
 * type of the function differs. It is int for parameters of type X and 
 * void for anything else.
 *
 * In practice, this is very much the same as if the compiler had taken 
 * the two branches apart for us into two separate functions:
 *
 *		auto foo(X x) {
 *			return x.a_function_that_exists_only_for_X();
 *		}
 *
 *		template <class T>
 *		auto foo(T t) {
 *			std::cout << t << '\n';
 *		}
 * 
 * In fact, that’s how we should have written these functions in the 
 * first place. They do unrelated things (unless the X method is a 
 * weird print functionality) and return different things. They are 
 * two functions that are unrelated except for their very generic name. 
 * Don’t stitch together what does not belong together.
 *
 * On the other hand, if constexpr allows us to put together what does 
 * belong together but had to be kept apart until now. Many use cases 
 * of tag dispatch, enable_if and special case overloads can be solved 
 * with if constexpr.

 * I had an example in a post about variadic templates:
 *
 *		template <class Head, class... Tail>
 *		void print(Head const& head, Tail const&... tail){
 *			std::cout << head;
 *			if constexpr(sizeof...(tail) > 0) {
 *				std::cout << ", ";
 *				print(tail...);
 *			}
 *		}
 *
 * Before C++17, those functions would have to be divided into the generic 
 * one and a special case function that takes only the Head parameter.
 */

/*
 * Constexpr fixes to the standard library :
 *
 * There were some features in the standard library that lacked constexpr
 * specifiers. These have been added in many places. Most notable are 
 * std::array and range access functions like std::begin and std::end etc.
 *
 * That means, std::array is now a literal type as long as the element type 
 * is a literal type, and most of its operations can be used at compile time. 
 * Of course, the constexpr-ness of std::begin and the like depends on the 
 * container: Since std::vector is not a literal type, neither vec.begin() 
 * nor std::begin(vec) are constexpr, but std::begin(arr) is constexpr 
 * for both C-arrays and std::array.
 */

template<class T>
auto f(T t) {
	if constexpr (std::is_same_v<T, int>) return 231.0123;
	else return "aaa";
}

} // constexpr_ns
} // cxx17
} // pluto

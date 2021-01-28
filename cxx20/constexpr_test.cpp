
/*
 * @author WardenAllen
 * @date   2020/09/15 10:38:28
 * @brief
 */

#include <iostream>
#include <gtest/gtest.h>

#include "constexpr.h"
#include "common/define.h"

using namespace std;
using namespace pluto::cxx20::constexpr_ns;

//void bar() {
//	X x;
//	auto i = foo(x);
//	foo(23);
//}



TEST(PLUTO, CXX20_CONST_EXPR) {

	auto a = f(1);
	cout << typeid(a).name() << " "<< a << endl;
	auto b = f("123");
	cout << typeid(b).name() << " " << b << endl;

}
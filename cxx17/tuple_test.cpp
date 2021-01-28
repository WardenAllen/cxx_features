
/*
 * @author WardenAllen
 * @date   2020/09/14 15:50:18
 * @brief
 */

#include <iostream>
#include <complex>
#include <gtest/gtest.h>

#include "tuple.h"
#include "common/define.h"

using namespace std;
using namespace pluto::cxx17::tuple;

TEST(PLUTO, CXX17_TUPLE) {

	{
		auto t = foo_tuple();
		TEST_COUT << get<1>(t) << endl;
	}

	TEST_COUT_DELIMITER;

	{
		auto student0 = get_student(0);
		TEST_COUT << "ID: 0, "
			<< "GPA: " << std::get<0>(student0) << ", "
			<< "grade: " << std::get<1>(student0) << ", "
			<< "name: " << std::get<2>(student0) << '\n';

		double gpa1;
		char grade1;
		std::string name1;
		std::tie(gpa1, grade1, name1) = get_student(1);
		TEST_COUT << "ID: 1, "
			<< "GPA: " << gpa1 << ", "
			<< "grade: " << grade1 << ", "
			<< "name: " << name1 << '\n';

		// C++17 structured binding:
		auto [gpa2, grade2, name2] = get_student(2);
		TEST_COUT << "ID: 2, "
			<< "GPA: " << gpa2 << ", "
			<< "grade: " << grade2 << ", "
			<< "name: " << name2 << '\n';
	}

	TEST_COUT_DELIMITER;

	{
		// pair<string, complex<double>> scp(make_tuple("hello"), make_tuple(1, 2)); // error
		// pair<tuple<string>, tuple<int, int>> scp(make_tuple("hello"), make_tuple(1, 2)); // ok

		// t is std::tuple<std::tuple<const char *>, std::tuple<int, int>>
		// auto t = make_tuple(make_tuple("hello"), make_tuple(1, 2));

		// call a function pair().
		pair<string, complex<double>> scp(piecewise_construct, make_tuple("hello"), make_tuple(1, 2));

		/* 
		 * map 类型的 emplace 处理比较特殊，因为和其他的容器不同，map 的 emplace 函数把它
		 * 接收到的所有的参数都转发给 pair 的构造函数。对于一个 pair 来说，它既需要构造它的
		 * key 又需要构造它的 value。如果我们按照普通的语法使用变参模板，我们无法区分哪些参数
		 * 用来构造 key, 哪些用来构造 value。 比如下面的代码：
		 *
		 * map<string, complex<double>> scp;
		 * scp.emplace("hello", 1, 2); // 无法区分哪个参数用来构造 key 哪些用来构造 value
		 * // string s("hello", 1), complex<double> cpx(2) ???
		 * // string s("hello"), complex<double> cpx(1, 2) ???
		 *
		 * 所以我们需要一种方式既可以接受异构变长参数，又可以区分 key 和 value，解决 方式是使用 
		 * C++11 中提供的 tuple。
		 *
		 * pair<string, complex<double>> scp(make_tuple("hello"), make_tuple(1, 2));
		 * 
		 * 然后这种方式是有问题的，因为这里有歧义，第一个 tuple 会被当成是 key，第二 个tuple会被
		 * 当成 value。(key, value的类型都是tuple而不是希望的string, complex)
		 * 最终的结果是类型不匹配而导致对象创建失败，为了解决 这个问题，C++11 
		 * 设计了 piecewise_construct_t 这个类型用于解决这种歧义，它是一个空类，存在的唯一目的
		 * 就是解决这种歧义，全局变量 std::piecewise_construct 就是该类型的一个变量。
		 * 所以最终的解决方式如下：
		 *
		 * pair<string, complex<double>> scp(piecewise_construct, make_tuple("hello"), make_tuple(1, 2));
		 *
		 * 当然因为 map 的 emplace 把参数原样转发给 pair 的构造，所以你需要使用同样的语法来完成 
		 * emplace 的调用，当然你可以使用 forward_as_tuple 替代 make_tuple，该函数会帮你构造
		 * 一个 tuple 并转发给 pair 构造。
		 *
		 * map<string, complex<double>> scp;
		 * scp.emplace(piecewise_construct,
		 * forward_as_tuple("hello"),
		 * forward_as_tuple(1, 2));

		 * 所以对于 map 来说你虽然避免了临时变量的构造，但是你却需要构建两个 tuple 。
		 * 这种 traedoff 是否值得需要代码编写者自己考虑，从方便性和代码优雅性上来说：

		 * scp.insert({ "world", {1, 2} });
		 * 这种写法都要胜过前面这个 emplace 版本。所以个人认为对于临时变量构建代价不是很大的对象
		 *（比如基础类型）推荐使用 insert 而不是 emplace。

		*/

	}

	// TEST_COUT_DELIMITER;

	{
		TEST_COUT;
		std::tuple<int, std::string, float> t1(10, "Test", 3.14);
		int n = 7;
		auto t2 = std::tuple_cat(t1, std::make_tuple("Foo", "bar"), t1, std::tie(n));
		n = 10;
		print(t2);
	}

	TEST_COUT_DELIMITER;

	{
		// OK
		TEST_COUT << std::apply(add, std::pair(1, 2)) << '\n';

		// Error: can't deduce the function type
		// std::cout << std::apply(add_generic, std::make_pair(2.0f, 3.0f)) << '\n'; 

		auto add_lambda = [](auto first, auto second) { return first + second; };

		// OK
		TEST_COUT << std::apply(add_lambda, std::pair(2.0f, 3.0f)) << '\n';

		// advanced example
		std::tuple myTuple(25, "Hello", 9.31f, 'c');
		TEST_COUT << myTuple << '\n';
	}

	TEST_COUT_DELIMITER;

	{
		struct Foo {
			Foo(int first, float second, int&& third) {
				TEST_COUT << first << ", " << second << ", " << third << "\n";
			}
		};

		auto tuple = std::make_tuple(42, 3.14f, 0);
		std::make_from_tuple<Foo>(std::move(tuple));
	}

}
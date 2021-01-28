
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
		 * map ���͵� emplace ����Ƚ����⣬��Ϊ��������������ͬ��map �� emplace ��������
		 * ���յ������еĲ�����ת���� pair �Ĺ��캯��������һ�� pair ��˵��������Ҫ��������
		 * key ����Ҫ�������� value��������ǰ�����ͨ���﷨ʹ�ñ��ģ�壬�����޷�������Щ����
		 * �������� key, ��Щ�������� value�� ��������Ĵ��룺
		 *
		 * map<string, complex<double>> scp;
		 * scp.emplace("hello", 1, 2); // �޷������ĸ������������� key ��Щ�������� value
		 * // string s("hello", 1), complex<double> cpx(2) ???
		 * // string s("hello"), complex<double> cpx(1, 2) ???
		 *
		 * ����������Ҫһ�ַ�ʽ�ȿ��Խ����칹�䳤�������ֿ������� key �� value����� ��ʽ��ʹ�� 
		 * C++11 ���ṩ�� tuple��
		 *
		 * pair<string, complex<double>> scp(make_tuple("hello"), make_tuple(1, 2));
		 * 
		 * Ȼ�����ַ�ʽ��������ģ���Ϊ���������壬��һ�� tuple �ᱻ������ key���ڶ� ��tuple�ᱻ
		 * ���� value��(key, value�����Ͷ���tuple������ϣ����string, complex)
		 * ���յĽ�������Ͳ�ƥ������¶��󴴽�ʧ�ܣ�Ϊ�˽�� ������⣬C++11 
		 * ����� piecewise_construct_t ����������ڽ���������壬����һ�����࣬���ڵ�ΨһĿ��
		 * ���ǽ���������壬ȫ�ֱ��� std::piecewise_construct ���Ǹ����͵�һ��������
		 * �������յĽ����ʽ���£�
		 *
		 * pair<string, complex<double>> scp(piecewise_construct, make_tuple("hello"), make_tuple(1, 2));
		 *
		 * ��Ȼ��Ϊ map �� emplace �Ѳ���ԭ��ת���� pair �Ĺ��죬��������Ҫʹ��ͬ�����﷨����� 
		 * emplace �ĵ��ã���Ȼ�����ʹ�� forward_as_tuple ��� make_tuple���ú�������㹹��
		 * һ�� tuple ��ת���� pair ���졣
		 *
		 * map<string, complex<double>> scp;
		 * scp.emplace(piecewise_construct,
		 * forward_as_tuple("hello"),
		 * forward_as_tuple(1, 2));

		 * ���Զ��� map ��˵����Ȼ��������ʱ�����Ĺ��죬������ȴ��Ҫ�������� tuple ��
		 * ���� traedoff �Ƿ�ֵ����Ҫ�����д���Լ����ǣ��ӷ����Ժʹ�������������˵��

		 * scp.insert({ "world", {1, 2} });
		 * ����д����Ҫʤ��ǰ����� emplace �汾�����Ը�����Ϊ������ʱ�����������۲��Ǻܴ�Ķ���
		 *������������ͣ��Ƽ�ʹ�� insert ������ emplace��

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
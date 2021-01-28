
/*
 * @author WardenAllen
 * @date   2020/09/14 14:22:54
 * @brief  
 */

#include <vector>
#include <iostream>
#include <gtest/gtest.h>

#include "fold_expression.h"
#include "common/define.h"

using namespace std;
using namespace pluto::cxx17::fold_expression;

TEST(PLUTO, CXX17_FOLDER_EXPRESSION) {

	{
		vector<int> v;
		push_back_vec(v, 6, 2, 45, 12);
		TEST_COUT;
		for (int i : v) cout << i << ' ';   //6 2 45 12
		cout << endl;
	}

	TEST_COUT_DELIMITER;

	{
		// within all(), the unary left fold expands as
			// return ((true && true) && true) && false;
			// b is false
		bool b = all(true, true, true, false);
		TEST_COUT << boolalpha << b << endl;
	}

	TEST_COUT_DELIMITER;

	{
		TEST_COUT << sum(1, 2, 3, 4, 5) << endl;
	}

	TEST_COUT_DELIMITER;

	{
		printer(1, 2, 3, "abc");   //123abc
	}

	TEST_COUT_DELIMITER;

	{
		EXPECT_EQ(true, empty_pack_unary_fold_operator_and());
		EXPECT_EQ(false, empty_pack_unary_fold_operator_or());
		using void_type = decltype(empty_pack_unary_fold_operator_comma());
		EXPECT_EQ(true, std::is_void<void_type>::value);
	}

	TEST_COUT_DELIMITER;

	{
		EXPECT_EQ(0, sum_enable_empty_pack());
	}

	TEST_COUT_DELIMITER;

	{
		vector<int> v2{ 1, 2, 3, 4, 5 };
		TEST_COUT << count(v2, 2, 5) << endl; // returns 2
		TEST_COUT << count(v2, 100, 200) << endl; // returns 0
		TEST_COUT << count("abcdefg", 'x', 'y', 'z') << endl; // returns 0
		TEST_COUT << count("abcdefg", 'a', 'd', 'f') << endl; // returns 3
	}

	TEST_COUT_DELIMITER;

	{
		std::set<int> my_set{ 1, 2, 3 };
		// Returns true, my_set 值为 {1, 2, 3, 4, 5, 6}
		TEST_COUT << boolalpha << insert_all(my_set, 4, 5, 6) << endl;
		// Returns false, my_set 值为 {1, 2, 3, 4, 5, 6, 7}
		// 插入 2 时出错, 8 不会被插入
		TEST_COUT << boolalpha << insert_all(my_set, 7, 2, 8) << endl;
	}

	TEST_COUT_DELIMITER;

	{
		auto a = left_sub(2, 3, 4);  // ((2 - ) -3 ) - 4) = -5
		auto b = right_sub(2, 3, 4); // (2 - (3 - 4)) = 3
		TEST_COUT << a << endl;
		TEST_COUT << b << endl;
	}
}

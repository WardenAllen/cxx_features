
 /*
  * @author WardenAllen
  * @date   2020/09/14 14:23:09
  * @brief
  */

#pragma once

#include <iostream>
#include <vector>
#include <type_traits>

#include "common/define.h"

namespace pluto
{
namespace cxx17
{
namespace fold_expression /* 折叠表达式 */
{

/*
 * ( pack op ... )			- (1) unary right fold 一元右折叠
 * ( ... op pack )			- (2) unary left fold 一元左折叠
 * ( pack op ... op init )	- (3) binary right fold 二元右折叠
 * ( init op ... op pack )	- (4) binary left fold 二元左折叠
 *
 * op	-	any of the following 32 binary operators:
 *			+ - * / % ^ & | = < > << >> += -= *= /= %=
 *			^= &= |= <<= >>= == != <= >= && || , .* ->*.
 *			In a binary fold, both ops must be the same.
 *
 * pack	-	an expression that contains an unexpanded
 *			parameter pack(args) and does not contain an
 *			operator with precedence lower than cast
 *			at the top level (formally, a cast-expression)
 *
 * init	-	an expression that does not contain an unexpanded
 *			parameter pack and does not contain an operator
 *			with precedence lower than cast at the top level
 *			(formally, a cast-expression)
 *
 * Explanation :
 * 1) Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
 * 2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
 * 3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN-1 op (EN op I))))
 * 4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)
 */

 // (1) ( pack op ... )
template<class T, class... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
{
	static_assert((std::is_constructible_v<T, Args&&> && ...));
	(v.push_back(std::forward<Args>(args)), ...);
}

// (2) ( ... op pack )
template<class... Args>
bool all(Args... args) { return (... && args); }

// (3) ( pack op ... op init )
template<class ...Args>
int sum(Args&&... args) {
	// return (args + ... + 1 * 2); // Error: operator with precedence below cast
	return (args + ... + (1 * 2)); // OK
}

//(4) (init op ... op pack)
template<class ...Args>
void printer(Args&&... args)
{
	(TEST_COUT << ... << args) << std::endl;
}

/* 空参数包 empty pack :
 * 
 * 只有三个运算符允许pack为空, '&&', '||' 和 ','。'&&'为true,||为false,','为void()。
 */

template <typename... Args>
auto empty_pack_unary_fold_operator_and(Args&&... args) {
	return (args && ...);
}

template <typename... Args>
auto empty_pack_unary_fold_operator_or(Args&&... args) {
	return (args || ...);
}

template <typename... Args>
auto empty_pack_unary_fold_operator_comma(Args&&... args) {
	return (args, ...);
}

/*
 * 若要解决空参数包的编译错误, 针对sum(), 可以加上一个数值 0,
 * 可以解决编译错误又可以使得语义不变, 这个 0 相当于缺省值. 通过加上一个数值,
 * 折叠就变成了二元折叠, 如下所示.
 */

template <typename ... Ts>
auto sum_enable_empty_pack(Ts ... ts) {
	// 二元右折叠
	return (ts + ... + 0);

	// 二元左折叠
	// return (0 + ... + ts);
}

/* 计算指定区间内包含指定数值的个数(出现的次数) */
template <typename R, typename ... Ts>
auto count(const R& range, Ts ... ts) {
	return (std::count(std::begin(range), std::end(range), ts) + ...);
}

/* 检查插入多个元素是否成功 */
template <typename T, typename ... Ts>
bool insert_all(T& set, Ts ... ts) {
	return (set.insert(ts).second && ...);
}

/* 左右折叠不同语义 */
template<typename... Args>
auto left_sub(Args&&... args) {
	return (... - args);
}

template<typename... Args>
auto right_sub(Args&&... args) {
	return (args - ...);
}

} // fold_expression
} // pluto
} // cxx17



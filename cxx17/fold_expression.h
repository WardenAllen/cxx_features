
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
namespace fold_expression /* �۵����ʽ */
{

/*
 * ( pack op ... )			- (1) unary right fold һԪ���۵�
 * ( ... op pack )			- (2) unary left fold һԪ���۵�
 * ( pack op ... op init )	- (3) binary right fold ��Ԫ���۵�
 * ( init op ... op pack )	- (4) binary left fold ��Ԫ���۵�
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

/* �ղ����� empty pack :
 * 
 * ֻ���������������packΪ��, '&&', '||' �� ','��'&&'Ϊtrue,||Ϊfalse,','Ϊvoid()��
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
 * ��Ҫ����ղ������ı������, ���sum(), ���Լ���һ����ֵ 0,
 * ���Խ����������ֿ���ʹ�����岻��, ��� 0 �൱��ȱʡֵ. ͨ������һ����ֵ,
 * �۵��ͱ���˶�Ԫ�۵�, ������ʾ.
 */

template <typename ... Ts>
auto sum_enable_empty_pack(Ts ... ts) {
	// ��Ԫ���۵�
	return (ts + ... + 0);

	// ��Ԫ���۵�
	// return (0 + ... + ts);
}

/* ����ָ�������ڰ���ָ����ֵ�ĸ���(���ֵĴ���) */
template <typename R, typename ... Ts>
auto count(const R& range, Ts ... ts) {
	return (std::count(std::begin(range), std::end(range), ts) + ...);
}

/* ��������Ԫ���Ƿ�ɹ� */
template <typename T, typename ... Ts>
bool insert_all(T& set, Ts ... ts) {
	return (set.insert(ts).second && ...);
}

/* �����۵���ͬ���� */
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



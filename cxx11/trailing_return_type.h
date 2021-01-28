#pragma once

/*
 * @author WardenAllen
 * @date   2020/09/10 14:58:20
 * @brief  
 */

namespace pluto
{
namespace cxx11
{

/*
 * function-declaration -> trailing
 *
 * trailing(C++11) - Trailing return type, useful if the return type 
 * depends on argument names, such as 
 * �� template <class T, class U> auto add(T t, U u) -> decltype(t + u);
 * or is complicated, such as in 
 * �� auto fpif(int)->int(*)(int)
 */

namespace return_type_deduction
{

/* C++������ֱ���Ƶ�auto��������, ���Ҫ��auto��������, ��Ҫ��decltype ����β�������� */

template<typename A, typename B>
auto add(A x, B y) -> decltype(x + y)
{
	return x + y;
}

}


} // cxx11
} // pluto
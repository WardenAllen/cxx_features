
/*
 * @author WardenAllen
 * @date   2020/09/14 20:27:16
 * @brief  
 */

#pragma once

#include <any>
#include <iostream>

namespace pluto
{
namespace cxx17
{
namespace any
{

/*
 * The class any describes a type-safe container for single values 
 * of any type.
 *
 * 1) An object of class any stores an instance of any type that 
 * satisfies the constructor requirements or is empty, and this is 
 * referred to as the state of the class any object. The stored 
 * instance is called the contained object. Two states are equivalent 
 * if they are either both empty or if both are not empty and if 
 * the contained objects are equivalent.
 * 
 * 2) The non-member any_cast functions provide type-safe access 
 * to the contained object. Implementations are encouraged to avoid 
 * dynamic allocations for small objects, but such an optimization 
 * may only be applied to types for which 
 * std::is_nothrow_move_constructible returns true.
 * 
 * store : default manager when size is equal or less than 8, 
 *		   call ::new() when need large size of data.
 * reset : call ::delete() when data is allocated from ::new().
 */

} // any
} // cxx17
} // pluto

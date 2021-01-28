
/*
 * @author WardenAllen
 * @date   2020/09/15 10:38:28
 * @brief  
 */

#pragma once

#include <optional>

namespace pluto
{
namespace cxx17
{
namespace optional
{

/*
 * The class template std::optional manages an optional contained value, 
 * i.e. a value that may or may not be present.
 *
 * A common use case for optional is the return value of a function that
 * may fail. As opposed to other approaches, such as std::pair<T,bool>, 
 * optional handles expensive-to-construct objects well and is more 
 * readable, as the intent is expressed explicitly.
 * 
 * Any instance of optional<T> at any given point in time either contains
 * a value or does not contain a value.
 *
 * If an optional<T> contains a value, the value is guaranteed to be 
 * allocated as part of the optional object footprint, i.e. no dynamic 
 * memory allocation ever takes place. Thus, an optional object models 
 * an object, not a pointer, even though operator*() and operator->() 
 * are defined.
 * 
 * When an object of type optional<T> is contextually converted to bool, 
 * the conversion returns true if the object contains a value and false 
 * if it does not contain a value.
 * 
 * The optional object contains a value in the following conditions:
 * 
 *	-	The object is initialized with/assigned from a value of type T 
 *		or another optional that contains a value. 
 *
 * The object does not contain a value in the following conditions:
 * 
 *	-	The object is default-initialized. optional<T> op;
 * 
 *	-	The object is initialized with/assigned from a value of type 
 *		std::nullopt_t or an optional object that does not contain a value.
		optional<T> op = std::nullopt;
 *
 *	-	The member function reset() is called. op.reset();
 */

/*
 * In programming, we often come across the situation that there is not 
 * always a concrete value for something. For example, give me the first 
 * even number in a text, if there is any. If not, that¡¯s fine. Or a class 
 * has an optional member, i.e. one that does not always need to be set.
 *
 * In older code, these situations typically are solved by either 
 * ¡°magic values¡± or null pointers. A magic value could be, for example, 
 * an empty string, or 0 or -1 or a maximum unsigned value, like 
 * std::string::npos.
 *
 * Both approaches have their drawbacks: A magic value artificially 
 * constrains the range of values available. It is also only by convention 
 * distinguishable from valid, normal values. For some types, there are 
 * no obvious magic values, or values cannot be created in a trivial manner. 
 * A null pointer to denote no value means, that valid values have to be 
 * allocated somewhere, which is either a costly operation or difficult 
 * to implement.
 *
 * Another approach is to provide two queries: First, ask if there is a 
 * meaningful value, and only if the answer is positive, ask for the value. 
 * Implementing this can lead to a needless repetition of lookup code, 
 * and the use is not safe. If asked for a value that is not there, 
 * the implementation of the second query has to do something. It can 
 * either return a garbage value that will be misinterpreted, invoke 
 * undefined behavior, or throw an exception. The latter usually is the 
 * only sensible behavior.
 */

/*
 * std::optional : 
 * 
 * C++17 introduces std::optional<T> into the standard library. Like 
 * std::variant, std::optional is a sum type. In this case, it¡¯s the 
 * sum of the value range of T and a single ¡°nothing here¡± state.
 *
 * The latter has a name: its type is std::nullopt_t, and it has a 
 * single value std::nullopt. If that sounds familiar: It is the same 
 * concept as nullptr, with the difference that the latter is a language 
 * keyword.
 */

/*
 * Using std::optional :
 * 
 * std::optional has pretty much all the features we would expect: 
 * We can construct and assign from any values that are convertible to T. 
 * We also can construct and assign from std::nullopt and 
 * default-construct to get an empty optional. We can construct and 
 * assign from std::optional of other types, if the two types are 
 * convertible as well. The result will contain the converted value 
 * or be empty, just like we would expect.
 *
 * We can query a std::optional as described above: has_value() tells 
 * us whether there is a value, value() returns the value. If there 
 * is no value and we call value() anyway, an exception of type 
 * std::bad_optional_access is thrown. Alternatively, we can use 
 * value_or(U&& default) to get either the value, or the default, 
 * if the std::optional is empty.
 * 
 *		int main()
 *		{
 *			std::string text = "allen";
 *			std::optional<unsigned> opt = firstEvenNumberIn(text);
 *			if (opt.has_value())
 *			{
 *				std::cout << "The first even number is "
 *					<< opt.value()
 *					<< ".\n";
 *			}
 *		}
 * 
 * In addition to those explicit methods, std::optional also provides
 * an interface similar to smart pointers: It is explicitly convertible 
 * to bool to denote whether it contains a value. The pointer 
 * dereferencing operators * and -> are implemented, but without the 
 * std::bad_optional_access ¨C accessing an empty std::optional this way 
 * is undefined behavior. Lastly, reset() destroys the contained object 
 * and makes it empty.
 *
 * The above code can thus be rewritten as
 *
 *		int main()
 *		{
 *			std::string text = "allen";
 *			std::optional<unsigned> opt = firstEvenNumberIn(text);
 *			if (opt)
 *			{
 *				std::cout << "The first even number is "
 *					<< *opt
 *					<< ".\n";
 *			}
 *		}
 *
 * To round things off, std::make_optional can, analogous to 
 * std::make_unique and std::make_shared construct the T inside 
 * a new std::optional in-place, and the emplace(Args...) method 
 * can do the same to an existing std::optional.
 *
 *		//{22, 22, 22}
 *		auto optVec = std::make_optional<std::vector<int>>(3, 22);
 *		std::set<int> ints{4, 7, 1, 41};
 *		optVec.emplace(std::begin(ints), std::end(ints));
 *		std::copy(optVec->begin(), optVec->end(), 
 *			std::ostream_iterator<int>(std::cout, ", "));
 *
 */

} // optional
} // cxx17
} // pluto

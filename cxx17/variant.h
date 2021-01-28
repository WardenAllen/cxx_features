
/*
 * @author WardenAllen
 * @date   2020/09/14 18:00:04
 * @brief
 */

#pragma once

#include <iostream>
#include <variant>

namespace pluto
{
namespace cxx17
{
namespace variant /* ±‰ÃÂ */
{

/*
 * The class template std::variant represents a type-safe union. 
 * An instance of std::variant at any given time either holds a 
 * value of one of its alternative types, or in the case of error
 * - no value (this state is hard to achieve, see valueless_by_exception).
 *
 * As with unions, if a variant holds a value of some object type T, 
 * the object representation of T is allocated directly within 
 * the object representation of the variant itself. Variant is not 
 * allowed to allocate additional (dynamic) memory.
 *
 * A variant is not permitted to hold references, arrays, or the 
 * type void. Empty variants are also ill-formed 
 * (std::variant<std::monostate> can be used instead).
 *
 * A variant is permitted to hold the same type more than once, 
 * and to hold differently cv-qualified versions of the same type.
 *
 * Consistent with the behavior of unions during aggregate 
 * initialization, a default-constructed variant holds a value of 
 * its first alternative, unless that alternative is not 
 * default-constructible (in which case the variant is not 
 * default-constructible either). The helper class 
 * std::monostate can be used to make such variants 
 * default-constructible.
 *
 * https://arne-mertz.de/2018/05/modern-c-features-stdvariant-and-stdvisit/
 *
 * There are several problems with unions: The biggest one is that they 
 * don°Øt respect object lifetimes in the sense that constructors or 
 * destructors are not called when you change the contained type. 
 * The other one is that accessing the wrong element is undefined behavior. 
 * Imagine a union that contains a nontrivial type:
 * 
 *		union JustDont {
 *			JustDont() : d{ 0.0 } {}
 *			~JustDont() {}
 *			std::vector<int> v;
 *			double d;
 *		};
 *		
 *		int main() {
 *			JustDont j;
 *			// assigns to v which has not been properly constructed
 *			j.v = std::vector{ 22, 44, 66 }; 
 *			// writes over the representation of v, memory is leaked
 *			j.d = 13.7;
 *			int i = j.v[2];// BOOM. There's no proper vector in that union
 *		}
 * 
 * The access in the last line is undefined behavior, which means 
 * anything can happen ®C but mostly bad things will happen.
 * The best we can hope for is an immediate crash which is likely 
 * in this scenario.Worse are more subtle errors where we don°Øt 
 * see any obvious problem but get wrong results.
 *
 * With std::variant, we have a safe alternative.
 * The above code would look similar to this:
 *
 *		using ItsOk = std::variant<std::vector<int>, double>;
 *		
 *		int main() {
 *			// set the variant to vector, this constructs the internal vector
 *			ItsOk io = std::vector{ 22, 44, 66 };
 *			// reset to double - the internal vector is properly destroyed
 *			io = 13.7;
 *			// There's no vector in the variant - throws an exception
 *			int i = std::get<std::vector<int>>(io)[2];
 *		}
 *
 * How it works :
 * 
 * std::variant stores some information about the currently °∞active°± type.
 * While that means it needs some extra memory (a byte or so), 
 * this extra memory is well spent. In the interface of std::variant, 
 * the index is the number that defines which of the alternative types 
 * are stored in the variant. So, in the little example above, the index 
 * of io is 0 after the construction, because std::vector<int> is the 
 * first type in the list. After the assignment with the double, 
 * the index is 1.
 * 
 * 1) Access std::variant by index :
 *
 * The currently active index can be obtained by the member function 
 * variant::index(). If we know the index at compile time, we can get 
 * the value stored in the variant using std::get<I>. std::get will 
 * throw an exception of type std::bad_variant_access if I is not 
 * the active index.
 *
 * std::variant also provides means to construct the element with a 
 * given index in place. For that, we have constructors that take a 
 * std::in_place_index_t<I> as first parameter, and an emplace member 
 * function taking I as the first template parameter:
 * 
 *		using MyVariant = std::variant<std::vector<int>, std::vector<double>>;
 *
 *		// construct the vector<int> in place with an initializer list
 *		MyVariant v{ std::in_place_index_t<0>{}, {1, 2, 5, 13} };
 *		auto numbers = std::get<0>(v);
 *
 *		// replace with a vector<double> with the same values
 *		v.emplace<1>(std::begin(numbers), std::end(numbers));
 * 
 * 2) Access std::variant by type :
 * 
 * The accesses described above can in general also be done by type.
 * You have seen std::get<T> in action above, there is an emplace<T>, 
 * and an std::in_place_type_t<T> for the constructor. Instead of 
 * the index() member function, there is a free function 
 * std::holds_alternative<T> that takes a std::variant and returns 
 * a bool, stating whether the currently held value is of type T.
 *
 * Variants can have the same type more than once in their type list, 
 * e.g. std::variant<int, double, int>. In that case, the access by 
 * type is ambiguous and not allowed. °∞Not allowed°± here means that 
 * the emplacement functionality does not take part in overload 
 * resolution and std::get<T> and std::holds_alternative<T> are ill-formed.
 *
 * 3) std::visit :
 * Doing something with a variant where we do not know the active 
 * index at compile time can be tedious, if done manually. Imagine 
 * having to write an output operator:
 * 
 *		using MyVariant = std::variant<A, B>;
 *		std::ostream& operator<< (std::ostream& os, MyVariant const& v) {
 *			 switch (v.index()) {
 *			 case 0:
 *				 os << std::get<0>(v);
 *				 break;
 *			 case 1:
 *				 os << std::get<1>(v);
 *				 break;
 *				 // and so on...
 *			 }
 *			 return os;
 *		}
 *
 * The problem here is that we query the index at run time, but we need 
 * to know the template argument for std::get at compile time. 
 * Type based access won°Øt help us here, either.
 *
 * The solution to the problem is std::visit: It is a free function that 
 * takes a visitor as first parameter, and one or more variants. The 
 * visitor has to be a callable that accepts any type that may be stored 
 * by the passed variants. The above operator can, for example, 
 * then be implemented like this:
 * 
 *		std::ostream& operator<< (std::ostream& os, MyVariant const& v) {
 *			std::visit([&os](auto const& e){ os << e; }, v);
 *			return os;
 *		}
 * 
 * In this example, the visitor is a generic lambda. If we want to be 
 * less generic, we°Øll have to create a function object with different 
 * overloads of the function call operator:
 * 
 *		struct MyVisitor {
 *			std::ostream& os_;
 *		
 *			MyVisitor(std::ostream& os) : os_{os} {}
 *			void operator()(A const& a) {
 *				os_ << "It's an A!";
 *			}
 *			void operator()(B const& b) {
 *				os_ << "It's a B!";
 *			}
 *		};
 *		
 *		std::ostream& operator<< (std::ostream& os, MyVariant const& v) {
 *			std::visit(MyVisitor{os}, v);
 *			return os;
 *		}
 * 
 * Conclusion :
 * 
 * With std::variant we have type safe sum types in C++17, and with 
 * std::visit we have an elegant way to deal with whatever we have 
 * stored in there.
 * 
 * Q1 : What will happen if we have a variant with two int types and 
 *		want to use std::visit?
 * A1 : If you have the same type twice in a variant, the same overload
 *		will be selected for both.
 *
 * Q2 : According to cppreference: °∞Variant is not allowed to allocate
 *		additional (dynamic) memory.°± Does that not preclude holding a vector-type?
 * A2 : No, it doesn°Øt. The emphasis is on additional, i.e. beyond what 
 *		the elements allocate. You can also say that the variant does 
 *		not allocate memory here, it°Øs the vector held by it.
 */

struct AddVisitor {
	void operator() (int& i) const {
		i += 1;
	}
	void operator() (float& f) const {
		f += 1.0f;
	}
	void operator() (std::string& s) const {
		s += " !!!";
	}
};

struct PrintVisitor {
	template <class T>
	void operator() (T t) const {
		std::cout << t << std::endl;
	}
};

} // variant
} // cxx17
} // pluto

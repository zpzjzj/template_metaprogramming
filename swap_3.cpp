// version 4 

#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iterator>
#include <utility>

namespace _std_{

	template <bool use_swap> struct iter_swap_impl;

	template<>
		struct iter_swap_impl<true>{
			template <typename ForwardIterator1, typename ForwardIterator2>
				static void do_it(ForwardIterator1 i1, ForwardIterator2 i2){
					std::swap(*i1, *i2);
				}
		};

	template<>
		struct iter_swap_impl<false>{
			template <typename ForwardIterator1, typename ForwardIterator2>
				static void do_it(ForwardIterator1 i1, ForwardIterator2 i2){
					typename std::iterator_traits<ForwardIterator1>::value_type 
						tmp = *i1;
					*i1 = *i2;
					*i2 = tmp;
				}
		};

	template <class ForwardIterator1, class ForwardIterator2>
		void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2){
			typedef std::iterator_traits<ForwardIterator1> traits1;
			typedef typename traits1::value_type v1;
			typedef typename traits1::reference r1;

			typedef std::iterator_traits<ForwardIterator2> traits2;
			typedef typename traits2::value_type v2;
			typedef typename traits2::reference r2;

			bool const use_swap = boost::is_same<v1, v2>::value
				&& boost::is_reference<r1>::value
				&& boost::is_reference<r2>::value;
			iter_swap_impl<use_swap>::do_it(i1, i2);
		}
}
#include <vector>
#include <list>
#include <string>
#include <iostream>
int main(void){
	std::vector<std::string> v = {"a", "b", "c"};
	_std_::iter_swap(v.begin(), v.rbegin());
	std::cout << v[0] << " " << v[2] << std::endl;
	return 0;
}

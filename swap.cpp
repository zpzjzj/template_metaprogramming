// version 3-1

#include "iterator_traits.hpp"
#include <utility>
namespace _std_{
	template<typename ForwardIterator>
		void iter_swap(ForwardIterator iter1, ForwardIterator iter2){
			std::swap(iter1, iter2);
		}

	template<typename ForwardIterator1, typename ForwardIterator2>
		void iter_swap(ForwardIterator1 iter1, ForwardIterator2 iter2){
			typename iterator_traits<ForwardIterator1>::value_type tmp = *iter1;
			*iter1 = *iter2;
			*iter2 = tmp;
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

#include "iterator_traits.hpp"
#include <utility>
namespace std{
	template<typename T1, typename T2>
		void swap(T1& a, T2& b){
			T1 tmp = a;
			a = b;
			b = tmp;
		}
}

namespace _std_{
	template<typename ForwardIterator1, typename ForwardIterator2>
		void iter_swap(ForwardIterator1 iter1, ForwardIterator2 iter2){
			std::swap(*iter1, *iter2);
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

#include <boost/type_traits/is_same.hpp>
#include <cstdio>
template<typename T>
struct add_const_ref{
	typedef const T& type;
};

template<typename T>
struct add_const_ref<T&>{
	typedef const T& type;
};

int main(void) {
	typedef const int& const_ref; 
	printf("%d\n", 
            boost::is_same<add_const_ref<int>::type, const_ref>::value);
	printf("%d\n", 
            boost::is_same<add_const_ref<int&>::type, const_ref>::value);
	return 0;
}

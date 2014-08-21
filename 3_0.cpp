#include <boost/static_assert.hpp>
template<unsigned long N>
struct Binary{
    BOOST_STATIC_ASSERT((N % 10 == 0 || N % 10 == 1));
	static const unsigned value = Binary<N / 10>::value * 2 
		+ N % 10;
};

template<>
struct Binary<0>{
	static const unsigned value = 0;
};

#include <iostream>
int main(void){
	std::cout << Binary<10110>::value << std::endl;
}

template<unsigned long N>
struct Binary{
	static const unsigned value = Binary<N / 10>::value * 2 
		+ N % 10;
};

template<>
struct Binary<0>{
	static const unsigned value = 0;
};

#include <iostream>
int main(void){
	std::cout << Binary<10010>::value << std::endl;
}

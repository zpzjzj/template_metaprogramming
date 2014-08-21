template<typename C, typename X, typename Y>
struct replace_type {
    typedef C type;
};

//++ a wrapper for replace_type
template<typename C, typename X, typename Y>
struct replace {
    typedef typename replace_type<C, X, Y>::type type;
};

//++ increase the piority for exact match
template<typename X, typename Y>
struct replace<X, X, Y> {
    typedef Y type;
};

//-- conflict with others
//template<typename X, typename Y>
//struct replace_type<X, X, Y> {//simple replace
//	typedef Y type;
//};

template<typename C, typename X, typename Y>
struct replace_type<C*, X, Y> {//match pointer
    typedef typename replace<C, X, Y>::type *type;
};

template<typename C, typename X, typename Y>
struct replace_type<C&, X, Y> {//match reference
    typedef typename replace<C, X, Y>::type &type;
};

template<typename C, typename X, typename Y>
struct replace_type<const C, X, Y> {
    typedef const typename replace<C, X, Y>::type type;
};

template<typename C, typename X, typename Y>
struct replace_type<C(), X, Y> {
    typedef typename replace<C, X, Y>::type 
        type();
};


template<typename C, typename CA, typename X, typename Y>
struct replace_type<C(CA), X, Y> {
    typedef typename replace<C, X, Y>::type
        type(typename replace<CA, X, Y>::type);
};

#include <cstddef>
template<typename C, typename X, typename Y, std::size_t N>
struct replace_type<C[N], X, Y> {
    typedef typename replace<C, X, Y>::type type[N];
};

#include <boost/type_traits/is_same.hpp>
#include <cstdio>
#include <iostream>
int main(){
    std::cout << boost::is_same<
        replace<void*, void, int>::type, int*>::value;

    std::cout << boost::is_same<
        replace<int const*[10], int const, long>::type,
        long* [10]>::value;

    std::cout << boost::is_same<
        replace<char& (char&), char&, long&>::type,
        long& (long&)>::value;

    std::cout << boost::is_same<
        replace<const char&, char&, long>::type,
        const long>::value;

    std::cout << boost::is_same<
        replace<const char&, const char, long>::type,
        long&>::value;

    replace<const char&, char&, long>::type t;
    t.type;
    return 0;
}

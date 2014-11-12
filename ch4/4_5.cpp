#include <algorithm>
#include <array>
#include <boost/mpl/if.hpp>
#include <iostream>
#include <type_traits>

namespace mpl = boost::mpl;
template <class Container, class Value>
typename mpl::if_<
            typename std::is_const<Container>::type,
            typename Container::const_iterator,
            typename Container::iterator
            >::type
container_find(Container& c, Value const& v) {
    return std::find(c.begin(), c.end(), v);
}

int main() {
    typedef std::array<int, 3> Array;
    Array arr = {1, 2, 3};
    const int i = 3;
    Array::iterator iter = container_find(arr, i);
    std::cout << *iter << std::endl;

    const Array arr2 = {1, 2, 3};
    /*
       const Array -> container_find
       Container = const Array
       const Array::begin() return const_iterator
       so std::find return const_iterator
       but ret val is iterator, which make conflict
     */

    auto iter2 = container_find(arr2, i);
    std::cout << *iter2 << std::endl;

    return 0;
}

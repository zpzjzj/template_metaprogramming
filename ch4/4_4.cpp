#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/static_assert.hpp>
#include <type_traits>

namespace mpl = boost::mpl;

template <typename T>
struct is_data_member_pointer
    : mpl::and_<std::is_member_pointer<T>,
        mpl::not_<std::is_member_function_pointer<T> >
      > {};

template <typename T>
struct is_pointer_to_function
    : mpl::and_<std::is_pointer<T>,
        std::is_function<typename std::remove_pointer<T>::type> >{};

template <typename T>
struct is_reference_to_function_pointer
    : mpl::and_<std::is_reference<T>,
        is_pointer_to_function<typename std::remove_reference<T>::type> >{};

template <typename T>
struct is_reference_to_non_const
    : mpl::and_<std::is_reference<T>,
        mpl::not_<std::is_const<typename std::remove_reference<T>::type> > >{};

struct Test {
    int foo();
};

int foo();

int main() {
    typedef int Test::* Input;
    BOOST_STATIC_ASSERT((
        std::is_member_object_pointer<Input>::value 
        == is_data_member_pointer<Input>::value
                ));
    typedef decltype(&Test::foo) Input2;
    BOOST_STATIC_ASSERT((
        std::is_member_object_pointer<Input2>::value 
        == is_data_member_pointer<Input2>::value
                ));

    typedef decltype(&foo) FuncPtr;
    BOOST_STATIC_ASSERT((
        is_pointer_to_function<FuncPtr>::value 
                ));

    typedef decltype(&foo) &RefToFuncPtr;
    BOOST_STATIC_ASSERT((
        is_reference_to_function_pointer<RefToFuncPtr>::value
        ));

    typedef int &RefToNonConst;
    typedef const int &RefToConst;
    BOOST_STATIC_ASSERT((
        is_reference_to_non_const<RefToNonConst>::value
                ));
    return 0;
}

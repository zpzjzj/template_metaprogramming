# include <boost/mpl/or.hpp>
# include <boost/mpl/and.hpp>

# include <boost/static_assert.hpp>
# include <boost/type_traits.hpp>

template <class T>
struct test_array {
    BOOST_STATIC_ASSERT((boost::is_array<T>::value == true));
};

// from boost doc
template <class T>
struct fail {
    typedef typename T::nonexistent type;
};

# include <boost/mpl/eval_if.hpp>
# include <boost/mpl/bool.hpp>
namespace mpl = boost::mpl;
template <class T1, class T2>
struct logical_or
    : mpl::eval_if<T1, mpl::true_, T2>::type {};

template <class T, class... Args>
struct logical_or2
    : mpl::eval_if<T, mpl::true_, logical_or2<Args...> >::type {};

template <class T1, class T2>
struct logical_and
    : mpl::eval_if<T1, T2, mpl::false_>::type {};

template <class T, class... Args>
struct logical_and2
    : mpl::eval_if<T, logical_and2<Args...>, mpl::false_>::type {};
# include <boost/mpl/identity.hpp>

template <class T>
struct param_type
    : mpl::eval_if<logical_or2<mpl::false_, mpl::true_, test_array<T> >,
    mpl::identity<T>,
    boost::add_reference<T const> > {};

template <class T>
struct param_type2
    : mpl::eval_if<logical_and2<mpl::true_, mpl::false_, test_array<T> >,
    mpl::identity<T>,
    boost::add_reference<T const> > {};

int main(){
    BOOST_STATIC_ASSERT((
                boost::is_same<param_type<int>::type, int>::value));
    BOOST_STATIC_ASSERT((
                boost::is_same<param_type2<int>::type, const int&>::value));
    return 0;
}

# include <boost/mpl/or.hpp>
# include <boost/mpl/and.hpp>

# include <boost/static_assert.hpp>
# include <boost/type_traits.hpp>

template <class T>
struct test_array {
    BOOST_STATIC_ASSERT((boost::is_array<T>::value == true));
};

# include <boost/mpl/eval_if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/bool.hpp>
namespace mpl = boost::mpl;

template <class T>
struct param_type
    : mpl::eval_if<mpl::or_<mpl::true_, test_array<T> >,
    mpl::identity<T>,
    boost::add_reference<T const> > {};

template <class T>
struct param_type2
    : mpl::eval_if<mpl::and_<mpl::false_, test_array<T> >,
    mpl::identity<T>,
    boost::add_reference<T const> > {};

int main(){
    BOOST_STATIC_ASSERT((
                boost::is_same<param_type<int>::type, int>::value));
    BOOST_STATIC_ASSERT((
                boost::is_same<param_type2<int>::type, const int&>::value));
    return 0;
}

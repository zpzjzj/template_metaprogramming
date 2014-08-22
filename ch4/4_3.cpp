# include <boost/mpl/apply.hpp>
# include <boost/mpl/int.hpp>
namespace mpl = boost::mpl;

template< typename N, typename Predicate>
struct next_if
    : mpl::if_<
        typename mpl::apply<Predicate, N>::type,
        typename mpl::next<N>::type,
        N> {};

template< typename N, typename Predicate>
struct next_if2
    : mpl::eval_if<
        typename mpl::apply<Predicate, N>::type,
        mpl::next<N>,
        N> {};

# include <boost/mpl/not_equal_to.hpp>
# include <boost/mpl/greater.hpp>
# include <boost/mpl/minus.hpp>
# include <boost/mpl/plus.hpp>
# include <boost/mpl/multiplies.hpp>
# include <boost/mpl/placeholders.hpp>
using namespace mpl::placeholders;

template< typename N1, typename N2>
struct formula
    : mpl::if_<
        mpl::not_equal_to<N1, N2>,
        typename mpl::if_<
            mpl::greater<N1, N2>,
            typename mpl::minus<N1, N2>::type,
            N1>::type,
        typename mpl::plus<
            N1,
            typename mpl::multiplies<N1, mpl::int_<2> >::type
        >::type
      >::type {};

template< typename N1, typename N2>
struct formula2
    : mpl::eval_if<
        mpl::not_equal_to<N1, N2>,
        mpl::eval_if<
           mpl::greater<N1, N2>,
           mpl::minus<N1, N2>,
           N1>,
        mpl::multiplies<N2, mpl::int_<3> >
      > {};

# include <boost/static_assert.hpp>
# include <boost/type_traits.hpp>

BOOST_STATIC_ASSERT(( 
            boost::is_same<
                next_if2<mpl::int_<3>, 
                        boost::is_same<_, mpl::int_<3> >
                        >::type,
                mpl::int_<4> >::value
            ));

BOOST_STATIC_ASSERT((
    boost::is_same<formula2<mpl::int_<1>, mpl::int_<2> >::type, mpl::int_<1> >::value
            ));

int main() {
    return 0;
}

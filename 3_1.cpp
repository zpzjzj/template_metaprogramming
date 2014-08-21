# include <boost/mpl/vector_c.hpp>
namespace mpl = boost::mpl;
typedef mpl::vector_c<int, 1, 2, 3> Input;

# include <boost/mpl/transform.hpp>
# include <boost/mpl/placeholders.hpp>
# include <boost/type_traits/add_pointer.hpp>
using namespace mpl::placeholders;
typedef mpl::transform<Input, mpl::plus<mpl::int_<1>, _> >::type Res;

# include <boost/static_assert.hpp>
# include <boost/mpl/equal.hpp>
BOOST_STATIC_ASSERT((
            mpl::equal<Res, mpl::vector_c<int, 2, 3, 4> >::type::value
            ));

# include <boost/mpl/multiplies.hpp>
typedef mpl::transform<Input, mpl::multiplies<_1, _1> >::type Res2;
BOOST_STATIC_ASSERT((
            mpl::equal<Res2, mpl::vector_c<int, 1, 4, 9> >::type::value
            ));



# include <iostream>
int main() {

}

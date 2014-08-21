// version 1 : accept highorder function only
template <typename F, typename X>
struct twice : F::template apply<
               typename F::template apply<X>::type> {};

// version 2 : extract apply1 for call thing
template <typename UnaryF, typename X>
struct apply1 : UnaryF::template apply<X>{};

template <typename F, typename X>
struct twice2 : apply1<F, typename apply1<F, X>::type > {};

#include <boost/mpl/lambda.hpp>
// version 3 : use lambda to accept placeholder expr
namespace mpl = boost::mpl;
template <typename F, typename X>
struct twice3 
    : apply1<
           typename mpl::lambda<F>::type,
           typename apply1<typename mpl::lambda<F>::type, X>::type>{};

//version 4 : use standart apply to simplify the code
#include <boost/mpl/apply.hpp>
template <typename F, typename X>
struct twice4
    : mpl::apply<F, typename mpl::apply<F, X>::type>{};

// examples
#include <boost/type_traits/add_pointer.hpp>
#include <boost/mpl/placeholders.hpp>

using namespace mpl::placeholders;

template <class X>
struct two_pointers : 
    twice<typename mpl::lambda<boost::add_pointer<_> >::type, X> {};

// twice4 can accept placeholder expr
template <class X>
struct two_pointers2 : 
    twice4<boost::add_pointer<_>, X> {};

#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT((
    boost::is_same<
        two_pointers2<int>::type,
        int**
        >::value
));

template<class T>
struct four_pointers :
	twice4<
        twice4<boost::add_pointer<_>, _>, T> {};

template<class T>
struct four_pointers2 :
    twice4<boost::add_pointer<_>, 
        typename twice4<boost::add_pointer<_>, T>::type> {};

BOOST_STATIC_ASSERT((
    boost::is_same<
        four_pointers2<int>::type,
        int****
        >::value
));


int main(){
    int * x;
    twice4<boost::add_pointer<_>, int>::type q = &x;

    return 0;
}

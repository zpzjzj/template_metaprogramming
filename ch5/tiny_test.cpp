#include "tiny.hpp"
#include <boost/mpl/equal.hpp>
#include <iostream>
#include <boost/static_assert.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/insert.hpp>

int main() {
	typedef tiny<mpl::int_<1>, mpl::int_<2> > Input;

	std::cout << 
       mpl::equal<
			mpl::pop_back<Input>::type,
			tiny<mpl::int_<1> >
		>::type::value << std::endl;

	BOOST_STATIC_ASSERT((
        mpl::equal<
			mpl::pop_back<Input>::type,
			tiny<mpl::int_<1> >
		>::type::value
    ));

	BOOST_STATIC_ASSERT((
        mpl::equal<
			mpl::push_back<Input, mpl::int_<3> >::type,
			tiny<mpl::int_<1>, mpl::int_<2>, mpl::int_<3> >
		>::type::value
    ));

    BOOST_STATIC_ASSERT((
        mpl::equal<
			mpl::erase<
				Input,
				mpl::begin<Input>::type,
				// tiny_iterator<Input, mpl::int_<1> >
				tiny_iterator<Input, mpl::integral_c<int, 1> >
			>::type, 
			tiny<mpl::int_<2> >
		>::type::value
    ));

    BOOST_STATIC_ASSERT((
    	mpl::equal<
			mpl::insert<Input, mpl::end<Input>::type, mpl::int_<3> >::type,
			tiny<mpl::int_<1>, mpl::int_<2>, mpl::int_<3> >
		>::type::value
    ));

	return 0;
}
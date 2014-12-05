#include "tiny.hpp"
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/advance.hpp>


namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template <typename Seq>
struct double_first_half {
	typedef typename mpl::advance<
				typename mpl::begin<Seq>::type,
				typename mpl::divides<mpl::size<Seq>, mpl::int_<2> >
			>::type Pos;
	typedef typename mpl::erase<
				Seq,
				typename mpl::begin<Seq>::type,
				Pos>::type BackHalf;
	typedef typename mpl::erase<
				Seq, Pos,
				typename mpl::end<Seq>::type>::type HeadHalf;
	typedef typename mpl::insert_range<
				BackHalf,
				typename mpl::begin<BackHalf>::type,
				typename mpl::transform<HeadHalf, mpl::multiplies<mpl::int_<2>, _1> >::type
			>::type type;
};

#include <iostream>
#include <boost/static_assert.hpp>

int main(int argc, char const *argv[])
{
	std::cout << mpl::equal<
	double_first_half<mpl::vector_c<int, 1, 2, 3, 4> >::type,
	mpl::vector_c<int, 2, 4, 3, 4> >::type::value;

	typedef tiny<mpl::integral_c<int, 1>,
				mpl::integral_c<int, 2>,
				mpl::integral_c<int, 3>,
				mpl::integral_c<int, 4>
				> Input;
	std::cout <<
		mpl::equal<
			double_first_half<Input>::type,
			tiny<
				mpl::integral_c<int, 2>,
				mpl::integral_c<int, 4>,
				mpl::integral_c<int, 3>,
				mpl::integral_c<int, 4> >
		>::type::value;
	return 0;
}

#include <iterator>
#include "boost/mpl/advance.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/mpl/minus.hpp"
#include "boost/mpl/plus.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/push_back.hpp"
#include "boost/mpl/pop_front.hpp"
#include "boost/mpl/pop_back.hpp"

namespace mpl = boost::mpl;

struct tiny_tag{};

template <typename ...Args>
struct tiny
{
	typedef tiny_tag tag;
	typedef tiny type;
	typedef mpl::integral_c<int, sizeof...(Args)> size;
};

// get args[N]'s type
template <int N, typename ArgFirst, typename ...Args>
struct args_at : args_at<N - 1, Args...>{};

template <typename ArgFirst, typename ...Args>
struct args_at<0, ArgFirst, Args...>
{
	typedef ArgFirst type;
};

// used by at_impl
template <int N, typename ...Args>
struct tiny_at{};

template <int N, typename ...Args>
struct tiny_at<N, tiny<Args...> > : args_at<N, Args...>{};

template <typename Tiny, typename Pos>
struct tiny_iterator : tiny_at<Pos::value, Tiny>
{
	typedef std::random_access_iterator_tag category;
};

template <typename T, typename ...Args>
struct tiny_push_front {};

template <typename T, typename ...Args>
struct tiny_push_front<T, tiny<Args...> >
	: tiny<T, Args...> {};

template <int N, typename T, typename ArgFirst, typename ...Args>
struct tiny_insert {};

template <typename T, typename ...Args>
struct tiny_insert<0, T, tiny<Args...> >
	: tiny<T, Args...> {};

template <int N, typename T, typename ArgFirst, typename ...Args>
struct tiny_insert<N, T, tiny<ArgFirst, Args...> >
	: tiny_push_front<
		ArgFirst,
		typename tiny_insert<N - 1, T,  tiny<Args...> >::type > {};

template <int N, typename ArgFirst, typename ...Args>
struct tiny_erase {};

template <typename ArgFirst, typename ...Args>
struct tiny_erase<0, tiny<ArgFirst, Args...> > : tiny<Args...> {};

template <int N, typename ArgFirst, typename ...Args>
struct tiny_erase<N, tiny<ArgFirst, Args...> >
	: tiny_push_front<
		ArgFirst,
		typename tiny_erase<N - 1, tiny<Args...> >::type >{};

namespace boost {
	namespace mpl {
		template <typename Tiny, typename Pos>
		struct next<tiny_iterator<Tiny, Pos> > {
			typedef tiny_iterator<
						Tiny,
						typename mpl::next<Pos>::type
					> type;
		};

		template <typename Tiny, typename Pos>
		struct prior<tiny_iterator<Tiny, Pos> > {
			typedef tiny_iterator<
						Tiny,
						typename mpl::prior<Pos>::type
					> type;
		};

		template <>
		struct at_impl<tiny_tag>
		{
			template <typename Tiny, typename N>
			struct apply : tiny_at<N::value, Tiny> {};
		};

		template <typename Tiny, typename Pos, typename N>
		struct advance <tiny_iterator<Tiny, Pos>, N> {
			typedef tiny_iterator<
						Tiny,
						typename mpl::plus<Pos, N>::type> type;
		};

		template <typename Tiny, typename Pos1, typename Pos2>
		struct distance <tiny_iterator<Tiny, Pos1>,
			tiny_iterator<Tiny, Pos2> >
			: mpl::minus<Pos2, Pos1> {};

		template <>
		struct begin_impl<tiny_tag> {
			template <typename Tiny>
			struct apply {
				typedef tiny_iterator<Tiny, integral_c<int, 0> > type;
			};
		};

		template <>
		struct end_impl<tiny_tag> {
			template <typename Tiny>
			struct apply {
				typedef tiny_iterator<Tiny, typename Tiny::size> type;	
			};
		};

		template <>
		struct size_impl<tiny_tag> {
			template <typename Tiny>
			struct apply : Tiny::size {};
		};

		template <>
		struct clear_impl<tiny_tag> {
			template <typename Tiny>
			struct apply : tiny<> {};
		};

		template <>
		struct push_front_impl<tiny_tag> {
			template <typename Tiny, typename T>
			struct apply : tiny_push_front<T, Tiny> {};	
		};

		template <>
		struct push_back_impl<tiny_tag> {
			template <typename Tiny, typename T>
			struct apply : tiny_insert<Tiny::size::value, T, Tiny> {};
		};

		template <>
		struct pop_front_impl<tiny_tag> {
			template <typename Tiny>
			struct apply : tiny_erase<0, Tiny> {};
		};

		template <>
		struct pop_back_impl<tiny_tag> {
			template <typename Tiny>
			struct apply
				: tiny_erase<Tiny::size::value - 1, Tiny> {};
		};
	}
}
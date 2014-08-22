#include <boost/mpl/vector_c.hpp>

namespace mpl = boost::mpl;

typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
//typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> amount_of_substance;

typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;
typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;
typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;
typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;

#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>

template <class T, class Dimensions>
struct quantity {
    explicit quantity(T x) : m_value(x){}

    template<class OtherDimensions>
    quantity(quantity<T, OtherDimensions> const& rhs) : m_value(rhs.value()) {
        BOOST_STATIC_ASSERT((mpl::equal<Dimensions, OtherDimensions>::type::value));
    }

    T value() const {return m_value;}

private:
    T m_value;
};

template <class T, class D1, class D2>
quantity<T, D1> operator+ (quantity<T, D1> x, quantity<T, D2> y) {
    BOOST_STATIC_ASSERT((mpl::equal<D1, D2>::type::value));
    return quantity<T, D1>(x.value() + y.value());
}

template <class T, class D>
quantity<T, D> operator- (quantity<T, D> x, quantity<T, D> y) {
    return quantity<T, D>(x.value() - y.value());
}

struct plus_f {
    template <class T1, class T2>
    struct apply {
        typedef typename mpl::plus<T1, T2>::type type;
    };
};

struct minus_f {
    template <class T1, class T2>
    struct apply : mpl::minus<T1, T2> {};
};

#include <boost/mpl/transform.hpp>

template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, plus_f>::type>
operator* (quantity<T, D1> x, quantity<T, D2> y) {
    typedef typename mpl::transform<D1, D2, plus_f>::type dim;
    return quantity<T, dim>(x.value() * y.value());
}

#include <boost/mpl/placeholders.hpp>
using namespace mpl::placeholders;

template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, mpl::minus<_1, _2> >::type>
operator / (quantity<T, D1> x, quantity<T, D2> y) {
    typedef typename mpl::transform<D1, D2, mpl::minus<_1, _2> >::type dim;
    return quantity<T, dim>(x.value() / y.value());
}

#include <iostream>
#include <cmath>
int main() {
    quantity<float, mass> m(5.0f);
    quantity<float, acceleration> a(9.8f);
    quantity<float, force> f(0);
    f = f + m * a;
    std::cout << "force = " << f.value() << std::endl;

    quantity<float, mass> m2 = f / a;
    float rounding_error = std::abs((m2 - m).value());
    std::cout << "rounding_error = " << rounding_error << std::endl;
    return 0;
}

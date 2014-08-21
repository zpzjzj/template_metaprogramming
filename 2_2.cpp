struct A {
    virtual ~A() {};
};

struct B : A{};

struct C {};

#include <boost/cast.hpp>

namespace boost {
    template <class Target, class Source>
        Target polymorphic_downcast(Source& x) {
            return static_cast<Target>(x);
        }
}

int main(){
    B b;
    A *a_ptr = &b;
    B *b_ptr = boost::polymorphic_downcast<B*>(a_ptr);

    A& a_ref = b;
    B& b_ref = boost::polymorphic_downcast<B&>(a_ref);
    return 0;
}

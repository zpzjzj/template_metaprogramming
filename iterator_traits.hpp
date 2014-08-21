template<typename Iterator>
struct iterator_traits {
	typedef typename Iterator::value_type value_type;
};

template<typename T>
struct iterator_traits<T*> {
	typedef T value_type;
};

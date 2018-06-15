#pragma once

namespace detail {

template <class T, class... Args>
struct FactoryImpl {
	static T * create(Args &&... args) {
		T * t = new(std::nothrow) T;
		if (t && t->init(std::forward<Args>(args)...)) {
			t->autorelease();
			return t;
		}
		delete t;
		return nullptr;
	}
};

template <class T>
struct FactoryHelper;

template <class T, class... Args>
struct FactoryHelper<bool (T::*)(Args...)> {
    using type = FactoryImpl<T, Args...>;
};

} // detail

/**
 * This class allows to automatically add a static create member function to a class
 * which call the init() member function with the same parameters.
 * This class must be used as a parent class in a CRTP.
 */
template <class T>
struct Factory : detail::FactoryHelper<decltype(&T::init)>::type {};

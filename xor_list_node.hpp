#ifndef _XOR_LIST_NODE_HPP_
#define _XOR_LIST_NODE_HPP_

#include <cstdint>
#include <utility>

namespace detail {
	template<typename T>
	union ptr_union {
		uintptr_t intptr;
		T *ptr;

		constexpr ptr_union(T *ptr) : ptr(ptr) {}
		constexpr ptr_union(uintptr_t intptr) : intptr(intptr) {}
	};
}


template<typename T>
struct xor_list_node {
	using value_type = T;

	value_type value;
	uintptr_t both;

	constexpr xor_list_node(const value_type &value, uintptr_t both = 0) : value(value), both(both) {}
	constexpr xor_list_node(value_type &&value, uintptr_t both = 0) : value(std::move(value)), both(both) {}

	friend constexpr void swap(xor_list_node *&a, xor_list_node *&b) {
		auto tmp = a;
		a = b;
		b = tmp;
	}
};


template<typename T>
inline uintptr_t get_xor_of_nodes(detail::ptr_union<T> a, detail::ptr_union<T> b) {
	return a.intptr ^ b.intptr;
}

#endif
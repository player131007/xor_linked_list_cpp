#ifndef _XOR_LIST_NODE_HPP_
#define _XOR_LIST_NODE_HPP_

#include <cstdint>
#include <utility>

template<typename T>
struct xor_list_node {
	using value_type = T;

	value_type value;
	uintptr_t both;

	constexpr xor_list_node(const value_type &value, uintptr_t both = 0) : value(value), both(both) {}
	constexpr xor_list_node(value_type &&value, uintptr_t both = 0) : value(std::move(value)), both(both) {}
};

#endif
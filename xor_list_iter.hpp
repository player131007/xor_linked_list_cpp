#ifndef _XOR_LIST_ITER_HPP_
#define _XOR_LIST_ITER_HPP_

#include "xor_list_node.hpp"
#include <iterator>


//TODO: make iterator STL-compatible
//TODO: make const_iterator

template<typename T>
class xor_base_iterator {
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	using node = xor_list_node<std::remove_cv_t<T>>;
	node *prev,*curr;

	constexpr xor_base_iterator() : prev(nullptr), curr(nullptr) {}
	constexpr xor_base_iterator(node* prev,node *curr) : prev(prev),curr(curr) {}
	constexpr xor_base_iterator(const xor_base_iterator &other) : prev(other.prev),curr(other.curr) {}

	constexpr operator bool() const noexcept { return curr != nullptr; }
	constexpr friend bool operator==(const xor_base_iterator &a, const xor_base_iterator &b) noexcept {
		return a.curr==b.curr;
	}


	constexpr reference operator*() {
		return (curr->value);
	}
	constexpr pointer operator->() {
		return &curr->value;
	}


	constexpr xor_base_iterator& operator++() {
		node *tmp = curr;
		curr = reinterpret_cast<node*>(get_xor(curr->both,prev));
		prev = tmp;
		return *this;
	}
	constexpr xor_base_iterator& operator--() {
		node *tmp = prev;
		prev = reinterpret_cast<node*>(get_xor(prev->both, curr));
		curr = tmp;
		return *this;
	}


	constexpr xor_base_iterator operator++(int) {
		auto res = *this;
		++*this;
		return res;
	}
	constexpr xor_base_iterator operator--(int) {
		auto res = *this;
		--*this;
		return res;
	}

};

template<typename T>
class xor_list_iterator : public xor_base_iterator<T> {
public:
	using typename xor_base_iterator<T>::node;

	constexpr xor_list_iterator() : xor_base_iterator<T>() {}
	constexpr xor_list_iterator(node* prev,node *curr) : xor_base_iterator<T>(prev,curr) {}
	constexpr xor_list_iterator(const xor_list_iterator &other) : xor_base_iterator<T>(other) {}

	friend constexpr void swap(xor_list_iterator &a, xor_list_iterator &b) {
		auto tmp = a;
		a = b;
		b = tmp;
	}
};

template<typename T>
class xor_list_const_iterator : public xor_base_iterator<const T> {
public:
	using typename xor_base_iterator<const T>::node;

	constexpr xor_list_const_iterator() : xor_base_iterator<const T>() {}
	constexpr xor_list_const_iterator(node* prev,node *curr) : xor_base_iterator<const T>(prev,curr) {}
	constexpr xor_list_const_iterator(const xor_list_const_iterator &other) : xor_base_iterator<const T>(other) {}
	friend constexpr void swap(xor_list_const_iterator &a, xor_list_const_iterator &b) {
		auto tmp = a;
		a = b;
		b = tmp;
	}
};

#endif
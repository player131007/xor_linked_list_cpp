#ifndef _XOR_LIST_HPP_
#define _XOR_LIST_HPP_

#include "xor_list_iter.hpp"
#include "xor_list_node.hpp"


//TODO: add STL-like functions

template<typename T>
class xor_list {
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using node = xor_list_node<T>;
	using iterator = xor_list_iterator<T>;
	using reverse_iterator = iterator;
	using const_iterator = iterator;
	
	constexpr xor_list() : _begin(), _end() {}
	constexpr void push_back(const T& value) {
		node *new_node = new node(value);
		if(!_begin) {
			_begin.curr = _end.prev = new_node;
		} else {
			new_node->both = reinterpret_cast<uintptr_t>(_end.prev);
			_end.prev->both = get_xor(_end.prev->both,new_node);
			_end.prev = new_node;
		}
	}

	constexpr ~xor_list() {
		for(++_begin;_begin!=_end;++_begin) delete _begin.prev;
		delete _begin.prev;
	}


	constexpr iterator begin() { return _begin; }
	constexpr iterator end() { return _end; }
	constexpr reverse_iterator rbegin() { return reverse_iterator(_end.curr,_end.prev); }
	constexpr reverse_iterator rend() { return reverse_iterator(_begin.curr,_begin.prev); }


	constexpr xor_list<T>& reverse() {
		swap(_begin,_end);
		swap(_begin.prev, _begin.curr);
		swap(_end.prev, _end.curr);
		return *this;
	}

private:
	iterator _begin,_end;
};

#endif
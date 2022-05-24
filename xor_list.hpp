#ifndef _XOR_LIST_HPP_
#define _XOR_LIST_HPP_

#if __cplusplus <=201103L
#error "This XOR linked list implementation only supports C++11 and later versions."
#endif

#include "xor_list_iter.hpp"
#include "xor_list_node.hpp"


//TODO: add STL-like functions
//TODO: add exception guarantee

template<typename T>
class xor_list {
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using node = xor_list_node<T>;
	using iterator = xor_list_iterator<T>;
	using reverse_iterator = iterator;
	using const_iterator = xor_list_const_iterator<T>;
	
	constexpr xor_list() : _begin(), _end() {}
	constexpr void push_back(const T& value) {
		insert(_end,value);
	}

	constexpr iterator insert(const_iterator pos,const T& value) {
		return insert_by_node(pos,new node(value));
	}
	constexpr iterator insert(const_iterator pos,T&& value) {
		return insert_by_node(pos,new node(std::move(value)));
	}

	constexpr ~xor_list() {
		for(++_begin;_begin!=_end;++_begin) delete _begin.prev;
		delete _begin.prev;
	}


	constexpr iterator begin() { return _begin; }
	constexpr iterator end() { return _end; }
	constexpr reverse_iterator rbegin() { return reverse_iterator(_end.curr,_end.prev); }
	constexpr reverse_iterator rend() { return reverse_iterator(_begin.curr,_begin.prev); }
	constexpr const_iterator cbegin() { return const_iterator(_begin.prev,_begin.curr); }
	constexpr const_iterator cend() { return const_iterator(_end.prev,_end.curr); }


	constexpr xor_list<T>& reverse() {
		swap(_begin,_end);
		swap(_begin.prev, _begin.curr);
		swap(_end.prev, _end.curr);
		return *this;
	}

private:
	iterator _begin,_end;
	constexpr iterator insert_by_node(const_iterator pos, node *new_node) {
		if(pos.prev) pos.prev->both = get_xor(pos.prev->both,pos.curr,new_node);
		if(pos.curr) pos.curr->both = get_xor(pos.curr->both,pos.prev,new_node);
		new_node->both = get_xor(pos.prev,pos.curr);
		if(pos==_begin) _begin = iterator(nullptr,new_node);
		if(pos==_end) _end = iterator(new_node,nullptr);
		return iterator(pos.prev,new_node);
	}
};

#endif
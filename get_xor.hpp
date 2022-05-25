#ifndef _GET_XOR_HPP_
#define _GET_XOR_HPP_

#include <cstdint>
#include <type_traits>

#define unused __attribute__((unused))

namespace detail {
	template<typename T>
	uintptr_t get_uintptr(T t, unused std::true_type is_ptr) {
		return reinterpret_cast<uintptr_t>(t);
	}

	template<typename T>
	uintptr_t get_uintptr(T t, unused std::false_type is_ptr) {
		return static_cast<uintptr_t>(t);

	}

	template<typename T>
	constexpr bool is_numeric = std::is_integral<T>::value || std::is_pointer<T>::value;

	uintptr_t get_xor() {return 0;}

	template<typename Head,typename ...Tail>
	typename std::enable_if<is_numeric<Head>,uintptr_t>::type get_xor(Head head, Tail ...tail) {
		return get_uintptr(head,std::is_pointer<Head>()) ^ get_xor(tail...);
	}
}

#undef unused

#endif
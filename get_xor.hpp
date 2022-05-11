#ifndef _GET_XOR_H_
#define _GET_XOR_H_

#include <cstdint>
#include <type_traits>

namespace detail {
	template<typename T>
	constexpr uint64_t get_uint64(T val,std::true_type) {
		return reinterpret_cast<uint64_t>(val);
	}

	template<typename T>
	constexpr uint64_t get_uint64(T val,std::false_type) {
		return static_cast<uint64_t>(val);
	}

	template<typename T>
	constexpr bool is_numerical = std::is_integral<T>::value || std::is_pointer_v<T>::value;

#if __cplusplus >= 202002L
	template<typename T>
	concept numerical = is_numerical<T>;
#endif
}


#if __cplusplus >= 201703L

#if __cplusplus >= 202002L
template<detail::numerical Head,detail::numerical ...Tail> 
constexpr uint64_t get_xor(Head head, Tail ...tail)
#else
template<typename Head, typename ...Tail>
constexpr std::enable_if_t<detail::is_numerical<Head>,uint64_t> get_xor(Head head, Tail ...tail)
#endif

{
	uint64_t value;
	if constexpr(std::is_pointer_v<Head>) value = reinterpret_cast<uint64_t>(head);
	else value = static_cast<uint64_t>(head);
	if constexpr(sizeof...(Tail)) return value ^ get_xor(tail...);
	else return value;
}

#else

template<typename Head,typename ...Tail,typename = std::enable_if<detail::is_numerical<Head>,void>::type> 
constexpr std::enable_if<sizeof...(Tail)!=0,uint64_t>::type get_xor(Head head, Tail ...tail) {
	uint64_t value = detail::get_uint64(head,std::is_pointer<Head>());
	return value ^ get_xor(tail...);
}

template<typename Head,typename ...Tail,typename = std::enable_if<detail::is_numerical<Head>,void>::type>
constexpr std::enable_if<sizeof...(Tail)==0,uint64_t>::type get_xor(Head head, Tail ...tail) {
	uint64_t value = detail::get_uint64(head,std::is_pointer<Head>());
	return value;
}
#endif

#endif
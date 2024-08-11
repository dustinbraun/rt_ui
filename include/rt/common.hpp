#pragma once

#include <iostream>

// Allows us to change the inline behaviour if the compiler directly in the code or a config.hpp.
// I know, generally its said that the compiler knows much better than a human what should be inlined and what not,
// but I some trust issues here probably :D
// Anyway, we can not loose, just win with this option. there is no drawback, we can change it to be empty if we wish.
// It also indicates clearly that we seriously want to inline a method or function. E.g. when we know that a method
// will be called very often, we may want to force an inline because the compiler may not detect this without proper profiling.
// method which are declared RT_INLINE should also be defined and declared in a header file so that the code can be optimized
// even without LTO.
// LTO costs time, and time costs money, and money costs...

// #define RT_INLINE
#define RT_INLINE inline
// #define RT_INLINE __force_inline

#include <cassert>
#define RT_ASSERT assert

// A panic() is a release-mode assert.
// A panic must be used when we encounter an error we can not recover from, if the program continues, it will have
// undefined behaviour.
// It can be used for critical code.
inline void panic(const char* msg = "Oops!") {
	std::cerr << msg;

	// ToDo: Return a specific error-code which means that the program has paniced.
	// So we can expect and test for panics in unit-tests.
	std::exit(-1);
}

constexpr const char* PANIC_REASON_OUT_OF_MANA = "Out of memory.";

inline void not_implemented(const char* msg = "Not implemented.") {
	panic(msg);
}

inline void ToDo(const char* msg = "") {
	panic(msg);
}
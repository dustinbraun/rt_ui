#pragma once

#include <iostream>

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
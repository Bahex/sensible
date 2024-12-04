#ifndef SENSIBLE_COMMON_H
#define SENSIBLE_COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define STRINGIFY_(S) #S
#define STRINGIFY(S) STRINGIFY_(S)
#define CONCAT_(L, R) L##R
#define CONCAT(L, R) CONCAT_(L, R)

typedef uint8_t u8;
typedef int8_t i8;

typedef uint32_t u32;
typedef int32_t i32;

typedef uint64_t u64;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef size_t usize;
typedef ptrdiff_t isize;

// Size of value
#define m_sizeof(x) ((usize)sizeof(x))
// Count of array
#define countof(a) (m_sizeof(a) / m_sizeof(*(a)))
// Length of string *literal*
#define lengthof(s) (countof(s) - 1)
// Making use of a gnu extension to speed up writing code. Replace usages with
// actual type afterwards.
#define let __auto_type

// Similar to `memcpy`
static void clone(void *dest, const void *src, usize len) {
	u8 *_dest = dest;
	const u8 *_src = src;
	for (usize i = 0; i < len; i++) {
		_dest[i] = _src[i];
	}
}

#endif /* ifndef SENSIBLE_COMMON_H */

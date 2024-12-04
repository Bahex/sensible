// #define T u8
// #include <stdlib.h>

#ifndef T
#error "`T` is not defined, define it before including this file."
#else /* ifndef T */

#include "common.h"

#define Ts CONCAT(T, s)
#define T_buf CONCAT(T, _buf)
#define Ts_slice CONCAT(Ts, _slice)
#define Ts_from_ptr CONCAT(Ts, _from_ptr)
#define T_buf_at_least_cap CONCAT(T_buf, _at_least_cap)
#define T_buf_clone_from_slice CONCAT(T_buf, _clone_from_slice)
#define T_buf_with_capacity CONCAT(T_buf, _with_capacity)
#define T_buf_push CONCAT(T_buf, _push)

typedef struct Ts {
	T *data;
	usize len;
} Ts;

typedef union T_buf {
	Ts slice;
	struct {
		T *data;
		usize len;
		usize cap;
	};
} T_buf;

static Ts Ts_slice(Ts sl, usize b, usize e) {
	Ts r = {0};
	r.data = &sl.data[b];
	r.len = e - b;
	return r;
}

static Ts Ts_from_ptr(T *b, T *e) {
	Ts r = {0};
	r.data = b;
	r.len = e - b;
	return r;
}

#ifdef _STDLIB_H
static void T_buf_at_least_cap(T_buf *buf, usize size) {
	if (buf->cap >= size) {
		return;
	}
	if (buf->cap == 0) {
		buf->cap = 8;
	}
	while (buf->cap < size) {
		buf->cap *= 2;
	}
	buf->data = realloc(buf->data, sizeof(T) * buf->cap);
}

static void T_buf_clone_from_slice(T_buf *buf, Ts src) {
	T_buf_at_least_cap(buf, src.len);
	clone(buf->data, src.data, src.len);
	buf->len = src.len;
}

static T_buf T_buf_with_capacity(usize cap) {
	T_buf buf = {0};
	buf.data = malloc(sizeof(T) * cap);
	buf.cap = cap;
	return buf;
}

static void T_buf_push(T_buf *buf, T e) {
	if (buf->len >= buf->cap) {
		T_buf_at_least_cap(buf, buf->len + 1);
	}
	buf->data[buf->len] = e;
	buf->len += 1;
}

#endif /* ifndef STDLIB_H */

#undef Ts
#undef T_buf
#undef Ts_slice
#undef Ts_from_ptr
#undef T_buf_at_least_cap
#undef T_buf_clone_from_slice
#undef T_buf_with_capacity
#undef T_buf_push

#undef T
#endif /* ifndef T */

#ifndef SENSIBLE_STR_H
#define SENSIBLE_STR_H

#include "slice/u8.h"

typedef u8s str;
typedef u8_buf strbuf;

// Macro to create `str` from a string literal
#define str(s)               \
	(str) {                  \
		(u8 *)s, lengthof(s) \
	}

// format string for `str` values
#define fstr "%.*s"

// unpack `str` value for formatting with `fstr`
#define pstr(s) (int)(s).len, (s).data

// compare two strings for lexical order
static int str_cmp(str left, str right) {
	usize len = left.len < right.len ? left.len : right.len;
	for (usize i = 0; i < len; i++) {
		int d = left.data[i] - right.data[i];
		if (d != 0) {
			return d < 0 ? -1 : 1;
		}
	}
	if (left.len == right.len) {
		return 0;
	}
	return left.len < right.len ? -1 : 1;
}

// compare two strings for equality
static bool str_equals(str left, str right) {
	if (left.len != right.len) {
		return false;
	}
	return str_cmp(left, right) == 0;
}

// create a `str` from a pointer pair [start, end)
static str str_from_ptr(u8 *start, u8 *end) {
	str r = {0};
	r.data = start;
	r.len = end - start;
	return r;
}

static bool is_whitespace(u8 c) {
	return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static bool is_comma(u8 c) {
	return c == ',';
}

static str str_trim(str s) {
	if (s.len == 0) {
		return s;
	}

	u8 *b = s.data;
	u8 *e = b + s.len;

	for (; b < e && is_whitespace(b[0]); b++) {}
	for (; b < e && is_whitespace(e[-1]); e--) {}
	return str_from_ptr(b, e);
}

typedef bool fn_is_char(u8);

static usize str_span_fn(str s, fn_is_char *fn) {
	usize len = 0;
	for (; len < s.len && fn(s.data[len]); len++) {}
	return len;
}

static usize str_span_not_fn(str s, fn_is_char *fn) {
	usize len = 0;
	for (; len < s.len && !fn(s.data[len]); len++) {}
	return len;
}

static str str_sep_fn(str *rest, fn_is_char *fn) {
	str r = {0};

	// Return NULL on NULLs *and* zero length strings
	if (rest->data == NULL || rest->len == 0) {
		return r;
	}

	// Advance rest, skipping all consecutive `sep` characters
	usize skip = str_span_fn(*rest, fn);
	rest->data += skip;
	rest->len -= skip;

	// Get non `sep` string in `r`
	r.data = rest->data;
	r.len = str_span_not_fn(*rest, fn);
	rest->data += r.len;
	rest->len -= r.len;

	// Advance rest, skipping all consecutive `sep` characters
	skip = str_span_fn(*rest, fn);
	rest->data += skip;
	rest->len -= skip;

	return r;
}

static str str_sep_fn_each(str *rest, fn_is_char *fn) {
	str r = {0};

	// Return NULL on NULL
	if (rest->data == NULL) {
		return r;
	}

	// If `rest` is 0 length, pass it to `r` and set `rest` NULL.
	if (rest->len == 0) {
		r.data = rest->data;
		rest->data = NULL;

		return r;
	}

	// Get non `sep` string in `r`
	r.data = rest->data;
	r.len = str_span_not_fn(*rest, fn);
	rest->data += r.len;
	rest->len -= r.len;

	// Skip one `sep` character in `rest` if it exists
	if (rest->len > 0 && fn(rest->data[0])) {
		rest->data++;
		rest->len--;
	}

	return r;
}

#ifdef	_STRING_H

// create a `str` from c string, calls `strlen()`
static str str_from_cstr(char *s) {
	str r = {0};
	r.data = (u8 *)s;
	r.len = strlen(s);
	return r;
}

#endif

#ifdef _STDLIB_H

#define strbuf_at_least_cap u8_buf_at_least_cap
#define strbuf_clone_from_str u8_buf_clone_from_slice
#define strbuf_with_capacity u8_buf_with_capacity
#define strbuf_buf_push u8_buf_push

static char *strbuf_as_cstr(strbuf *buf) {
	strbuf_at_least_cap(buf, buf->len + 1);
	buf->data[buf->len] = 0;
	return (char *)buf->data;
}

static str str_clone(str s) {
	str r = {0};
	r.len = s.len;
	r.data = malloc(r.len);
	clone(&r.data, &s.data, r.len);
	return r;
}

#endif /* ifdef _STDLIB_H */

#endif /* ifndef SENSIBLE_STR_H */

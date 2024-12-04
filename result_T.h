// #define T u8

#ifndef T
#error "`T` is not defined, define it before including this file."
#else /* ifndef T */

#include "common.h"
#include "panic.h"

#define Result_T CONCAT(Result_, T)
#define Result_T_Ok CONCAT(Result_T, _Ok)
#define Result_T_Err CONCAT(Result_T, _Err)
#define Result_T_is_ok CONCAT(Result_T, _is_ok)
#define Result_T_is_err CONCAT(Result_T, _is_err)
#define Result_T_unwrap CONCAT(Result_T, _unwrap)
#define Result_T_expect CONCAT(Result_T, _expect)
#define Result_T_unwrap_or CONCAT(Result_T, _unwrap_or)
#define Result_T_unwrap_err CONCAT(Result_T, _unwrap_err)

typedef struct Result_T {
	T value;
	/* string literals only */
	const char *err;
} Result_T;

static Result_T Result_T_Ok(T value) {
	Result_T res = {.value = value, .err = NULL};
	return res;
}

static Result_T Result_T_Err(const char *err) {
	Result_T res = {.err = err};
	return res;
}

static bool Result_T_is_ok(const Result_T *res) {
	return res->err == NULL;
}

static bool Result_T_is_err(const Result_T *res) {
	return res->err != NULL;
}

static T Result_T_unwrap(const Result_T *res) {
	if (Result_T_is_err(res)) {
		panicf(
			"Attempted to unwrap empty Result of type " STRINGIFY(T
			) ". Instead had error: %s",
			res->err
		);
	}
	return res->value;
}

static T Result_T_expect(const Result_T *res, const char *message_on_err) {
	if (Result_T_is_err(res)) {
		panic(message_on_err);
	}
	return res->value;
}

static T Result_T_unwrap_or(const Result_T *res, T else_val) {
	if (Result_T_is_err(res)) {
		return else_val;
	}
	return res->value;
}

static const char *Result_T_unwrap_err(const Result_T *res) {
	if (Result_T_is_ok(res)) {
		panic("Result was not an error; type: " STRINGIFY(T));
	}
	return res->err;
}

#undef Result_T
#undef Result_T_Ok
#undef Result_T_Err
#undef Result_T_is_ok
#undef Result_T_is_err
#undef Result_T_unwrap
#undef Result_T_expect
#undef Result_T_unwrap_or
#undef Result_T_unwrap_err

#undef T
#endif /* ifndef T */

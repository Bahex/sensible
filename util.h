#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "str.h"
#include "result/strbuf.h"

static Result_strbuf read_file(char const *filename) {
	FILE *const fp = fopen(filename, "r");

	if (fp == NULL) {
		return Result_strbuf_Err("Failed to open file");
	}

	fseek(fp, 0, SEEK_END);
	usize const length = (usize)ftell(fp);
	fseek(fp, 0, SEEK_SET);

	strbuf buffer = strbuf_with_capacity(length);
	if (buffer.data == NULL) {
		fclose(fp);
		return Result_strbuf_Err("Can't allocate memory");
	}
	fread(buffer.data, sizeof(u8), length, fp);
	fclose(fp);

	buffer.len = length;

	return Result_strbuf_Ok(buffer);
}

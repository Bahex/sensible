# a `sensible` library to fill in the cracks

This library is a collection of headers that I use in most of my C projects.
Some patterns here are inspired by the Rust programming language and standard
library.

Contains a somewhat successful attempt at generics in C. Files whose names end
with `_T` are generic templates, included after `#define`ing `T`.

If an instance of a generic type is required in multiple files, a separate
header instantiating that type should be created with and
`#ifndef-define-endif` guard. e.g. `slice/u8.h`

Re-entrancy and thread safety should be a primary concern. Static variables and
globals are avoided.

## Slice
Length terminated generic array pointer. Comes with a rudimentary dynamic
array/growable buffer.

## Str
Null byte terminated C-strings are bothersome, and length terminated strings
are much more convenient and safe.

Backed by `slice<u8>`.

Includes some utilities for splitting and trimming strings.

## Result and Panic
Regrettably, C does not support sum types (tagged unions) natively. Result is
an attempt at an implementation of a sum type, representing the possibility of
failure in a functions signature.

`result` provides an alternative to sentinel values (e.g. returning `-1` to
signify error) or globals (`errno`)

Panic is for the immediate termination of the program. Should be used when the
program can't meaningfully continue execution.

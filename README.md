# jot
Diffing and versioning tool written in c89.

## Building
Just use the Makefile.

rules:
- `make setup` creates the intermediate `build/` and `deps/` directories as well as the output binary directory, `bin/`.
- `make all` (default rule) will produce the object files in the `build/` directory and then produce the output binary, called `jot`, in the `bin/` directory. It will also generate dependency files for make in the `deps/` directory to help make build faster.
- `make clean` removes everything in the `bin`, `build`, `deps/` dirs.
- [not impl] `make test` run the tests in `test/`.
- [not impl] `make check` runs valgrind against the output binary.

There are some options that can be set in the Makefile:
- `debug`: setting to 1 enables a debug build by adding the `-g` and `-O0` CFLAGS (defaults to 0 which set `-03` and `DNDEBUG` CFLAGS)
- `sanitize`: setting to 1 enables the use of `-fsanitize=address,leak,undefined` option. (defaults to 0 which disables this option) (requires `libasan`, `liblsan`, and `libubsan`)


_note: please see warning at the bottom of this README.md if you plan to run where CC != gcc_

## Overview
A diff is an operation based on solving the [longest common sequence](https://en.wikipedia.org/wiki/Longest_common_subsequence) (or LCS) problem. The idea is to take a starting state (a string of text or a file itself) and the end state, then produce the smallest number of changes that can be applied to the start state to reach the end state. It does this by minimzing the number of deletions and insertions that need to be applied ot the start state to reach the end state.

This might sound a little like the Levenshtein distance (or LD) string metric and it is quite similar. However, the difference between the LSC and LD is that LCS doesn't allow outright subtitutions whereas LD allows for substitutions. This is an important differentiating factor between the edit distance metrics.

## Part 1 - Diff 2 files
For the first part of this tool, I want to diff 2 files using a diffing algorithm known a Myers diffing algorithm. It is described in detail by Eugene Myers [here](http://www.xmailserver.org/diff2.pdf).

## Warning
I have only compiled and run with `gnu make` and `gcc 15.2` (though, I imagine any gcc version works because this is in ANSI C). That is what the Makefile is geared towards with its current CFLAGS. If cc != gcc on your machine, run the Makefile with `make CC=gcc` for now.

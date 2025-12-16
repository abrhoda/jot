# jot
Diffing and versioning tool

## Building
It's a simple project with 1 `.c` file. However, I'm compiling with a healthy amount of compiler options. The Makefile is not good for a few reasons but for a dead simple project, it works for now. So, just use the Makefile. `make` or `make all` will produce the output binary, called `jot`. `make clean` removes this binary.

_note: Makefile.complex exists for when/if this project progresses and I want to use it instead. For now, it's unused._

## Overview
A diff is an operation based on solving the [longest common sequence](https://en.wikipedia.org/wiki/Longest_common_subsequence) (or LCS) problem. The idea is to take a starting state (a string of text or a file itself) and the end state, then produce the smallest number of changes that can be applied to the start state to reach the end state. It does this by minimzing the number of deletions and insertions that need to be applied ot the start state to reach the end state.

This might sound a little like the Levenshtein distance (or LD) string metric and it is quite similar. However, the different between the LSC and LD is that LCS doesn't allow outright subtitutions where as LD allows for substitutions. This is an important differentiating factor between the edit distance metrics.

## Part 1 - Diff Strings
For the first part of this tool, I want to diff 2 string using a diffing algorithm known a Myers diffing algorithm. It is described in detail by Eugene Myers [here](http://www.xmailserver.org/diff2.pdf).

## Warning
I have only compiled and run with `gnu make` and `gcc 15.2` (though, I imagine any gcc version works because this is in ANSI C). That is what the Makefile is geared towards with its current CFLAGS. If cc != gcc on your machine, run the Makefile with `make CC=gcc` for now.

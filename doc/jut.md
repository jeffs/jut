# Project JUT: Jeff's Utilities

This repository is intended to hold a collection of useful C++ code, general-
purpose libraries and specific application.

## Package structure

The `src` directory contains two subdirectories: `app` contains top-level
APPlications (i.e., definitions of `::main`), whereas `jut` contains a group of
*packages*, each having a distinct name and defining one or more *components*.

A component is a set of source files whose paths differ only in the file
extension; e.g., a component may be a single `.py` file or a `.[hc]` pair, or
even some combination thereof (so long as the files live in the same directory
and have the same base name).

A package may define at most one group-level component directly within `jut`,
having the same base name as the package, as well as any number of components
within a subdirectory having the same name as the package.

Relative to the `src` directory:

    app                 - APPlications; i.e., definitions of ::main
    jut                 - Jeff's UTilities library packages
     `- slw             - Standard Library Wrappers
         `- std.hpp     - STanDard library headers 

## Style

C++ code defined in `jut` conforms to the following guidelines:

* At least two levels of namespace: `jut` and the package name
* Macro names begin `JUT_PKG_`, where `PKG` is the package name
* Indent four spaces, but only two for labels and operators
* 79 columns
* UTF-8
* No newline between `)` and `{`; e.g., `int main() {`

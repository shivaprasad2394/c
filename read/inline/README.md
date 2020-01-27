# inline 

https://www.greenend.org.uk/rjk/tech/inline.html
Introduction
GNU C (and some other compilers) had inline functions long before standard C introduced them (in the 1999 standard); this page summarizes the rules they use, and makes some suggestions as to how to actually use inline functions.

The point of making a function inline is to hint to the compiler that it is worth making some form of extra effort to call the function faster than it would otherwise - generally by substituting the code of the function into its caller. As well as eliminating the need for a call and return sequence, it might allow the compiler to perform certain optimizations between the bodies of both functions.

Sometimes it is necessary for the compiler to emit a stand-alone copy of the object code for a function even though it is an inline function - for instance if it is necessary to take the address of the function, or if it can't be inlined in some particular context, or (perhaps) if optimization has been turned off. (And of course, if you use a compiler that doesn't understand inline, you'll need a stand-alone copy of the object code so that all the calls actually work at all.)

There are various ways to define inline functions; any given kind of definition might definitely emit stand-alone object code, definitely not emit stand-alone object code, or only emit stand-alone object code if it is known to be needed. Sometimes this can lead to duplication of object code, which is a potential problem for following reasons:

It wastes space.
It can cause pointers to what is apparently the same function to compare not equal to one another.
It might reduce the effectiveness of the instruction cache. (Although inlining might do that in other ways too.)
If any of these are a problem for you then you will want to use a strategy that avoids duplication. These are discussed below.

C99 inline rules
The specification for inline is section 6.7.4 of the C99 standard (ISO/IEC 9899:1999). Unfortunately this isn't freely available. The following possibilities exist:

A function where all the declarations (including the definition) mention inline and never extern. There must be a definition in the same translation unit. The standard refers to this as an inline definition. No stand-alone object code is emitted, so this definition can't be called from another translation unit.

You can1 have a separate (not inline) definition in another translation unit, and the compiler might choose either that or the inline definition.

Such functions may not contain modifiable static variables, and may not refer to static variables or functions elsewhere in the source file where they are declared.

In this example, all the declarations and definitions use inline but not extern:

// a declaration mentioning inline
inline int max(int a, int b);

// a definition mentioning inline
inline int max(int a, int b) {
  return a > b ? a : b;
}
The function won't be callable from other files; if another file has a definition that might be used instead.

1 The standard is vague on this point. It says that the inline definition does not forbid an external definition elsewhere, but then that it provides an alternative to an external definition. Unfortunately this doesn't really make clear whether this external definition must actually exist.

In practice unless you are torture-testing your compiler it will exist: if you wanted to keep your inline function entirely private to one translation unit, you make it static inline.

A function where at least one declaration mentions inline, but where some declaration doesn't mention inline or does mention extern. There must be a definition in the same translation unit. Stand-alone object code is emitted (just like a normal function) and can be called from other translation units in your program.

The same constraint about statics above applies here, too.

In this example all the declarations and definitions use inline but one adds extern:

// a declaration mentioning extern and inline
extern inline int max(int a, int b);

// a definition mentioning inline
inline int max(int a, int b) {
  return a > b ? a : b;
}
In this example, one of the declarations does not mention inline:

// a declaration not mentioning inline
int max(int a, int b);

// a definition mentioning inline
inline int max(int a, int b) {
  return a > b ? a : b;
}
In either example, the function will be callable from other files.

A function defined static inline. A local definition may be emitted if required. You can have multiple definitions in your program, in different translation units, and it will still work. Just dropping the inline reduces the program to a portable one (again, all other things being equal).

This is probably useful primarily for small functions that you might otherwise use macros for. If the function isn't always inlined then you get duplicate copies of the object code, with the problems described above.

A sensible approach would be to put the static inline functions in either a header file if they are to be widely used or just in the source files that use them if they are only ever used from one file.

In this example the function is defined static inline:

// a definition using static inline
static inline int max(int a, int b) {
  return a > b ? a : b;
}
The first two possibilities go together naturally. You either write inline everywhere and extern in one place to request a stand-alone definition, or write inline almost everywhere but omit it exactly once to get the stand-alone definition.

main is not allowed to be an inline function.

(If you think I've misinterpreted these rules, please let me know!)

(C++ is stricter: a function which is inline anywhere must be inline everywhere and must be defined identically in all the translation units that use it.)

GNU C inline rules
The GNU C rules are described in the GNU C manual, which is included with the compiler. This is freely available if you follow links from e.g. http://gcc.gnu.org. The following possibilities exist:

A function defined with inline on its own. Stand-alone object code is always emitted. You can only write one definition like this in your entire program. If you want to use it from other translation units to the one where it is defined, you put a declaration in a header file; but it would not be inlined in those translation units.

This is of rather limited use: if you only want to use the function from one translation unit then static inline below makes more sense, if not the you probably want some form that allows the function to be inlined in more than one translation unit.

However it does have the advantage that by defining away the inline keyword, the program reduces to a portable program with the same meaning (provided no other non-portable constructions are used).

A function defined with extern inline. Stand-alone object code is never emitted. You can have multiple such definitions and your program will still work. However, you should add a non-inline definition somewhere too, in case the function is not inlined everywhere.

This provides sensible semantics (you can avoid duplicate copies of the functions' object code) but is a bit inconvenient to use.

One approach to using this would be to put the definitions in a header file, surrounded by a #if that expands to true either when using GNU C, or when the header has been included from the file that is contain the emitted definitions (whether or not using GNU C). In the latter case the extern is omitted (for instance writing EXTERN and #define-ing that to either extern or nothing). The #else branch would contain just declarations of the functions, for non-GNU compilers.

A function defined with static inline. Stand-alone object code may be emitted if required. You can have multiple definitions in your program, in different translation units, and it will still work. This is the same as the C99 rules.

As of release 4.3, GNU C supports the C99 inline rules described above and defaults to them with the -std=c99 or -std=gnu99 options. The old rules can be requested in new compilers with the -gnu89-inline option or via the gnu_inline function attribute.

If the C99 rules are in force then GCC will define the __GNUC_STDC_INLINE__ macro. Since GCC 4.1.3, it will define __GNUC_GNU_INLINE__ if the GCC-only rules are in use, but older compilers use these rules without defining either macro. You could normalize the situation with a fragment like this:

#if defined __GNUC__ && !defined __GNUC_STDC_INLINE__ && !defined __GNUC_GNU_INLINE__
# define __GNUC_GNU_INLINE__ 1
#endif
Strategies for using inline functions
These rules suggest several possible models for using inline functions in more or less portable ways.

A simple portable model. Use static inline (either in a common header file or just in one file). If the compiler needs to emit a definition (e.g. to take its address, or because it doesn't want to inline some call) then you waste a bit of space; if you take the address of the function in two translation units then the result won't compare equal.

For instance, in a header file:

static inline int max(int a, int b) {
  return a > b ? a : b;
}
You can support legacy compilers (i.e. anything without inline) via -Dinline="", although this may waste space if the compiler does not optimize out unused functions..

A GNU C model. Use extern inline in a common header and provide a definition in a .c file somewhere, perhaps using macros to ensure that the same code is used in each case. For instance, in the header file:

#ifndef INLINE
# define INLINE extern inline
#endif
INLINE int max(int a, int b) {
  return a > b ? a : b;
}
...and in exactly one source file:

#define INLINE
#include "header.h"
Supporting legacy compilers is awkward unless you don't mind wasting space and having multiple addresses for the same function; you need to restrict the definitions to a in single translation unit (with INLINE defined to the empty string) and add some external declarations in the header file.

A C99 model. Use inline in a common header, and provide definitions in a .c file somewhere, via extern declarations. For instance, in the header file:

inline int max(int a, int b) {
  return a > b ? a : b;
}
...and in exactly one source file:

#include "header.h"
extern int max(int a, int b);
To support legacy compilers, you have to swap the whole thing around so that the declarations are visible in the common header and the definitions are restricted to a single translation unit, with inline defined away.

A complicated portable model. Use macros to choose either extern inline for GNU C, inline for C99, or neither for a definition. For instance, in the header:

#ifndef INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif
INLINE int max(int a, int b) {
  return a > b ? a : b;
}
...and in exactly one source file:

#define INLINE
#include "header.h"
Supporting legacy compilers has the same issues as the GNU C model.

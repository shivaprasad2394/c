# strings
[todo here help yourself with more]

    characters with null termination is called Strings.
    C-style strings, which are arrays, there are also string literals, such as "this".
    In reality, both of these string types are merely just collections of characters sitting next to each other in memory.

    Whenever you write a string, enclosed in double quotes, C automatically creates an array of characters for us, 
    containing that string, terminated by the \0 character.

    For example, you can declare and define an array of characters, and initialize it with a string constant:

    char string[] = "Hello cruel world!";
    
    Straightforward answer: You don't really need to worry about the usage of characters with null termination, 
    this work independent of any platform.

[further help for strings follow the links!!!]
[# the examples are buggy and outdated pls help yourself]
---------------------------------------------------------
extras:-In any embedded work it is important to establish and maintain an Interface Control Document, (IDC), that defines all of your communications structures including string formats, endianness, integer sizes, etc., as soon as possible, (ideally before starting), and it should be your, and all the teams, holy book when writing the system - if someone wishes to introduce a new structure or format it must be documented there first and everybody that might be impacted informed, possibly with an option to veto the change

Determination of the terminating character is up to the compiler for literals and the implementation of the standard library for strings in general. It isn't determined by the operating system.

The convention of NUL termination goes back to pre-standard C, and in 30+ years, I can't say I've run into an environment that does anything else. This behavior was codified in C89 and continues to be part of the C language standard (link is to a draft of C99):

Section 6.4.5 sets the stage for NUL-terminated strings by requiring that a NUL be appended to string literals.
Section 7.1.1 brings that to the functions in the standard library by defining a string as "a contiguous sequence of characters terminated by and including the first null character."
There's no reason why someone couldn't write functions that handle strings terminated by some other character, but there's also no reason to buck the established standard in most cases unless your goal is giving programmers fits. :-)
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf
https://wiki.c2.com/?NonNullTerminatedString

https://softwareengineering.stackexchange.com/questions/344603/are-c-strings-always-null-terminated-or-does-it-depend-on-the-platform

--------------------------------------------------------------------------------------------------------------
Others have addressed the issue that in C, strings are largely what you make of them. But there seems to be some confusion in your question w.r.t. the terminator itself, and from one perspective, this could be what someone in your position is worried about.

# C strings are null-terminated. That is, they are terminated by the null character, NUL. They are not terminated by the null pointer NULL, which is a completely different kind of value with a completely different purpose.

NUL is guaranteed to have the integer value zero. Within the string, it will also have the size of the underlying character type, which will usually be 1.

NULL is not guaranteed to have an integer type at all. NULL is intended for use in a pointer context, and is generally expected to have a pointer type, which shouldn't convert to a character or integer if your compiler is any good. While the definition of NULL involves the glyph 0, it is not guaranteed to actually have that value[1], and unless your compiler implements the constant as a one-character #define (many don't, because NULL really shouldn't be meaningful in a non-pointer context), the expanded code is therefore not guaranteed to actually involve a zero value (even though it confusingly does involve a zero glyph).

If NULL is typed, it will also be unlikely to have a size of 1 (or another character size). This may conceivably cause additional problems, although actual character constants don't have character size either for the most part.

Now most people will see this and think, "null pointer as anything other than all-zero-bits? what nonsense" - but assumptions like that are only safe on common platforms like x86. Since you've explicitly mentioned an interest in targeting other platforms, you need to take this issue into account, as you have explicitly separated your code from assumptions about the nature of the relationship between pointers and integers.

# Therefore, while C strings are null-terminated, they aren't terminated by NULL, but by NUL (usually written '\0'). Code which explicitly uses NULL as a string terminator will work on platforms with a straightforward address structure, and will even compile with many compilers, but it's absolutely not correct C.

[1] the actual null pointer value is inserted by the compiler when it reads a 0 token in a context where it would be converted to a pointer type. This is not a conversion from the integer value 0, and is not guaranteed to hold if anything other than the token 0 itself is used, such as a dynamic value from a variable; the conversion is also not reversible, and a null pointer doesn't have to yield the value 0 when converted to an integer.

----------------------------------------------------------------------------------------------------

I am working with embedded systems ... with no operating system...I am...using the idea of having NULL terminated character pointers and treating them as strings where the NULL signifies the end. I know that this is fairly common, but can you always count on this to be the case?

There is no string data type in the C language, but there are string literals.

If you put a string literal in your program, it will usually be NUL terminated (but see the special case, discussed in comments below.) That is to say, If you put "foobar" in a place where a const char * value is expected, the compiler will emit foobar⊘ to the const/code segment/section of your program, and the value of the expression will be a pointer to the address where it stored the f character. (Note: I am using ⊘ to signify the NUL byte.)

The only other sense in which the C language has strings is, it has some standard library routines that operate on NUL terminated character sequences. Those library routines will not exist in a bare metal environment unless you port them yourself.

They're just code---no different from the code that you yourself write. If you don't break them when you port them, then they will do what they always do (e.g., stop on a NUL.)

--------------------------------------------------------------------------------------------------------------
1
Re: "If you put a string literal in your program, it will always be NUL terminated": Are you sure about that? I'm pretty sure that (e.g.) char foo[4] = "abcd"; is a valid way to create a non-null-terminated array of four characters. – ruakh Mar 21 '17 at 20:32
1
@ruakh, Oops! that's a case that I did not consider. I was thinking about a string literal that appear in a place where a char const * expression is expected. I forgot that C initializers can sometimes obey different rules. – Solomon Slow Mar 21 '17 at 20:47
@ruakh The string literal is NUL-terminated. The array is not. – jamesdlin Mar 22 '17 at 6:44
@jamesdlin: What do you mean? – ruakh Mar 22 '17 at 7:27
2
@ruakh you have a char[4]. That is not a string, but it was initialised from one – Caleth Mar 22 '17 at 9:33
2
@Caleth, "initialized from one" is not something that must happen at run time. If we add the keyword static to Ruakh's example, then the compiler may emit a non NUL terminated "abcd" to an initialized data segment so that the variable is initialized by the program loader. So, Ruakh was right: There is at least one case where the appearance of a string literal in a program does not require the compiler to emit a NUL-terminated string. (p.s., I actually compiled the example with gcc 5.4.0, and the compiler did not emit the NUL.) – Solomon Slow Mar 22 '17 at 13:17 
@jameslarge my point is there aren't "string literals" in the data segment or at runtime. There are char[]s, of various lengths, most of which have a NUL terminator, which get pretty printed as "abcd/0" or "abcd" etc. – Caleth Mar 22 '17 at 13:49
@Caleth, Sorry, I think I mixed up your comment with jamesdlin's comment when I responded. – Solomon Slow Mar 22 '17 at 14:05
this is the right answer, but i would add that whether a compiler emits a nul-terminated array for the example char[4] is a matter of optimization, not lamguage definition. a compiler could emit just about anything, so long as it has the right semantics. – user223083 Mar 22 '17 at 20:03

---------------------------------------------------------------------------------------------

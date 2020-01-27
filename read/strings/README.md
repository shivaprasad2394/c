# strings
[todo here help yourself with more]

https://softwareengineering.stackexchange.com/questions/344603/are-c-strings-always-null-terminated-or-does-it-depend-on-the-platform
I am working with embedded systems ... with no operating system...I am...using the idea of having NULL terminated character pointers and treating them as strings where the NULL signifies the end. I know that this is fairly common, but can you always count on this to be the case?

There is no string data type in the C language, but there are string literals.

If you put a string literal in your program, it will usually be NUL terminated (but see the special case, discussed in comments below.) That is to say, If you put "foobar" in a place where a const char * value is expected, the compiler will emit foobar⊘ to the const/code segment/section of your program, and the value of the expression will be a pointer to the address where it stored the f character. (Note: I am using ⊘ to signify the NUL byte.)

The only other sense in which the C language has strings is, it has some standard library routines that operate on NUL terminated character sequences. Those library routines will not exist in a bare metal environment unless you port them yourself.

They're just code---no different from the code that you yourself write. If you don't break them when you port them, then they will do what they always do (e.g., stop on a NUL.)

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

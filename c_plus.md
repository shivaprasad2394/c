Intro
-----
          - Origns:-Bell Labs(1979)
          - Scope of languague:-compiler,OS & games
          - c v/s c++
          - C is Procedure/process oriented, structured
          - C++ is Object oriented


What Are Variables?
-------------------

          A variable is a named storage in memory to hold a value. Think of it as a labeled box.
          int age = 25;

This declares a variable named age of type int (integer), and stores the value 25 in it.


Basic Data Types in C++
------------------------
          Type	Size	Description
          int	4 bytes	Whole numbers
          float	4 bytes	Numbers with decimal points
          double	8 bytes	More precise decimal numbers
          char	1 byte	A single character ('a')
          bool	1 byte	Boolean values (true/false)
          void	—	No value (used in functions)

🛠 Namespace
------------
          Namespace:-C++  Namespace are used to group logically related functions,variables and other entities to avoid name conflicts.

⚠️ Examples
-----------------
          Namespace Graphics{
                    class image{
                              //Image processing code
                    };
          }
          Namespace Audio{
                    class image{//same name ,different namespace
                              //Audio related code
                    };
          }
          Graphics::Image img1;//No conflict
          Audio::Image img2;

Namespace Alias:
---------------
          To simplify long namespace name ,you can use aliases.
          Namespace LongNamespaceName{
                    class Example{//same name ,different namespace
                          //Audio related code
                    };}
                    namespace LNN=LongNamespaceName;//Alias
                    LNN::Example  obj;//Easier to use.

🧠 Const & Macros
-----------------
          #define directive can also be used to define symbolic constants that do not require a data type. 
          They are called macros and are replaced by their values at compile time.
          Syntax:
          #define CONSTANT_NAME value

          constant variables in c are immutable after its definition, i.e., they can be initialized only once in the whole program. 
          After that, we cannot modify the value stored inside that variable.

🧪 Static
---------
**Static Variables in a Function**

          - Memory space is Aloocated only once in static storage.
          - The value of the variable is persistent.
          - Scope is Lifetime of the Program.

**Static Member Variable in a Class**

          - static member variables in a class are shared by the objects. 
          * There cannot be multiple copies of the same static variables for different objects. 
          + Also because of this reason static variables cannot be initialized using constructors.
          + static variable inside a class should be initialized explicitly by the user using the class name and scope resolution operator outside the class

**Example**

          #include <iostream>
          using namespace std;
          
          class GfG {
          public:
            
              // Static data member
              static int i;
          
              GfG(){
                  // Do nothing
              };
          };
          
          // Static member inintialization
          int GfG::i = 1;//OK
          
          int main() {
            GfG obj1;
            GfG obj2;
            obj1.i=2;//❗ **Not possible**
              // Prints value of i
              cout << GfG::i;//OK
          }


**Static Member Functions in a Class**

          - Static member functions are allowed to access only the static data members or other static member functions, 
          - they cannot access the non-static data members or member functions of the class. 

**Applications**

The static member functions have the following uses in C++:

- Accessing Static Member Variables
- Implement helper functions that do not depend on specific instances.
- Singleton Pattern Implementation
- Factory Methods to create and return objects without requiring an instance of the class.
- Logging and Debugging

**Global Static Variable**

- static variable declared outside of any class or function.
- global static variable has internal linkage, meaning it is accessible only within the file where it is defined. 
- This Also means you cant use extern to access the variable across folder.

🔢 C++ Lambda Expressions
---------------------------------------------

C++ 11 introduced lambda expressions to allow inline functions which can be used for short snippets of code that are not going to be reused. Therefore, they do not require a name.

**Syntax**

          [capture-clause] (parameters) -> return-type { 
              // definition
          }

**Example**

          #include <bits/stdc++.h>
          using namespace std;
          
          int main() {
              
              // Defining a lambda
              auto res = [](int x) {
                  return x + x;
              };
              cout << res(5);
              
              return 0;
          }

**Capture Clause**

A lambda expression can have more power than an ordinary function by having access to variables from the enclosing scope. We can capture external variables from the enclosing scope in three ways using capture clause:

- [&]: capture all external variables by reference.
- [=]: capture all external variables by value.
- [a, &b]: capture 'a' by value and 'b' by reference.

A lambda with an empty capture clause [] can only access variables which are local to it.

**Eaxmple2**

          #include <bits/stdc++.h>
          using namespace std;
          
          void print(vector<int> v) {
              for (auto x : v) cout << x << " ";
              cout << endl;
          }
          
          int main() {
              vector<int> v1, v2;
          
              // Capture v1 and v2 by reference
              auto byRef = [&] (int m) {
                  v1.push_back(m);
                  v2.push_back(m);
              };
              
              // Capture v1 and v2 by value
              auto byVal = [=] (int m) mutable {
                  v1.push_back(m);
                  v2.push_back(m);
              };
              
              // Capture v1 by reference and v2 by value
              auto mixed = [=, &v1] (int m) mutable {
                  v1.push_back(m);
                  v2.push_back(m);
              };
          
              // Push 20 in both v1 and v2
              byRef(20);
              
              // Push 234 in both v1 and v2
              byVal(234);
              
              // Push 10 in both v1 and v2
              mixed(10);
              
              print(v1);
              print(v2);
              
              return 0;
          }

**Examples**

Lamda expressions are extensively used in STL in place of callback i.e. functions passed as arguments. The below examples demonstrate that:

**Sort Vector in Descending Order**

          #include <bits/stdc++.h>
          using namespace std;
          
          int main() {
          	vector<int> v = {5, 1, 8, 3, 9, 2};
          
          	// Sort in descending order
                     //sort(v.begin,v,end,comparator)
          	sort(v.begin(), v.end(), [] (const int& a, const int&b) {
          		return a > b;
          	});
          
          	for (int x : v)
          		cout << x << " ";
          	return 0;
          }
Pointers & refernce
-------------------
- pointers and refrence both are mechanism used to deal with Memory.
- **pointers** are used to Store the memory Address of the variable wheras,
- **Reference** are used to Create an Alias(Alternative name) for an already existing variable.
- **Double pointers** are those pointers which store the Address of Another pointer.

| Pointers | Reference |
| -------- | -------- |
| a pointer can be declared as void | a reference can never be void |
| a pointer can be made to point to another | Once a refrence is created,it cannot be later made to refernce another object |
| a pointer are often made NULL | a refernce cannot be NULL |
| No restriction with pointers for init | A refernce must be initialized when declared |

Arrays pointers & Arthematic
----------------------------
- Arrays are Derived Data type that is used to store multiple values of similar data types in a contigous memory location.

<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230302091959/Arrays-in-C.png" alt="A sample image" width="280"/><img src="https://media.geeksforgeeks.org/wp-content/uploads/20230302092603/c-array-declaration.png" alt="A sample image" width="270"/>
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20250510151101341950/access-array-element.webp" alt="A sample image" width="250"/>
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230215172222/indexing_in_array.png" alt="A sample image" width="200"/>

- When a pointers is incremented,it actually increments by the number equal to the size of the data type for which it is a pointer.
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230424100855/Pointer-Increment-Decrement.webp" alt="A sample image" width="320"/>

          // CPP program to demonstrate the addition of a constant to a pointer
          #include <iostream>
          using namespace std;
          
          int main()
          {
          
              int n = 20;
              int* ptr = &n;
          
              cout << "Address stored in ptr: " << ptr << endl;
          
              // Adding the integer value 1 to the pointer ptr
              ptr = ptr + 1;
              cout << "Adding 1 to ptr: " << ptr << endl;
          
              // Adding the integer value 2 to the pointer ptr
              ptr = ptr + 2;
              cout << "Adding 2 to ptr: " << ptr;
          
              return 0;
          }

- When a pointers is added/subtracted with an integer value,the value is first multiplied by the size of the data type and then added to the pointer.

 <img src="https://media.geeksforgeeks.org/wp-content/uploads/20230424100935/Pointer-Addition.webp" alt="A sample image" width="320"/><img src="https://media.geeksforgeeks.org/wp-content/uploads/20230424101002/Pointer-Subtraction.webp" alt="A sample image" width="320"/> 

<img src="https://example.com/image.png" alt="A sample image" width="100"/>

**Strings in C++**

- strings are sequences of characters that are used to store words and text. They are also used to store data, such as numbers and other types of information in the form of text. Strings are provided by <string> header file in the form of std::string class.
- syntax
            string str_name;

**c++ strings v/s c strings**
  
| String | Character Array | 
| :--------- | :----------: |
| Strings define objects that can be represented as string streams. | The null character terminates a character array of characters. |
| No Array decay occurs in strings as strings are represented as objects.  | The threat of array decay(The loss of type and dimensions of an array ) is present in the case of the character array.    |
| A string class provides numerous functions for manipulating strings.  | Character arrays do not offer inbuilt functions to manipulate strings.    |
| Memory is allocated dynamically.  | The size of the character array has to be allocated statically.more memory cannot be allocated at run time if required. Unused allocated memory is also wasted     | 

**string Function & Example**



| Function Name | Description | Example |
| :------------ | :---------- | ------- |
| `length()` | This function returns the length of the string. | `std::string text = "geeksforGeeks"; int length = text.length();` |
| `swap()` | This function is used to swap the values of 2 strings. | `std::string str1 = "Hello", str2 = "World"; str1.swap(str2);` |
| `size()` | Used to find the size of string. | `std::string str = "Hello"; int sz = str.size();` |
| `resize()` | This function is used to resize the length of the string up to the given number of characters. | `std::string str = "HelloWorld"; str.resize(5);` |
| `find()` | Used to find the string which is passed in parameters. | `std::string str = "HelloWorld"; size_t pos = str.find("World");` |
| `push_back()` | This function is used to push the passed character at the end of the string. | `std::string str = "Hello"; str.push_back('!');` |
| `pop_back()` | This function is used to pop the last character from the string. | `std::string str = "Hello!"; str.pop_back();` |
| `clear()` | This function is used to remove all the elements of the string. | `std::string str = "Hello"; str.clear();` |
| `strncmp()` | This function compares at most the first num bytes of both passed strings. | `int result = strncmp("abc", "abd", 2);` |
| `strncpy()` | This function is similar to strcpy() function, except that at most n bytes of src are copied. | `char dest[10]; strncpy(dest, "Hello", 5);` |
| `strrchr()` | This function locates the last occurrence of a character in the string. | `char *ptr = strrchr("Hello World", 'o');` |
| `strcat()` | This function appends a copy of the source string to the end of the destination string. | `char str1[20] = "Hello "; strcat(str1, "World");` |
| `find()` | This function is used to search for a certain substring inside a string and returns the position of the first character of the substring. | `std::string str = "This is a test"; size_t found = str.find("test");` |
| `replace()` | This function is used to replace each element in the range [first, last) that is equal to old value with new value. | `std::string str = "I love apples"; str.replace(7, 6, "oranges");` |
| `substr()` | This function is used to create a substring from a given string. | `std::string str = "HelloWorld"; std::string sub = str.substr(0, 5);` |
| `compare()` | This function is used to compare two strings and returns the result in the form of an integer. | `std::string a = "abc", b = "abd"; int result = a.compare(b);` |
| `erase()` | This function is used to remove a certain part of a string. | `std::string str = "HelloWorld"; str.erase(5, 5);` |
| `rfind()` | This function is used to find the string's last occurrence. | `std::string str = "Hello World Hello"; size_t pos = str.rfind("Hello");` |

| Function Name | Problem Statement | Example |
| :------------ | :---------------- | ------- |
| `length()` | Validate user input length. | `#include <iostream>\n#include <string>\nint main() {\n  std::string input = "OpenAI";\n  if (input.length() > 5)\n    std::cout << "Too long\\n";\n  return 0;\n}` |
| `swap()` | Swap contents of two strings. | `#include <iostream>\n#include <string>\nint main() {\n  std::string a = "Hello", b = "World";\n  a.swap(b);\n  std::cout << a << " " << b;\n  return 0;\n}` |
| `size()` | Check if string meets size. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "Hello";\n  if (s.size() == 5)\n    std::cout << "Size 5\\n";\n  return 0;\n}` |
| `resize()` | Resize a string. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "HelloWorld";\n  s.resize(5);\n  std::cout << s;\n  return 0;\n}` |
| `find()` | Locate substring. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "Find the needle";\n  size_t pos = s.find("needle");\n  if (pos != std::string::npos)\n    std::cout << "Found at " << pos;\n  return 0;\n}` |
| `push_back()` | Add char to string. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "Hi";\n  s.push_back('!');\n  std::cout << s;\n  return 0;\n}` |
| `pop_back()` | Remove last char. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "Oops!";\n  s.pop_back();\n  std::cout << s;\n  return 0;\n}` |
| `clear()` | Clear string content. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "Reset me";\n  s.clear();\n  std::cout << "Length: " << s.length();\n  return 0;\n}` |
| `strncmp()` | Compare parts of strings. | `#include <iostream>\n#include <cstring>\nint main() {\n  const char* a = "abc";\n  const char* b = "abd";\n  if (strncmp(a, b, 2) == 0)\n    std::cout << "First 2 match";\n  return 0;\n}` |
| `strncpy()` | Copy n chars. | `#include <iostream>\n#include <cstring>\nint main() {\n  char src[] = "Hello";\n  char dest[10];\n  strncpy(dest, src, 5);\n  dest[5] = '\\0';\n  std::cout << dest;\n  return 0;\n}` |
| `strrchr()` | Find last char. | `#include <iostream>\n#include <cstring>\nint main() {\n  const char* path = "/usr/bin/g++";\n  const char* file = strrchr(path, '/');\n  if (file)\n    std::cout << "File: " << file+1;\n  return 0;\n}` |
| `strcat()` | Concatenate C-strings. | `#include <iostream>\n#include <cstring>\nint main() {\n  char s[20] = "Hi "; char t[] = "there";\n  strcat(s, t);\n  std::cout << s;\n  return 0;\n}` |
| `replace()` | Replace part of string. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "I like cats";\n  s.replace(7, 4, "dogs");\n  std::cout << s;\n  return 0;\n}` |
| `substr()` | Extract substring. | `#include <iostream>\n#include <string>\nint main() {\n  std::string date = "2025-05-23";\n  std::string year = date.substr(0, 4);\n  std::cout << year;\n  return 0;\n}` |
| `compare()` | Compare two strings. | `#include <iostream>\n#include <string>\nint main() {\n  std::string a = "abc", b = "abd";\n  if (a.compare(b) < 0)\n    std::cout << "abc < abd";\n  return 0;\n}` |
| `erase()` | Remove substring. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "Hello, World!";\n  s.erase(5, 7);\n  std::cout << s;\n  return 0;\n}` |
| `rfind()` | Last substring match. | `#include <iostream>\n#include <string>\nint main() {\n  std::string s = "one fish two fish";\n  size_t pos = s.rfind("fish");\n  std::cout << pos;\n  return 0;\n}` |



---
Sure! To keep the table neat and renderable **without code inside the table cells**, we put only problem info and sample input/output in the table, and then place the full code snippets **below the table**, each clearly numbered and titled. This way the Markdown renders perfectly everywhere.

Here’s the full markdown content for you:

---

````markdown
# 10 Must-Know Competitive Programming String Problems

| #  | Problem Title                  | Description                                             | Sample Input/Output & Explanation                                     |
|----|-------------------------------|---------------------------------------------------------|------------------------------------------------------------------------|
| 1  | Reverse a String               | Reverse the characters in a string.                     | Input: 'OpenAI' <br> Output: 'IAnepO' <br> Explanation: Reverse each character. |
| 2  | Check for Palindrome           | Check if a string reads the same backward.              | Input: 'madam' <br> Output: 'Yes' <br> Explanation: 'madam' is the same reversed. |
| 3  | Anagram Check                  | Check if two strings are anagrams of each other.        | Input: 'listen', 'silent' <br> Output: 'Anagram' <br> Explanation: Same letters in different order. |
| 4  | Remove Duplicates              | Remove duplicate characters from a string.              | Input: 'programming' <br> Output: 'progamin' <br> Explanation: Remove repeated chars, keep first appearance. |
| 5  | Longest Common Prefix          | Find the longest prefix common to all strings in array. | Input: ['flower', 'flow', 'flight'] <br> Output: 'fl' <br> Explanation: All words start with 'fl'. |
| 6  | Longest Palindromic Substring  | Find the longest palindrome substring.                  | Input: 'babad' <br> Output: 'bab' or 'aba' <br> Explanation: Both are valid palindromes of max length. |
| 7  | String Compression             | Compress consecutive repeating characters.              | Input: 'aabcccccaaa' <br> Output: 'a2b1c5a3' <br> Explanation: Replace sequences with character + count. |
| 8  | Substring Search (KMP)         | Check if pattern exists in text using KMP algorithm.    | Input: Text='abxabcabcaby', Pattern='abcaby' <br> Output: 'Found' <br> Explanation: Pattern found at index 6. |
| 9  | Remove All Adjacent Duplicates | Remove adjacent duplicates in one pass.                 | Input: 'abbaca' <br> Output: 'ca' <br> Explanation: Remove 'bb', then 'aa' leaves 'ca'. |
| 10 | Valid Parentheses              | Check for valid and balanced parentheses.               | Input: '{[()]}' <br> Output: 'Valid' <br> Explanation: All brackets closed in correct order. |

---

## 1. Reverse a String

Reverse the characters in a string.

```cpp
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string input = "OpenAI";
    std::reverse(input.begin(), input.end());
    std::cout << input << std::endl; // Output: IAnepO
    return 0;
}
````

---

## 2. Check for Palindrome

Check if a string reads the same backward.

```cpp
#include <iostream>
#include <string>

bool isPalindrome(const std::string& s) {
    int left = 0, right = s.size() - 1;
    while(left < right) {
        if(s[left] != s[right]) return false;
        left++; right--;
    }
    return true;
}

int main() {
    std::string s = "madam";
    if (isPalindrome(s))
        std::cout << "Yes\n"; // Output: Yes
    else
        std::cout << "No\n";
    return 0;
}
```

---

## 3. Anagram Check

Check if two strings are anagrams of each other.

```cpp
#include <iostream>
#include <string>
#include <algorithm>

bool areAnagrams(std::string s1, std::string s2) {
    if (s1.size() != s2.size()) return false;
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    return s1 == s2;
}

int main() {
    std::string a = "listen", b = "silent";
    if (areAnagrams(a, b))
        std::cout << "Anagram\n"; // Output: Anagram
    else
        std::cout << "Not Anagram\n";
    return 0;
}
```

---

## 4. Remove Duplicates

Remove duplicate characters from a string, keeping first appearances.

```cpp
#include <iostream>
#include <string>
#include <unordered_set>

std::string removeDuplicates(const std::string& s) {
    std::unordered_set<char> seen;
    std::string result;
    for (char c : s) {
        if (seen.find(c) == seen.end()) {
            result.push_back(c);
            seen.insert(c);
        }
    }
    return result;
}

int main() {
    std::string s = "programming";
    std::cout << removeDuplicates(s) << std::endl; // Output: progamin
    return 0;
}
```

---

## 5. Longest Common Prefix

Find the longest prefix common to all strings in an array.

```cpp
#include <iostream>
#include <vector>
#include <string>

std::string longestCommonPrefix(const std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    std::string prefix = strs[0];
    for (int i = 1; i < strs.size(); ++i) {
        while (strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.size() - 1);
            if (prefix.empty()) return "";
        }
    }
    return prefix;
}

int main() {
    std::vector<std::string> words = {"flower", "flow", "flight"};
    std::cout << longestCommonPrefix(words) << std::endl; // Output: fl
    return 0;
}
```

---

## 6. Longest Palindromic Substring

Find the longest palindrome substring.

```cpp
#include <iostream>
#include <string>

int expandAroundCenter(const std::string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

std::string longestPalindrome(const std::string& s) {
    if (s.empty()) return "";
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); i++) {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int len = std::max(len1, len2);
        if (len > end - start) {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }
    return s.substr(start, end - start + 1);
}

int main() {
    std::string s = "babad";
    std::cout << longestPalindrome(s) << std::endl; // Output: bab or aba
    return 0;
}
```

---

## 7. String Compression

Compress consecutive repeating characters.

```cpp
#include <iostream>
#include <string>

std::string compressString(const std::string& s) {
    std::string result;
    int count = 1;
    for (int i = 1; i <= s.size(); i++) {
        if (i < s.size() && s[i] == s[i - 1]) {
            count++;
        } else {
            result += s[i - 1];
            result += std::to_string(count);
            count = 1;
        }
    }
    return result;
}

int main() {
    std::string s = "aabcccccaaa";
    std::cout << compressString(s) << std::endl; // Output: a2b1c5a3
    return 0;
}
```

---

## 8. Substring Search (KMP Algorithm)

Check if pattern exists in text using KMP algorithm.

```cpp
#include <iostream>
#include <vector>
#include <string>

std::vector<int> computeLPS(const std::string& pattern) {
    int length = 0;
    std::vector<int> lps(pattern.size(), 0);
    int i = 1;
    while (i < pattern.size()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

bool KMPSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> lps = computeLPS(pattern);
    int i = 0, j = 0;
    while (i < text.size()) {
        if (pattern[j] == text[i]) {
            i++; j++;
        }
        if (j == pattern.size()) {
            return true; // Found at index i - j
        } else if (i < text.size() && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false;
}

int main() {
    std::string text = "abxabcabcaby";
    std::string pattern = "abcaby";
    if (KMPSearch(text, pattern))
        std::cout << "Found\n"; // Output: Found
    else
        std::cout << "Not Found\n";
    return 0;
}
```


````

---

## 9. Remove All Adjacent Duplicates

Remove adjacent duplicates in one pass.

```cpp
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

std::string removeAdjacentDuplicates(const std::string& s) {
    std::stack<char> st;
    for (char c : s) {
        if (!st.empty() && st.top() == c) {
            st.pop(); // Remove duplicate
        } else {
            st.push(c);
        }
    }
    std::string result;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string s = "abbaca";
    std::cout << removeAdjacentDuplicates(s) << std::endl; // Output: ca
    return 0;
}
````

---

## 10. Valid Parentheses

Check for valid and balanced parentheses.

```cpp
#include <iostream>
#include <stack>
#include <string>

bool isValidParentheses(const std::string& s) {
    std::stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '['))
                return false;
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    std::string s = "{[()]}";
    if (isValidParentheses(s))
        std::cout << "Valid\n"; // Output: Valid
    else
        std::cout << "Invalid\n";
    return 0;
}
```

---




--------------------------
C++
C++ Classes and Objects
C++ Polymorphism
C++ Inheritance
C++ Abstraction
C++ Encapsulation
C++ OOPs Interview Questions
C++ OOPs MCQ
C++ Interview Questions
C++ Function Overloading
C++ Programs
C++ Preprocessor
C++ Templates


````markdown
# C++ Classes and Objects

Classes and objects are the basic building blocks that lead to Object-Oriented Programming in C++.

---

## C++ Classes

A *class* is a user-defined data type which holds its own **data members** and **member functions**.
These members can be accessed and used by creating an instance (object) of that class.
A C++ class acts like a blueprint for objects.

### Example

Consider a **Class of Cars**. There may be many cars with different names and brands,
but all of them share some common properties like:

- All have 4 wheels
- Speed limit
- Mileage range

The car can also perform actions like:

- Accelerate
- Turn
- Apply brakes

Here:
- **Car** is the class.
- Wheels, speed limits, and mileage are its **attributes (data members)**.
- Accelerate, turn, apply brakes are its **methods (member functions)**.

---

## Create a Class

A class must be defined before it is used.  
Syntax:

```cpp
class className {
  access_specifier:
    // data members
    // member functions
};
````

* **Data Members:** Variables defined inside the class.
* **Member Functions:** Functions declared inside the class (also called member methods).

### Example:

```cpp
class GfG {
public:
    // Data member
    int val;

    // Member function
    void show() {
        cout << "Value: " << val << endl;
    }
};
```

In this example, the `GfG` class has:

* a data member `val`
* a member function `show()` which prints the value of `val`.

> Note: Member functions can be defined inside the class or declared inside and defined outside the class using the scope resolution operator `::`.

This is called a **class definition** or **template**.

---

## C++ Objects

When a class is defined, only the specification (attributes and behavior) is set.
**No memory is allocated** to the class itself until an object is created.

* Objects are instances of a class.
* You can create many objects of a class.

### Example:

If `Car` is a class, then an actual car made based on this class is an **object** of the `Car` class.

---

## Create Object

After the class is defined, objects are created similarly to variables of built-in types.

```cpp
className objectName;
```

This statement creates an object of the `className` class.

---



Got it! Here's the markdown-formatted version of your explanation about **Member Access** and **Access Modifiers** in C++, including the example and a placeholder for the explanation section for you to fill in:

````markdown
# Member Access and Access Modifiers in C++

---

## Member Access

- Members of a class can be accessed **inside the class** simply by using their names.
- To access members **outside the class**, use the **dot operator (.)** with the object of the class.

```cpp
obj.member1      // For data members
obj.member2(...) // For member functions
````

Where:

* `obj` is the name of the object
* `member1` is a data member
* `member2` is a member function

---

## Access Modifiers

Access specifiers (or access modifiers) control the access level of class members. They are keywords specified inside the class to set the accessibility of all members declared under them.

There are **3 access specifiers** in C++:

| Access Specifier | Access Level Description                                         |
| ---------------- | ---------------------------------------------------------------- |
| **public**       | Members can be accessed from outside the class.                  |
| **private**      | Members can only be accessed within the class itself.            |
| **protected**    | Members can be accessed within the class and by derived classes. |

> **Note:**
> If no access specifier is mentioned, members are **private** by default.

---

## Example

```cpp
#include <bits/stdc++.h>
using namespace std;

// Creating a class
class GfG {
public:
    // Data member
    int val;

    // Member function
    void show() {
        cout << "Value: " << val << endl;
    }
};

int main() {
    // Create Object
    GfG obj;

    // Access data member and assign it a value
    obj.val = 10;

    // Access member function
    obj.show();

    return 0;
}
```

### Output

```
Value: 10
```
---

## Explanation

Whether we can access a member of a class depends on the access specifier under which it is declared.
In the above example, the variable `val` is declared as **public**, so it can be accessed and modified directly through the object `obj` in `main()`. If `val` were declared **private**, then `obj.val = 10;` would cause a compilation error because private members cannot be accessed outside the class.



Sure! Here's a well-formatted Markdown version of your explanation on **Special Member Functions in C++ classes**, with proper code blocks and headings for clarity.

---

# Special Member Functions in C++ Classes

In C++, some **special member functions** are essential to manage objects and provide basic functionalities.

---

## Constructor

Constructors are special class members called automatically by the compiler whenever an object of the class is instantiated. They prepare the object for use and have the **same name as the class**.

### Example:

```cpp
#include <bits/stdc++.h>
using namespace std;

class MyClass {
public:
    // Constructor
    MyClass() {
        cout << "Constructor called!";
    }
};

int main() {
    // Constructor automatically called when object is created
    MyClass obj;
    return 0;
}
```

---

## Destructor

A destructor is called by the compiler when the scope of the object ends. It deallocates memory used by the object to prevent memory leaks. It has the **same name as the class**, prefixed by a tilde `~`.

### Example:

```cpp
#include <bits/stdc++.h>
using namespace std;

class MyClass {
public:
    MyClass() {
        cout << "Constructor called!" << endl;
    }

    // Destructor
    ~MyClass() {
        cout << "Destructor called!";
    }
};

int main() {
    MyClass obj;  // Destructor called automatically when obj goes out of scope
    return 0;
}
```

---

## Static Members

Static members belong to the class itself rather than any particular object. They can be accessed without creating an object.

### Static Data Members

Shared by all objects, only one copy exists for all instances.

```cpp
#include <iostream>
using namespace std;

class GfG {
public:
    static int val;
};

// Initialize static member
int GfG::val = 22;

int main() {
    // Access without creating object
    cout << GfG::val << endl;  // Output: 22
    return 0;
}
```

### Static Member Functions

Static member functions can only access static data members and are called using the class name.

```cpp
#include <iostream>
using namespace std;

class GfG {
public:
    static void printHello();
};

// Definition of static member function
void GfG::printHello() {
    cout << "Hello World";
}

int main() {
    // Call static member function without creating object
    GfG::printHello();  // Output: Hello World
    return 0;
}
```

---

## Friend Class and Friend Function

* **Friend Class:** Can access private and protected members of another class if declared as a friend.
* **Friend Function:** Not a member of the class but granted access to private and protected members.

This is useful for close cooperation between classes or functions.

---

## Local Class

A class defined **inside a function** is called a local class and can only be accessed within that function.

---

## Nested Class

A **nested class** is defined inside another class. It behaves like any other member of the enclosing class but does not grant special access back to the enclosing class.

---

## Enum Class

Enum classes provide a **safer and more organized** way to group related constants, preventing naming conflicts and improving type safety.

---

## `this` Pointer

`this` is a pointer available inside all non-static member functions that points to the current instance of the class.

### Example:

```cpp
class A {
    int n;
public:
    A(int n) {
        this->n = n;
    }
};
```

---

If you want me to save or share this in a file, just let me know!

Class vs Object

The following table lists the primary differences between the classes and objects in C++:

✅ 1. Types of Operators in C++
-------------------------------
          Category	        Operators	                   Description
          -----------------------------------------------------------------------
          Arithmetic	+, -, *, /, %	          Basic math operations
          Relational	==, !=, <, >, <=, >=	Comparison (true/false)
          Logical	          &&, `	
          Assignment	=, +=, -=, *=, /=, %=	Assign values
          Increment/Decrement	++, --	                    Increase or decrease value by 1
          Bitwise	          &, `	                    , ^, ~, <<, >>`
          Ternary	          ? :	                    Shortcut for if-else
          Comma	          ,	                    Evaluate multiple expressions
          Sizeof	          sizeof()	                    Returns size of type/variable

🧠 2. Operator Examples and Behavior
-------------------------------------
➕ Arithmetic Operators
-----------------------
          int a = 10, b = 3;
          cout << a + b;  // 13
          cout << a - b;  // 7
          cout << a * b;  // 30
          cout << a / b;  // 3 (integer division)
          cout << a % b;  // 1 (modulo)
          ⚠️ Note: a / b when both are integers does integer division. Use float for accurate decimals.

🧾 Assignment and Compound Operators
------------------------------------
          int x = 5;
          x += 3;   // x = x + 3 → 8
          x *= 2;   // x = x * 2 → 16

🧮 Increment and Decrement
--------------------------
          int a = 5;
          ++a;  // pre-increment: a becomes 6
          a++;  // post-increment: a used first, then becomes 7
🔁 Relational and Logical Operators
-----------------------------------
          int a = 5, b = 10;
          cout << (a < b);       // 1 (true)
          cout << (a == b);      // 0 (false)
          cout << (a != b);      // 1 (true)
          
          bool result = (a < b) && (b < 20);  // true
❓ Ternary Operator
-------------------
          int age = 18;
          string status = (age >= 18) ? "Adult" : "Minor";
          cout << status;
          This is a shortcut for:
          
          cpp
          Copy
          Edit
          if (age >= 18)
              status = "Adult";
          else
              status = "Minor";
📏 Sizeof Operator
------------------
          cout << sizeof(int);     // typically 4
          cout << sizeof(double);  // typically 8
🧠 3. Expressions in C++
------------------------
An expression could be:

          int a = 5 + 2;      // arithmetic expression
          bool b = (a > 3);   // logical expression
          a += 10;            // assignment expression
🔥 4. Operator Precedence and Associativity
-------------------------------------------

Operator precedence determines the order in which expressions are evaluated.

Example:
          int result = 5 + 3 * 2;  // 3 * 2 = 6, then 5 + 6 = 11
          
🧠 Multiplication has higher precedence than addition.
------------------------------------------------------
Parentheses () can override default precedence.

🧪 Mini Practice Task
---------------------
Write a program that:

          - Takes two integers as input.
          Displays:
          -Their sum, product, and quotient.
          - Which one is greater (using if or ternary).
          - Whether the first is divisible by the second.
🔁 Control Flow Statements in C++
---------------------------------
These statements allow your program to make decisions and repeat tasks.

✅ 1. Conditional Statements
----------------------------
These are used to execute different code blocks based on conditions.
          
          🔹 if / else if / else
          int age = 20;
          
          if (age < 18) {
              cout << "Minor";
          } else if (age == 18) {
              cout << "Exactly 18!";
          } else {
              cout << "Adult";
          }
✔️ Use else if when you have multiple conditions.
✔️ Conditions must be inside (), and code blocks inside {}.

          🔹 Nested if
          if (x > 0) {
              if (x < 10) {
                  cout << "Single-digit positive number";
              }
          }
🔸 Avoid deeply nested if statements when possible (use else if or switch).

🔹 Ternary Operator (Shortcut)
          string result = (score >= 50) ? "Pass" : "Fail";
          
✅ 2. switch Statement
----------------------
Useful for checking a variable against multiple constant values (integers or chars).

          int day = 3;
          
          switch (day) {
              case 1: cout << "Monday"; break;
              case 2: cout << "Tuesday"; break;
              case 3: cout << "Wednesday"; break;
              default: cout << "Invalid day";
          }
⚠️ Always include break; to prevent "fall-through"
✔️ default is optional but recommended as a fallback

✅ 3. Looping Statements
-------------------------
Used to repeat a block of code.

🔁 for Loop (when number of iterations is known)
-----------------------------------------------
          for (int i = 0; i < 5; i++) {
              cout << "i = " << i << '\n';
          }
🔁 while Loop (when condition is checked before each iteration)
--------------------------------------------------------------
          int i = 0;
          while (i < 5) {
              cout << i << '\n';
              i++;
          }
🔁 do-while Loop (runs at least once)
-------------------------------------
          int i = 0;
          do {
              cout << i << '\n';
              i++;
          } while (i < 5);
🔁 Break and Continue
---------------------
break: exits the loop early

continue: skips current iteration

          for (int i = 1; i <= 5; i++) {
              if (i == 3) continue;
              if (i == 5) break;
              cout << i << ' ';
          }  // Output: 1 2 4
🧠 Interview Tip
-----------------
You’ll often use these in:
          
          - Pattern printing
          - Searching/sorting
          - State machines
          - Menu-driven programs

🧪 Mini Practice Task
----------------------
Write a menu-driven program that:

          Asks user for 2 integers
          
          Shows a menu:
          
          markdown
          Copy
          Edit
          1. Add
          2. Subtract
          3. Multiply
          4. Divide
          5. Exit
          Executes the selected operation using switch

Loops until user chooses Exit


## Basic String I/O in C++

### 1. `cin >>` vs. `getline`

- **`cin >> str;`**  
  - Reads a single “word” (up to the first whitespace).
  - Stops at space, tab, or newline.
- **`std::getline(cin, line);`**  
  - Reads an entire line (including spaces) up to the newline character.
  - Useful when your input may contain spaces.

---

# C++ Basic Input/Output – `cin` / `cout`

Source: [Take U Forward - Basic I/O](https://takeuforward.org/c/c-basic-input-output/)

## 📘 Objective

Understand the basic input and output mechanisms in C++ using:
- `cin` – for input
- `cout` – for output

These are part of the `<iostream>` library.

---

## 📥 Input in C++

### 🔹 Syntax

```cpp
#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    return 0;
}
```
cin stands for “character input”.

The >> operator extracts the value from the input buffer and assigns it to the variable.

📝 **Example**: Input Two Integers
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << "The numbers are " << a << " and " << b << endl;
    return 0;
}
```
💡 You can chain inputs like cin >> a >> b.

📤 **Output in C++**
🔹 Syntax
```cpp
cout << "Text to print";
cout stands for “character output”.
```
The << operator sends data to the output stream.

📝 **Example**: Print a Variable
```cpp
int x = 5;
cout << "Value of x is: " << x << endl;
```
endl is used to move the output to the next line.

🔄 **Example**: Full I/O Program
```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    string name;

    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter your age: ";
    cin >> age;

    cout << "Name: " << name << ", Age: " << age << endl;

    return 0;
}
```
⚠️ **Note**: cin >> name only reads up to the first space. To input full names with spaces, use getline().

🧠 **Bonus**: getline() for Strings with Spaces
```cpp
#include <iostream>
using namespace std;

int main() {
    string fullName;
    getline(cin, fullName);
    cout << "Hello, " << fullName << "!" << endl;
    return 0;
}
```
**getline(cin, fullName)** reads the entire line including spaces until the newline character.

# 🧩 General Strategy to Solve Any Pattern Problem in C++

Understanding pattern-based questions is key to mastering loops, especially nested loops in C++.

---

## 🪜 Step 1: Understand the Pattern Visually

Look at:

- Total number of **rows** = `n`
- What is printed in **each row**?
- How many **columns per row**?
- Is the pattern **symmetric**?
- Is it **increasing or decreasing**?

---

## 🧮 Step 2: Find Relationships Between Row and Column

Ask:

- For each `i` (row number from 1 to `n`), how many items are printed?
- What values are printed in those items?
- Are they numbers, stars `*`, or letters?
- Any **spaces** or **indents**?

---

## 🔁 Step 3: Setup the Outer and Inner Loops

```cpp
for (int i = 1; i <= n; i++) {         // Outer loop → rows
    for (int j = 1; j <= ???; j++) {   // Inner loop → columns/items
        // logic to print correct item
    }
    cout << endl; // New line after each row
}
```
# 🧮 Deriving Loops in Pattern Problems

---

## 🔁 Loop Variables: Usually

- `i` = row number (outer loop)
- `j` = column index inside that row (inner loop)

---

## 📐 Common Patterns and Loop Formulas

| Pattern Type            | Outer Loop (Rows) | Inner Loop (Columns)                      | Tips                       |
|-------------------------|-------------------|-------------------------------------------|----------------------------|
| Left-aligned triangle   | `i = 1 to n`       | `j = 1 to i`                               | `j` depends on `i`         |
| Right-aligned triangle  | `i = 1 to n`       | Print spaces `n - i`, then stars `i`       | Use two inner loops        |
| Inverted triangle       | `i = 1 to n`       | `j = 1 to n - i + 1`                       | Count decreases            |
| Pyramid / Diamond       | `i = 1 to n`       | Spaces: `n - i`, Stars: `2i - 1`           | Symmetric patterns         |
| Number patterns         | `i = 1 to n`       | Print `j`, `i`, or `j = n - i + 1`         | Use logic for values       |

---

## 🔍 Let's See Some Examples

---

# 🧩 Pattern Problems: Loop Formula Guide for Striver's 21 Patterns

Based on: [Striver's A2Z DSA Pattern List](https://takeuforward.org/strivers-a2z-dsa-course/must-do-pattern-problems-before-starting-dsa/)

---

## 📐 General Loop Strategies

| Pattern Type            | Outer Loop (Rows)  | Inner Loop (Columns)                     | Tips                         |   |      |   |            |
| ----------------------- | ------------------ | ---------------------------------------- | ---------------------------- | - | ---- | - | ---------- |
| Left-aligned triangle   | `i = 1 to n`       | `j = 1 to i`                             | `j` depends on `i`           |   |      |   |            |
| Right-aligned triangle  | `i = 1 to n`       | Spaces: `n - i`, Stars: `i`              | Use two inner loops          |   |      |   |            |
| Inverted triangle       | `i = 1 to n`       | `j = 1 to n - i + 1`                     | Count decreases              |   |      |   |            |
| Pyramid / Diamond       | `i = 1 to n`       | Spaces: `n - i`, Stars: `2i - 1`         | Symmetric pattern            |   |      |   |            |
| Number patterns         | `i = 1 to n`       | Print `j`, `i`, or `j = n - i + 1`       | Use logic for value printing |   |      |   |            |
| Binary triangle         | `i = 1 to n`       | Print based on `(i + j) % 2`             | Alternate 1s and 0s          |   |      |   |            |
| Mirror/Reverse patterns | `i = 1 to n`       | Use `n - i` or reverse logic             | Flip direction or values     |   |      |   |            |
| Combined shapes         | `i = 1 to 2*n - 1` | Adjust inner loop using `min(i, 2n - i)` | Use min/max logic            |   |      |   |            |
| Hollow patterns         | `i = 1 to n`       | Print only edges or boundaries           | Use \`if (i==1               |   | i==n |   | j==1...)\` |

---

## ✅ Loop Formulas for All 21 Patterns

### 1. Left-Aligned Triangle

```
*  
* *  
* * *  
* * * *  
* * * * *
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to i`
* Print: `* `

---

### 2. Right-Aligned Triangle

```
    *
   * *
  * * *
 * * * *
* * * * *
```

* Outer: `i = 1 to n`
* Inner1: `j = 1 to n - i` → print spaces
* Inner2: `j = 1 to i` → print stars

---

### 3. Inverted Left-Aligned Triangle

```
* * * * *
* * * *
* * *
* *
*
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to n - i + 1`

---

### 4. Inverted Right-Aligned Triangle

```
* * * * *
 * * * *
  * * *
   * *
    *
```

* Outer: `i = 1 to n`
* Inner1: `j = 1 to i - 1` → spaces
* Inner2: `j = 1 to n - i + 1` → stars

---

### 5. Pyramid (Centered Triangle)

```
    *
   ***
  *****
 *******
*********
```

* Outer: `i = 1 to n`
* Inner1: `j = 1 to n - i` → spaces
* Inner2: `j = 1 to 2*i - 1` → stars

---

### 6. Inverted Pyramid

```
*********
 *******
  *****
   ***
    *
```

* Outer: `i = 1 to n`
* Inner1: `j = 1 to i - 1` → spaces
* Inner2: `j = 1 to 2*(n - i) + 1` → stars

---

### 7. Diamond

```
    *
   ***
  *****
   ***
    *
```

* Outer: `i = 1 to 2n - 1`
* Use: `stars = i <= n ? 2*i-1 : 2*(2n - i)-1`
* Spaces: `abs(n - i)`

---

### 8. Half Diamond

```
*
* *
* * *
* *
*
```

* Outer: `i = 1 to 2n - 1`
* Stars: `i <= n ? i : 2n - i`

---

### 9. Number Triangle

```
1
1 2
1 2 3
1 2 3 4
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to i` → print `j`

---

### 10. Repeated Row Number

```
1
2 2
3 3 3
4 4 4 4
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to i` → print `i`

---

### 11. Increasing Triangle Numbers

```
1
2 3
4 5 6
7 8 9 10
```

* Use counter `num = 1`
* Outer: `i = 1 to n`
* Inner: `j = 1 to i` → print `num++`

---

### 12. Binary Triangle

```
1
0 1
1 0 1
0 1 0 1
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to i` → print `(i + j) % 2`

---

### 13. Square Border (Hollow)

```
*****
*   *
*   *
*****
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to n`
* Print `*` if `i==1 || i==n || j==1 || j==n` else space

---

### 14. Right-Angle Triangle Numbers (Reverse)

```
1 2 3
1 2
1
```

* Outer: `i = n to 1`
* Inner: `j = 1 to i` → print `j`

---

### 15. Alphabet Triangle

```
A
A B
A B C
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to i` → print `char('A' + j - 1)`

---

### 16. Repeated Alphabets by Row

```
A
B B
C C C
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to i` → print `char('A' + i - 1)`

---

### 17. Alphabet Pyramid

```
    A
   ABA
  ABCBA
 ABCDCBA
```

* Outer: `i = 1 to n`
* Inner1: `j = 1 to n - i` → spaces
* Inner2: `j = 1 to i` → increasing chars
* Inner3: `j = i-1 to 1` → decreasing chars

---

### 18. Symmetric Triangle with Numbers

```
1
2 3
4 5 6
7 8 9 10
```

* Use `num = 1`
* Outer: `i = 1 to n`
* Inner: `j = 1 to i` → print `num++`

---

### 19. Reverse Pyramid of Numbers

```
1 2 3 4 5
1 2 3 4
1 2 3
1 2
1
```

* Outer: `i = 1 to n`
* Inner: `j = 1 to n - i + 1`

---

### 20. Alphabet Diamond

```
    A
   ABA
  ABCBA
   ABA
    A
```

* Outer: `i = 1 to 2n - 1`
* Use: `len = i <= n ? i : 2n - i`
* Inner: same as alphabet pyramid

---

### 21. Number Mirror Diamond

```
1
2 1
3 2 1
2 1
1
```

* Outer: `i = 1 to 2n - 1`
* Inner: `j = min(i, 2n - i) to 1` → print `j`

---
# 📘 C++ STL `unordered_set` – Explained with Examples

The `unordered_set` is a container that stores **unique elements** in **no particular order**, and provides **average constant time complexity (O(1))** for insertion, deletion, and lookup using hashing.

---

## 🧠 Key Characteristics

* Stores **only unique elements**.
* Elements are **not stored in any sorted order**.
* **Hash Table** is used internally.
* **Faster** than `set` (which uses BST) in average case.

---

## 📚 Syntax

```cpp
#include <unordered_set>
std::unordered_set<int> uset;
```

---

## ⚙️ Commonly Used Functions

| Function            | Description                                         |
| ------------------- | --------------------------------------------------- |
| `insert(val)`       | Inserts an element into the set                     |
| `find(val)`         | Returns iterator to element or `end()` if not found |
| `erase(val)`        | Deletes element if present                          |
| `count(val)`        | Returns 1 if element is present, else 0             |
| `size()`            | Returns the number of elements                      |
| `empty()`           | Checks if the set is empty                          |
| `clear()`           | Removes all elements                                |
| `begin()` / `end()` | Iterators for traversal                             |

---

## 🧪 Example: All Functions in Action

```cpp
#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> uset;

    // Inserting elements
    uset.insert(10);
    uset.insert(20);
    uset.insert(30);
    uset.insert(20); // duplicate, will not be inserted

    // Size
    cout << "Size: " << uset.size() << endl;

    // Checking if element exists
    if (uset.find(20) != uset.end())
        cout << "20 is present" << endl;
    else
        cout << "20 not found" << endl;

    // Erasing an element
    uset.erase(20);
    cout << "After erasing 20, size: " << uset.size() << endl;

    // Using count
    cout << "Count of 30: " << uset.count(30) << endl;
    cout << "Count of 40: " << uset.count(40) << endl;

    // Traversing
    cout << "Elements: ";
    for (auto val : uset) cout << val << " ";
    cout << endl;

    // Empty check
    cout << "Is set empty? " << (uset.empty() ? "Yes" : "No") << endl;

    // Clear all elements
    uset.clear();
    cout << "Set cleared. Is it empty now? " << (uset.empty() ? "Yes" : "No") << endl;

    return 0;
}
```

---

## ⚖️ `set` vs `unordered_set`

| Feature         | `set`          | `unordered_set` |
| --------------- | -------------- | --------------- |
| Internals       | Red-Black Tree | Hash Table      |
| Order           | Sorted         | No Order        |
| Time Complexity | O(log n)       | O(1) avg        |
| Duplicates      | ❌              | ❌               |

---

## 📌 Notes

* **No duplicates allowed**.
* Useful for **quick membership testing**.
* **Order is unpredictable** due to hashing.
* Avoid using `unordered_set` with complex keys unless a custom hash function is provided.

---

### ✅ Best Use Cases

* Membership lookup
* Removing duplicates from a list
* Unique word or number counting

---

> 🔁 Prefer `unordered_set` when you need **fast access** and **don’t care about order**.
# 📦 C++ STL Vector

The `vector` in C++ STL is a dynamic array that can grow and shrink in size. It provides the ability to use arrays with the power of object-oriented programming.

---

## 🧠 Why Use Vectors?

* Dynamic resizing
* Random access (like arrays)
* Predefined useful functions

---

## Declaration & Initialization

```cpp
#include <vector>
using namespace std;

// Empty vector of ints
vector<int> v1;

// Vector with initial size 5 (all values = 0)
vector<int> v2(5);

// Vector with size 5 and all values initialized to 10
vector<int> v3(5, 10);

// Initialize from array
int arr[] = {1, 2, 3};
vector<int> v4(arr, arr + 3);

// Copy another vector
vector<int> v5(v3);

// Using initializer list
vector<int> v6 = {1, 2, 3, 4};
```

---

## � Common Functions with Examples

### 1. `push_back()` – Add at end

```cpp
v1.push_back(10);
v1.push_back(20); // v1 = {10, 20}
```

### 2. `emplace_back()` – More efficient insertion

```cpp
v1.emplace_back(30); // v1 = {10, 20, 30}
```

### 3. `size()` – Number of elements

```cpp
cout << v1.size(); // 3
```

### 4. `pop_back()` – Remove last element

```cpp
v1.pop_back(); // v1 = {10, 20}
```

### 5. `front()` and `back()`

```cpp
cout << v1.front(); // 10
cout << v1.back();  // 20
```

### 6. `clear()` – Removes all elements

```cpp
v1.clear(); // v1 is now empty
```

### 7. `empty()` – Check if vector is empty

```cpp
if (v1.empty()) cout << "Empty!";
```

### 8. `at(index)` – Safe access

```cpp
v3.at(2); // 10
```

---

## � Iterating Through a Vector

### 1. Index-based

```cpp
for (int i = 0; i < v3.size(); i++) cout << v3[i] << " ";
```

### 2. Range-based loop

```cpp
for (int val : v3) cout << val << " ";
```

### 3. Using iterators

```cpp
for (vector<int>::iterator it = v3.begin(); it != v3.end(); ++it) cout << *it << " ";
```

### 4. Auto keyword with iterators

```cpp
for (auto it = v3.begin(); it != v3.end(); ++it) cout << *it << " ";
```

---

## � Other Useful Functions

### `insert()` – Insert at specific position

```cpp
v3.insert(v3.begin() + 1, 99); // Insert 99 at index 1
```

### `erase()` – Remove specific element or range

```cpp
v3.erase(v3.begin() + 1); // Erase element at index 1
```

### `swap()` – Exchange contents

```cpp
v3.swap(v4);
```

---

## Sample Program

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums;

    nums.push_back(1);
    nums.emplace_back(2);
    nums.push_back(3);

    for (auto x : nums) cout << x << " ";
    cout << "\nSize: " << nums.size();

    nums.pop_back();
    cout << "\nLast Element: " << nums.back();

    return 0;
}
```
---

## 🔂 Common Functions with Examples

### 1. `push_back()` – Add an element to the end

```cpp
vector<int> v;
v.push_back(10);
v.push_back(20); // v = [10, 20]
```

### 2. `pop_back()` – Remove last element

```cpp
v.pop_back(); // v = [10]
```

### 3. `size()` – Get current size

```cpp
cout << v.size(); // 1
```

### 4. `capacity()` – Current capacity of internal array

```cpp
cout << v.capacity();
```

### 5. `begin()` and `end()` – Iterators

```cpp
for (auto it = v.begin(); it != v.end(); it++)
    cout << *it << " ";
```

### 6. `clear()` – Remove all elements

```cpp
v.clear();
```

### 7. `empty()` – Check if vector is empty

```cpp
cout << v.empty(); // 1 (true)
```

### 8. `at(index)` – Access with bounds checking

```cpp
cout << v.at(0); // safer than v[0]
```

### 9. `front()` and `back()` – First and last elements

```cpp
v.push_back(100);
v.push_back(200);
cout << v.front(); // 100
cout << v.back();  // 200
```

### 10. `insert()` – Insert at position

```cpp
v.insert(v.begin() + 1, 150); // v = [100, 150, 200]
```

### 11. `erase()` – Erase by position or range

```cpp
v.erase(v.begin()); // v = [150, 200]
```

### 12. `resize()` – Change size

```cpp
v.resize(5); // Adds default 0s or removes elements
```

---

## 🧪 Traversing a Vector

```cpp
// Index-based
for (int i = 0; i < v.size(); i++) cout << v[i] << " ";

// Iterator-based
for (auto it = v.begin(); it != v.end(); it++) cout << *it << " ";

// Range-based for loop
for (auto x : v) cout << x << " ";
```

---

## 🧵 2D Vector

```cpp
vector<vector<int>> mat(3, vector<int>(4, 0)); // 3x4 matrix of 0s
```

---

## 🧠 Tips

* Use `reserve()` to avoid multiple resizes
* `vector` is contiguous in memory → can use with C-style arrays

---

## ✅ When to Use Vector?

* When size may change dynamically
* When you need array-like random access

---

## 📚 Related

* `vector` vs `array`
* `vector` vs `list`
* Performance tuning with `reserve()`
---
# 🌿 C++ STL: `set`

The `set` container in C++ STL stores **unique elements** in **sorted order** (by default ascending). It is usually implemented using **balanced binary search trees** (like Red-Black Tree).

---

## ✅ Basic Properties

* Stores only **unique** values
* Keeps values **sorted** automatically
* Provides **log(n)** time complexity for insert, erase, search
* Ordered using `<` comparator (can be customized)

---

## 🧱 Declaration & Initialization

```cpp
#include <set>

std::set<int> s1;                     // Empty set
std::set<int> s2 = {10, 20, 30};      // Set with values
std::set<string> s3 = {"abc", "xyz"}; // Set of strings
```

---

## ✨ Common Functions with Examples

### 🔹 `insert()` – Adds element

```cpp
s1.insert(10);
s1.insert(5);
s1.insert(10); // duplicate, will not be added
```

### 🔹 `count()` – Checks presence

```cpp
if (s1.count(5)) cout << "5 found";
else cout << "5 not found";
```

### 🔹 `erase()` – Remove element by value or iterator

```cpp
s1.erase(10);           // Remove by value
s1.erase(s1.begin());   // Remove first element
```

### 🔹 `find()` – Returns iterator to value (or `end()` if not found)

```cpp
if (s1.find(10) != s1.end())
    cout << "Found";
```

### 🔹 `begin()`, `end()` – Iterators

```cpp
for (auto it = s1.begin(); it != s1.end(); ++it)
    cout << *it << " ";
```

### 🔹 `size()` – Returns number of elements

```cpp
cout << s1.size();
```

### 🔹 `clear()` – Removes all elements

```cpp
s1.clear();
```

### 🔹 `empty()` – Checks if set is empty

```cpp
if (s1.empty()) cout << "Set is empty";
```

---

## 🔁 Example: Using all major functions

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;

    s.insert(3);
    s.insert(1);
    s.insert(7);
    s.insert(3); // ignored duplicate

    cout << "Elements in set: ";
    for (auto x : s) cout << x << " ";
    cout << endl;

    cout << "Count of 3: " << s.count(3) << endl;

    s.erase(1);

    if (s.find(7) != s.end()) cout << "7 found" << endl;

    s.clear();
    cout << "Set empty: " << s.empty() << endl;
}
```

---

## 🧠 Notes

* `set` does not allow modifying elements directly since it breaks ordering
* Internally implemented as **balanced BST** → insert/find in `O(log n)`
* Use `unordered_set` for faster (average `O(1)`) if ordering is not needed

---

## 🚀 Use-Cases

* Removing duplicates
* Storing sorted data
* Fast presence/absence checking

---
Let me know if you want to go over `multiset`, `unordered_set`, or some set-based interview problems!

---
### 1. Reverse a String

**Goal:** Reverse the characters in a string in-place or return a reversed copy.

**Steps:**

* Initialize two pointers: `left` at start, `right` at end of string.
* While `left < right`, swap characters at `left` and `right`.
* Move `left` forward and `right` backward.
* Stop when pointers meet or cross.

---

### 2. Check for Anagram

**Goal:** Check if two strings have the same characters with the same frequencies.

**Steps:**

* If lengths differ, return false immediately.
* Count frequency of each character in the first string (using a map or array).
* Decrease frequency based on the second string’s characters.
* If all frequencies return to zero, the strings are anagrams; otherwise, not.

---

### 3. Longest Palindromic Substring

**Goal:** Find the longest substring that reads the same backward.

**Steps:**

* Iterate over each character as a center.
* Expand around the center to check for odd-length palindromes.
* Also expand around center and center+1 for even-length palindromes.
* Keep track of the longest palindrome found.
* Return the longest substring after scanning all centers.

---

### 4. Remove All Duplicates

**Goal:** Remove duplicate characters, keeping only first occurrences.

**Steps:**

* Use a set or boolean array to track seen characters.
* Iterate over the string and append only characters not seen before.
* Return or modify the string to this new deduplicated string.

---

### 5. String Compression
---
What is String Compression?
You are given a string.
You need to "compress" it by replacing consecutive repeating characters with the character followed by the number of times it repeats.
If a character appears only once in a row, you just write the character (no number).

ExampleInput:
text
    aaabbcddddd

Output:
text
    a3b2cd5

---
How?

        aaa → a3 (three 'a's in a row)
        bb → b2 (two 'b's)
        c → c (just one 'c', so no number)
        ddddd → d5 (five 'd's)

**Goal:** Compress consecutive repeating characters as `char + count`.

**Steps:**

* Iterate over the string keeping track of current char and its count.
* When the next char is different, append the current char and count to the result.
* If count = 1, just append the char without count.
* Continue until the end, then return compressed string.

---

### 6. Check Rotation
---
What Does "Rotation" Mean?
A string is a rotation of another string if you can take some letters from the beginning of the string and move them to the end (without changing the order), and get the other string.

Examples
"waterbottle" and "erbottlewat"
If you move "wat" from the start to the end, you get "erbottlewat".

"hello" and "llohe"
Move "he" from the front to the end: "llohe" 

---
**Goal:** Check if one string is a rotation of another.

**Steps:**

* If lengths differ, return false.
* Concatenate the first string with itself.
* Check if the second string is a substring of this concatenation.
* If yes, it's a rotation; otherwise, no.

---

### 7. First Non-Repeating Character

**Goal:** Find the index of the first character that appears only once.

**Steps:**

* Count the frequency of each character.
* Iterate over the string and return the index of the first character with frequency 1.
* If none found, return -1.

---

### 8. Valid Palindrome (ignoring non-alphanumeric)
---
What is the Problem?
You need to check if a string reads the same forward and backward, ignoring:

Differences in upper/lower case (case-insensitive)

Non-alphanumeric characters (like spaces, punctuation, etc.)

Example:
Input: "A man, a plan, a canal: Panama"
After ignoring non-alphanumeric and case, it becomes: "amanaplanacanalpanama"
This is a palindrome.

---

**Goal:** Check if a string reads the same forward and backward, ignoring cases and non-alphanumeric chars.

**Steps:**

* Use two pointers `left` and `right` starting from ends.
* Move pointers inward skipping non-alphanumeric characters.
* Compare characters ignoring case.
* If mismatch found, return false.
* If pointers cross, return true.

---

### 9. Count and Say
---
What is the "Count and Say" Sequence?
It’s a sequence of strings where each term is generated by "reading" the previous term and describing it as counts of digits.

Example Terms:
1 (the first term)

11 (one 1)

21 (two 1s)

1211 (one 2, then one 1)

111221 (one 1, one 2, then two 1s)

312211 (three 1s, two 2s, one 1)

---

**Goal:** Generate the nth term of the count-and-say sequence.

**Steps:**

* Start with "1" as the first term.
* For each subsequent term, read the previous term left to right.
* Count consecutive repeating digits and say the count followed by the digit.
* Repeat until nth term is generated.

---

### 10. Check Subsequence

**Goal:** Check if `s` is a subsequence of `t`.

**Steps:**

* Use two pointers, `i` for `s`, `j` for `t`.
* While `j` < length of `t`, compare `s[i]` and `t[j]`.
* If equal, move `i` forward. Always move `j` forward.
* If `i` reaches end of `s`, return true (all chars matched).
* Otherwise, return false.

---


# 10 Frequently Asked String Problems in MNC Interviews

## 1. Reverse a String

**Problem:**
Reverse a given string.

**Approach:**
Use two pointers to swap characters from start and end moving toward the center.

```cpp
#include <iostream>
#include <string>
using namespace std;

string reverseString(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        cout << "Swapping " << s[left] << " and " << s[right] << endl;
        swap(s[left++], s[right--]);
    }
    return s;
}

int main() {
    string s = "hello";
    cout << "Reversed: " << reverseString(s) << endl;
    return 0;
}
```

## 2. Check for Anagram

**Problem:**
Check if two strings are anagrams of each other.

**Approach:**
Use a character count array of size 26.

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isAnagram(string s, string t) {
    cout << "Comparing: \"" << s << "\" and \"" << t << "\"" << endl;
    if (s.size() != t.size()) {
        cout << "Strings have different lengths. Not anagrams." << endl;
        return false;
    }
    vector<int> count(26, 0);
    cout << "Counting characters in first string..." << endl;
    for (char c : s) {
        count[c - 'a']++;
        cout << "  Incrementing count for '" << c << "' to " << count[c - 'a'] << endl;
    }
    cout << "Subtracting characters using second string..." << endl;
    for (char c : t) {
        count[c - 'a']--;
        cout << "  Decrementing count for '" << c << "' to " << count[c - 'a'] << endl;
    }
    cout << "Checking final counts for all characters:" << endl;
    for (int i = 0; i < 26; ++i) {
        cout << "  Character '" << char('a' + i) << "' count: " << count[i] << endl;
        if (count[i] != 0) {
            cout << "Mismatch found for '" << char('a' + i) << "'. Not anagrams." << endl;
            return false;
        }
    }
    cout << "All counts zero. Strings are anagrams." << endl;
    return true;
}

int main() {
    cout << "Result: " << isAnagram("listen", "silent") << endl;
    return 0;
}
```

## 3. Longest Palindromic Substring

**Problem:**
Find the longest palindromic substring in a given string.

**Approach:**
Expand around each character center.

```cpp
#include <iostream>
#include <string>
using namespace std;

string expandFromCenter(string s, int left, int right) {
    cout << "  expandFromCenter called with left=" << left << ", right=" << right << endl;
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        cout << "    Palindrome: " << s.substr(left, right - left + 1) << " (left=" << left << ", right=" << right << ")" << endl;
        --left; ++right;
    }
    string palindrome = s.substr(left + 1, right - left - 1);
    cout << "  Returning palindrome: " << palindrome << " from left=" << (left+1) << " to right=" << (right-1) << endl;
    return palindrome;
}

string longestPalindrome(string s) {
    string longest = "";
    cout << "Input string: " << s << endl;
    for (int i = 0; i < s.size(); ++i) {
        cout << "Center at index: " << i << endl;
        string odd = expandFromCenter(s, i, i);
        string even = expandFromCenter(s, i, i + 1);
        cout << "  Odd palindrome: " << odd << endl;
        cout << "  Even palindrome: " << even << endl;
        if (odd.size() > longest.size()) {
            cout << "  Updating longest with odd: " << odd << endl;
            longest = odd;
        }
        if (even.size() > longest.size()) {
            cout << "  Updating longest with even: " << even << endl;
            longest = even;
        }
        cout << "  Current longest palindrome: " << longest << endl;
        cout << "-----------------------------" << endl;
    }
    cout << "Final longest palindrome: " << longest << endl;
    return longest;
}

int main() {
    cout << "Result: " << longestPalindrome("babad") << endl;
    return 0;
}
```

## 4. Remove All Duplicates

**Problem:**
Remove all duplicate characters from a string.

**Approach:**
Use a boolean array to track seen characters.

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

string removeDuplicates(string s) {
    unordered_set<char> seen;
    string result = "";
    cout << "Input string: " << s << endl;
    for (char c : s) {
        cout << "Processing character: " << c << endl;
        if (seen.find(c) == seen.end()) {
            seen.insert(c);
            result += c;
            cout << "  Adding: " << c << " to result. Result now: " << result << endl;
        } else {
            cout << "  Skipping: " << c << " (already seen)" << endl;
        }
    }
    cout << "Final result: " << result << endl;
    return result;
}

int main() {
    cout << "Output: " << removeDuplicates("programming") << endl;
    return 0;
}
```

## 5. String Compression

**Problem:**
Compress the string using the counts of repeated characters.

**Approach:**
Iterate through and count consecutive characters.

```cpp
#include <iostream>
#include <string>
using namespace std;

string compressString(string s) {
    string result = "";
    for (int i = 0; i < s.length(); ) {
        int count = 1;
        while (i + count < s.length() && s[i] == s[i + count]) count++;
        result += s[i] + to_string(count);
        cout << "Char: " << s[i] << " Count: " << count << endl;
        i += count;
    }
    return result.length() < s.length() ? result : s;
}

int main() {
    cout << compressString("aaabbcc") << endl;
    return 0;
}
```

## 6. Check Rotation

**Problem:**
Check if one string is rotation of another.

**Approach:**
Concatenate original string with itself and check substring.

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isRotation(string s1, string s2) {
    if (s1.size() != s2.size()) return false;
    string temp = s1 + s1;
    cout << "Double string: " << temp << endl;
    return temp.find(s2) != string::npos;
}

int main() {
    cout << isRotation("waterbottle", "erbottlewat") << endl;
    return 0;
}
```

## 7. First Non-Repeating Character

**Problem:**
Find the first non-repeating character in a string.

**Approach:**
Use a frequency array and another pass to find the first with frequency 1.

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

char firstUniqChar(string s) {
    vector<int> count(26, 0);
    for (char c : s) count[c - 'a']++;
    for (char c : s) {
        cout << "Checking: " << c << " Count: " << count[c - 'a'] << endl;
        if (count[c - 'a'] == 1) return c;
    }
    return '_';
}

int main() {
    cout << firstUniqChar("leetcode") << endl;
    return 0;
}
```

## 8. Valid Palindrome (ignoring non-alphanumeric)

**Problem:**
Check if a string is a palindrome ignoring cases and non-alphanumeric chars.

**Approach:**
Use two pointers with character checks.

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        if (tolower(s[left]) != tolower(s[right])) return false;
        cout << "Matching: " << s[left] << " and " << s[right] << endl;
        left++; right--;
    }
    return true;
}

int main() {
    cout << isPalindrome("A man, a plan, a canal: Panama") << endl;
    return 0;
}
```

## 9. Count and Say

**Problem:**
Generate the nth term of the count-and-say sequence.

**Approach:**
Iteratively build string by counting digit groups.

```cpp
#include <iostream>
#include <string>
using namespace std;

string countAndSay(int n) {
    string result = "1";
    for (int i = 1; i < n; ++i) {
        string current = "";
        for (int j = 0; j < result.size(); ) {
            int count = 1;
            while (j + count < result.size() && result[j] == result[j + count]) count++;
            current += to_string(count) + result[j];
            cout << "Appending: " << count << result[j] << endl;
            j += count;
        }
        result = current;
    }
    return result;
}

int main() {
    cout << countAndSay(5) << endl;
    return 0;
}
```

## 10. Check Subsequence

**Problem:**
Check if one string is a subsequence of another.

**Approach:**
Use two pointers to traverse both strings.

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isSubsequence(string s, string t) {
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()) {
        cout << "Comparing: " << s[i] << " with " << t[j] << endl;
        if (s[i] == t[j]) ++i;
        ++j;
    }
    return i == s.size();
}

int main() {
    cout << isSubsequence("abc", "ahbgdc") << endl;
    return 0;
}
```
Absolutely! Below are the **step-by-step solutions** for the 10 commonly asked **array problems**, suitable for interviews and platforms like HackerRank.

---

## ✅ 1. **Find the Maximum Subarray** (Kadane’s Algorithm)

**Steps:**

1. Initialize `maxSum = currSum = nums[0]`.
2. Traverse the array from index 1:

   * `currSum = max(nums[i], currSum + nums[i])`
   * `maxSum = max(maxSum, currSum)`
3. Return `maxSum`.

---

## ✅ 2. **Two Sum**

**Steps:**

1. Initialize a hash map to store `{num → index}`.
2. For each element `x`, compute `target - x`.
3. If the difference exists in the map → return indices.
4. Otherwise, insert `x` into the map.

---

## ✅ 3. **Move Zeros**

**Steps:**

1. Use a pointer `j = 0` to track next non-zero position.
2. Loop through array:

   * If `nums[i] != 0`, swap with `nums[j]` and `j++`.
3. All zeros will move to the end.

---

## ✅ 4. **Merge Sorted Arrays** (Assume nums1 has enough space)

**Steps:**

1. Use 3 pointers:

   * `p1 = m - 1`, `p2 = n - 1`, `p = m + n - 1`
2. Compare from end of both arrays:

   * Place larger at `nums1[p]--`
3. Copy remaining from `nums2` if any.

---

## ✅ 5. **Find Missing Number** (0 to n)

**Steps:**

1. Compute expected sum: `n*(n+1)/2`.
2. Compute actual sum of array.
3. Missing number = `expected - actual`.

---

## ✅ 6. **Contains Duplicate**

**Steps:**

1. Use a set to store elements.
2. If an element already exists in the set → return true.
3. After loop, return false.

---

## ✅ 7. **Rotate Array** (Right by k steps)

**Steps:**

1. Normalize `k = k % n`.
2. Reverse entire array.
3. Reverse first `k` elements.
4. Reverse remaining `n - k` elements.

---

## ✅ 8. **Intersection of Two Arrays** (unique elements)

**Steps:**

1. Store all elements of `nums1` in a set.
2. For each `x` in `nums2`, if present in set → add to result set.
3. Return result as vector.

---

## ✅ 9. **Maximum Product Subarray**

**Steps:**

1. Initialize `maxProd = nums[0]`, `currMax = currMin = nums[0]`.
2. Traverse from index 1:

   * If negative, swap `currMax` and `currMin`.
   * Update `currMax = max(nums[i], currMax * nums[i])`
   * Update `currMin = min(nums[i], currMin * nums[i])`
   * `maxProd = max(maxProd, currMax)`
3. Return `maxProd`.

---

## ✅ 10. **Find All Duplicates in an Array**

**Steps:**

1. For each element `x = abs(nums[i])`:

   * If `nums[x - 1] < 0` → duplicate found.
   * Else, mark `nums[x - 1] = -nums[x - 1]`
2. Collect all such elements.

---


```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

// 1. Find the Maximum Subarray (Kadane’s Algorithm)
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0], currSum = nums[0];
    cout << "Initial maxSum and currSum: " << maxSum << endl;
    for (int i = 1; i < (int)nums.size(); i++) {
        currSum = max(nums[i], currSum + nums[i]);
        maxSum = max(maxSum, currSum);
        cout << "Index " << i << ": currSum = " << currSum << ", maxSum = " << maxSum << endl;
    }
    return maxSum;
}

// 2. Two Sum
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mp;
    for (int i = 0; i < (int)nums.size(); i++) {
        int diff = target - nums[i];
        cout << "Index " << i << ": num = " << nums[i] << ", looking for " << diff << endl;
        if (mp.find(diff) != mp.end()) {
            cout << "Found pair: " << mp[diff] << ", " << i << endl;
            return {mp[diff], i};
        }
        mp[nums[i]] = i;
    }
    return {};
}

// 3. Move Zeros
void moveZeroes(vector<int>& nums) {
    int j = 0;
    cout << "Original array: ";
    for (int n : nums) cout << n << " ";
    cout << endl;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] != 0) {
            cout << "Swapping nums[" << i << "]=" << nums[i] << " with nums[" << j << "]=" << nums[j] << endl;
            swap(nums[i], nums[j]);
            j++;
        }
    }
    cout << "After moving zeros: ";
    for (int n : nums) cout << n << " ";
    cout << endl;
}

// 4. Merge Sorted Arrays (nums1 has enough space)
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = m - 1, p2 = n - 1, p = m + n - 1;
    cout << "Merging arrays:" << endl;
    while (p1 >= 0 && p2 >= 0) {
        if (nums1[p1] > nums2[p2]) {
            cout << "Taking nums1[" << p1 << "] = " << nums1[p1] << endl;
            nums1[p--] = nums1[p1--];
        } else {
            cout << "Taking nums2[" << p2 << "] = " << nums2[p2] << endl;
            nums1[p--] = nums2[p2--];
        }
    }
    while (p2 >= 0) {
        cout << "Taking remaining nums2[" << p2 << "] = " << nums2[p2] << endl;
        nums1[p--] = nums2[p2--];
    }
}

// 5. Find Missing Number
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int expected = n * (n + 1) / 2;
    int actual = 0;
    for (int num : nums) {
        actual += num;
        cout << "Adding " << num << ", sum now = " << actual << endl;
    }
    cout << "Expected sum: " << expected << endl;
    return expected - actual;
}

// 6. Contains Duplicate
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> s;
    for (int num : nums) {
        cout << "Checking " << num << endl;
        if (s.find(num) != s.end()) {
            cout << "Duplicate found: " << num << endl;
            return true;
        }
        s.insert(num);
    }
    cout << "No duplicates found" << endl;
    return false;
}

// 7. Rotate Array (right by k steps)
void reverseArray(vector<int>& nums, int start, int end) {
    while (start < end) {
        swap(nums[start++], nums[end--]);
    }
}

void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    cout << "Rotate by " << k << " steps" << endl;
    cout << "Original array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    reverseArray(nums, 0, n - 1);
    cout << "After reversing whole array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    reverseArray(nums, 0, k - 1);
    cout << "After reversing first " << k << " elements: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    reverseArray(nums, k, n - 1);
    cout << "After reversing last " << n - k << " elements: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
}

// 8. Intersection of Two Arrays
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> s(nums1.begin(), nums1.end()), result;
    cout << "Set from nums1 created" << endl;
    for (int num : nums2) {
        cout << "Checking " << num << " in set" << endl;
        if (s.find(num) != s.end()) {
            cout << "Found in both arrays: " << num << endl;
            result.insert(num);
        }
    }
    return vector<int>(result.begin(), result.end());
}

// 9. Maximum Product Subarray
int maxProduct(vector<int>& nums) {
    int maxProd = nums[0], currMax = nums[0], currMin = nums[0];
    cout << "Initial maxProd: " << maxProd << endl;
    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] < 0) swap(currMax, currMin);
        currMax = max(nums[i], currMax * nums[i]);
        currMin = min(nums[i], currMin * nums[i]);
        maxProd = max(maxProd, currMax);
        cout << "Index " << i << ": currMax = " << currMax << ", currMin = " << currMin << ", maxProd = " << maxProd << endl;
    }
    return maxProd;
}

// 10. Find All Duplicates
vector<int> findDuplicates(vector<int>& nums) {
    vector<int> res;
    cout << "Finding duplicates by marking visited positions" << endl;
    for (int i = 0; i < (int)nums.size(); i++) {
        int idx = abs(nums[i]) - 1;
        cout << "Checking index " << idx << ", value: " << nums[i] << endl;
        if (nums[idx] < 0) {
            cout << "Duplicate found: " << abs(nums[i]) << endl;
            res.push_back(abs(nums[i]));
        } else {
            nums[idx] = -nums[idx];
        }
    }
    return res;
}
int main() {
    // 1. Maximum Subarray
    vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "1. Maximum Subarray Sum: " << maxSubArray(arr1) << "\n\n";

    // 2. Two Sum
    vector<int> arr2 = {2, 7, 11, 15};
    int target = 9;
    auto res2 = twoSum(arr2, target);
    cout << "2. Two Sum indices: ";
    for (int i : res2) cout << i << " ";
    cout << "\n\n";

    // 3. Move Zeros
    vector<int> arr3 = {0, 1, 0, 3, 12};
    moveZeroes(arr3);
    cout << "\n";

    // 4. Merge Sorted Arrays
    vector<int> arr4_1 = {1, 2, 3, 0, 0, 0};
    vector<int> arr4_2 = {2, 5, 6};
    merge(arr4_1, 3, arr4_2, 3);
    cout << "4. Merged array: ";
    for (int x : arr4_1) cout << x << " ";
    cout << "\n\n";

    // 5. Find Missing Number
    vector<int> arr5 = {3, 0, 1};
    cout << "5. Missing Number: " << missingNumber(arr5) << "\n\n";

    // 6. Contains Duplicate
    vector<int> arr6 = {1, 2, 3, 1};
    cout << "6. Contains Duplicate: " << (containsDuplicate(arr6) ? "Yes" : "No") << "\n\n";

    // 7. Rotate Array
    vector<int> arr7 = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;
    rotate(arr7, k);
    cout << "7. Rotated Array: ";
    for (int x : arr7) cout << x << " ";
    cout << "\n\n";

    // 8. Intersection of Two Arrays
    vector<int> arr8_1 = {1, 2, 2, 1};
    vector<int> arr8_2 = {2, 2};
    auto res8 = intersection(arr8_1, arr8_2);
    cout << "8. Intersection: ";
    for (int x : res8) cout << x << " ";
    cout << "\n\n";

    // 9. Maximum Product Subarray
    vector<int> arr9 = {2, 3, -2, 4};
    cout << "9. Maximum Product Subarray: " << maxProduct(arr9) << "\n\n";

    // 10. Find All Duplicates
    vector<int> arr10 = {4, 3, 2, 7, 8, 2, 3, 1};
    auto res10 = findDuplicates(arr10);
    cout << "10. Duplicates found: ";
    for (int x : res10) cout << x << " ";
    cout << "\n";

    return 0;
}


---

These 10 array problems cover a wide range of logic and are commonly asked in technical interviews. Each includes debug output to help understand the execution step by step.

# 10 Frequently Asked Array Problems in MNC Interviews

## 1. Find the Maximum Subarray (Kadane’s Algorithm)

**Problem:**
Given an integer array, find the contiguous subarray (containing at least one number) which has the largest sum.

**Approach:**
Use Kadane’s algorithm to maintain current and global max sums.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int maxSubArray(vector<int>& nums) {
    int maxSoFar = nums[0], maxEndingHere = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
        cout << "Step " << i << ": maxEndingHere=" << maxEndingHere << ", maxSoFar=" << maxSoFar << endl;
    }
    return maxSoFar;
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Max Subarray Sum: " << maxSubArray(nums) << endl;
    return 0;
}
```

## 2. Two Sum

**Problem:**
Given an array and a target, return indices of two numbers such that they add up to the target.

**Approach:**
Use a hashmap to store seen numbers.

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (map.count(complement)) {
            cout << "Found: " << complement << " at index " << map[complement] << endl;
            return {map[complement], i};
        }
        map[nums[i]] = i;
        cout << "Storing: " << nums[i] << " at index " << i << endl;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    vector<int> result = twoSum(nums, 9);
    cout << "Indices: " << result[0] << ", " << result[1] << endl;
    return 0;
}
```

## 3. Move Zeros

**Problem:**
Move all 0’s to the end of the array without changing the order of non-zero elements.

**Approach:**
Use two pointers to shift non-zero elements forward.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void moveZeroes(vector<int>& nums) {
    int insertPos = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[insertPos++] = nums[i];
            cout << "Moved: " << nums[i] << " to position " << insertPos - 1 << endl;
        }
    }
    while (insertPos < nums.size()) {
        nums[insertPos++] = 0;
        cout << "Inserted 0 at position " << insertPos - 1 << endl;
    }
}

int main() {
    vector<int> nums = {0,1,0,3,12};
    moveZeroes(nums);
    for (int x : nums) cout << x << " ";
    cout << endl;
    return 0;
}
```

## 4. Merge Sorted Arrays

**Problem:**
Merge two sorted arrays into one sorted array.

**Approach:**
Use two pointers and merge like in merge sort.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> mergeSortedArrays(vector<int>& a, vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) result.push_back(a[i++]);
        else result.push_back(b[j++]);
        cout << "Merged: " << result.back() << endl;
    }
    while (i < a.size()) result.push_back(a[i++]);
    while (j < b.size()) result.push_back(b[j++]);
    return result;
}

int main() {
    vector<int> a = {1, 3, 5};
    vector<int> b = {2, 4, 6};
    vector<int> result = mergeSortedArrays(a, b);
    for (int x : result) cout << x << " ";
    return 0;
}
```

## 5. Find Missing Number

**Problem:**
Find the missing number in an array of 0 to n.

**Approach:**
Use sum formula: `n*(n+1)/2 - actual sum`

```cpp
#include <iostream>
#include <vector>
using namespace std;

int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int expected = n * (n + 1) / 2;
    int actual = 0;
    for (int x : nums) actual += x;
    cout << "Expected Sum: " << expected << ", Actual Sum: " << actual << endl;
    return expected - actual;
}

int main() {
    vector<int> nums = {3,0,1};
    cout << "Missing Number: " << missingNumber(nums) << endl;
    return 0;
}
```

## 6. Contains Duplicate

**Problem:**
Check if any value appears more than once.

**Approach:**
Use an unordered_set to track elements.

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x)) {
            cout << "Duplicate found: " << x << endl;
            return true;
        }
        seen.insert(x);
        cout << "Inserting: " << x << endl;
    }
    return false;
}

int main() {
    vector<int> nums = {1,2,3,1};
    cout << containsDuplicate(nums) << endl;
    return 0;
}
```

## 7. Rotate Array

**Problem:**
Rotate the array to the right by k steps.

**Approach:**
Reverse the array in 3 parts: full, first k, rest.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
    cout << "Rotated Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    rotate(nums, 3);
    return 0;
}
```

## 8. Intersection of Two Arrays

**Problem:**
Return the intersection of two arrays.

**Approach:**
Use sets to store and compare.

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> result;
    for (int num : nums2) {
        if (set1.count(num)) {
            result.insert(num);
            cout << "Found Intersection: " << num << endl;
        }
    }
    return vector<int>(result.begin(), result.end());
}

int main() {
    vector<int> a = {1,2,2,1};
    vector<int> b = {2,2};
    vector<int> result = intersection(a, b);
    for (int x : result) cout << x << " ";
    return 0;
}
```

## 9. Maximum Product Subarray

**Problem:**
Find the contiguous subarray with the largest product.

**Approach:**
Track max and min product at each step.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int maxProduct(vector<int>& nums) {
    int maxProd = nums[0], minProd = nums[0], result = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < 0) swap(maxProd, minProd);
        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);
        result = max(result, maxProd);
        cout << "Step " << i << ": maxProd=" << maxProd << ", minProd=" << minProd << ", result=" << result << endl;
    }
    return result;
}

int main() {
    vector<int> nums = {2,3,-2,4};
    cout << "Max Product: " << maxProduct(nums) << endl;
    return 0;
}
```

## 10. Find All Duplicates

**Problem:**
Find all elements that appear twice in an array (1 ≤ a[i] ≤ n).

**Approach:**
Use in-place negation as a marker.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> findDuplicates(vector<int>& nums) {
    vector<int> result;
    for (int x : nums) {
        int index = abs(x) - 1;
        if (nums[index] < 0) {
            result.push_back(abs(x));
            cout << "Duplicate: " << abs(x) << endl;
        }
        nums[index] = -nums[index];
    }
    return result;
}

int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    vector<int> result = findDuplicates(nums);
    for (int x : result) cout << x << " ";
    return 0;
}
```
Certainly! Below are **highlighted step-by-step solutions** for each of the 10 graph problems in your document. This will help clarify the logic behind each approach.

---

## ✅ 1. Detect Cycle in Undirected Graph

**Steps:**

1. Perform DFS from every unvisited node.
2. In DFS, for each adjacent node:

   * If it’s not visited, recursively visit it.
   * If it's visited and **not the parent**, a cycle is found.

---

## ✅ 2. Detect Cycle in Directed Graph

**Steps:**

1. Use DFS with a **recursion stack** to track current path.
2. For each adjacent node:

   * If not visited, recurse.
   * If visited and in recursion stack → **cycle exists**.

---

## ✅ 3. Topological Sort (Kahn's Algorithm)

**Steps:**

1. Compute **in-degree** of each node.
2. Add nodes with 0 in-degree to queue.
3. While queue not empty:

   * Remove node, add to result.
   * Decrease in-degree of its neighbors.
   * If neighbor’s in-degree becomes 0, enqueue it.

---

## ✅ 4. Number of Islands (DFS)

**Steps:**

1. Traverse each cell in the grid.
2. On finding `'1'` (land), start DFS.
3. In DFS:

   * Mark current as `'0'` (visited).
   * Recursively visit all 4 neighbors (up/down/left/right).

---

## ✅ 5. Clone Graph

**Steps:**

1. Use DFS and a map to track cloned nodes.
2. For each node:

   * If already cloned → return clone.
   * Else, create new node and recursively clone neighbors.

---

## ✅ 6. Bipartite Graph Check

**Steps:**

1. Initialize all node colors as -1.
2. For every uncolored node:

   * Use BFS to color the graph with 2 colors.
   * If adjacent nodes have **same color**, it’s not bipartite.

---

## ✅ 7. Dijkstra’s Algorithm

**Steps:**

1. Initialize distances to all nodes as ∞, except `src = 0`.
2. Use min-heap (priority queue) for efficient min selection.
3. Pop node with smallest distance.
4. For each neighbor:

   * If shorter path is found → update and push to queue.

---

## ✅ 8. Bellman-Ford Algorithm

**Steps:**

1. Initialize distances to ∞, source = 0.
2. Relax all edges **V-1 times**:

   * For each edge, if shorter path is found → update.
3. (Optional) Run one more time to check for **negative cycle**.

---

## ✅ 9. Floyd-Warshall Algorithm

**Steps:**

1. Initialize `dist[i][j]` matrix with direct edge weights.
2. For each node `k` as intermediate:

   * Update all `dist[i][j]` using `dist[i][k] + dist[k][j]` if shorter.

---

## ✅ 10. Kruskal’s Algorithm (MST)

**Steps:**

1. Sort all edges by weight.
2. Use Union-Find to manage connected components.
3. For each edge:

   * If nodes are in different sets → add edge to MST.
   * Union the sets.
4. Stop after adding `V - 1` edges (for connected graph).

---

# 10 Frequently Asked Graph Problems in MNC Interviews

## 1. Detect Cycle in Undirected Graph

**Problem:**
Given an undirected graph, check if it contains a cycle.

**Approach:**
Use DFS. If a visited node is encountered that is not the parent of the current node, a cycle exists.

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool dfs(int v, int parent, vector<bool>& visited, vector<vector<int>>& adj) {
    visited[v] = true;
    cout << "Visiting node: " << v << endl;
    for (int u : adj[v]) {
        if (!visited[u]) {
            if (dfs(u, v, visited, adj)) return true;
        } else if (u != parent) {
            cout << "Cycle detected via node: " << u << endl;
            return true;
        }
    }
    return false;
}

bool hasCycle(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dfs(i, -1, visited, adj)) return true;
    }
    return false;
}

int main() {
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0] = {1};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {2, 4};
    adj[4] = {3};
    cout << "Cycle exists: " << hasCycle(n, adj) << endl;
    return 0;
}
```

---

## 2. Detect Cycle in Directed Graph

**Problem:**
Check if a directed graph has a cycle.

**Approach:**
Use DFS with recursion stack to detect back edges.

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool dfs(int v, vector<bool>& visited, vector<bool>& recStack, vector<vector<int>>& adj) {
    visited[v] = true;
    recStack[v] = true;
    cout << "DFS at node: " << v << endl;
    for (int u : adj[v]) {
        if (!visited[u] && dfs(u, visited, recStack, adj)) return true;
        if (recStack[u]) {
            cout << "Cycle detected at node: " << u << endl;
            return true;
        }
    }
    recStack[v] = false;
    return false;
}

bool hasCycleDirected(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false), recStack(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(i, visited, recStack, adj)) return true;
    }
    return false;
}

int main() {
    int n = 4;
    vector<vector<int>> adj = {{1}, {2}, {3}, {1}};
    cout << "Cycle exists: " << hasCycleDirected(n, adj) << endl;
    return 0;
}
```

---

## 3. Topological Sort

**Problem:**
Return a topological order of a DAG.

**Approach:**
Use DFS or Kahn’s algorithm (BFS-based).

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0), result;
    for (auto& edges : adj)
        for (int v : edges) indegree[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        result.push_back(u);
        cout << "Visiting: " << u << endl;
        for (int v : adj[u]) {
            if (--indegree[v] == 0) q.push(v);
        }
    }
    return result;
}

int main() {
    vector<vector<int>> adj = {{1, 2}, {3}, {3}, {}};
    vector<int> order = topoSort(4, adj);
    for (int x : order) cout << x << " ";
    return 0;
}
```

---

## 4. Number of Islands (DFS)

**Problem:**
Count islands in a 2D grid of '1' (land) and '0' (water).

**Approach:**
Use DFS to visit and mark each component.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0') return;
    grid[i][j] = '0';
    cout << "Visiting island cell: (" << i << ", " << j << ")" << endl;
    dfs(grid, i+1, j); dfs(grid, i-1, j); dfs(grid, i, j+1); dfs(grid, i, j-1);
}

int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                dfs(grid, i, j);
                count++;
                cout << "Island Count: " << count << endl;
            }
        }
    }
    return count;
}

int main() {
    vector<vector<char>> grid = {{'1','1','0','0','0'},
                                 {'1','1','0','0','0'},
                                 {'0','0','1','0','0'},
                                 {'0','0','0','1','1'}};
    cout << "Total Islands: " << numIslands(grid) << endl;
    return 0;
}
```

---

## 5. Clone Graph

**Problem:**
Clone an undirected graph.

**Approach:**
Use DFS with a hashmap to track visited nodes.

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int _val) { val = _val; }
};

Node* clone(Node* node, unordered_map<Node*, Node*>& map) {
    if (!node) return nullptr;
    if (map.count(node)) return map[node];

    Node* copy = new Node(node->val);
    map[node] = copy;
    cout << "Cloning node: " << node->val << endl;
    for (Node* n : node->neighbors) copy->neighbors.push_back(clone(n, map));
    return copy;
}

Node* cloneGraph(Node* node) {
    unordered_map<Node*, Node*> map;
    return clone(node, map);
}
```

---

## 6. Bipartite Graph Check

**Problem:**
Check whether a given graph is bipartite.

**Approach:**
Use BFS and color nodes with two colors. If any adjacent nodes have the same color, it's not bipartite.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                cout << "Coloring node " << u << " with color " << color[u] << endl;
                for (int v : graph[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        cout << "Conflict at node: " << v << endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << "Is Bipartite: " << isBipartite(graph) << endl;
    return 0;
}
```

---

---

### **1. Dijkstra’s Shortest Path Algorithm**

**Algorithm Explanation:**

Dijkstra’s algorithm finds the shortest path from a **single source** to all other vertices in a **graph with non-negative edge weights**. It uses a **priority queue (min-heap)** to always expand the currently known shortest node.

**Steps:**

1. Initialize all distances as infinity, except the source (0).
2. Use a min-heap to greedily select the nearest unvisited node.
3. For each neighbor, update the distance if a shorter path is found.
4. Repeat until all nodes are visited.

---

**MNC Question:**
**Problem:** You are given a city map represented as a graph. Find the shortest path from a starting node to all other cities.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int V, vector<vector<pii>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        cout << "Visiting node " << u << " with distance " << d << endl;

        for (auto [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
                cout << "Updated distance of " << v << " to " << dist[v] << endl;
            }
        }
    }
    return dist;
}
```

---

### **2. Bellman-Ford Algorithm**

**Algorithm Explanation:**

Bellman-Ford also finds the shortest path from a **single source** but supports **negative edge weights**.

**Steps:**

1. Initialize all distances to infinity, except source.
2. Relax all edges `V-1` times.
3. If a shorter path is still found, a negative-weight cycle exists.

---

**MNC Question:**
**Problem:** You are given a network with some negative tolls. Can you find the shortest distances from city `0`?

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> bellmanFord(int V, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i < V; ++i) {
        for (auto& e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                cout << "Relaxing edge " << e.u << "->" << e.v << ", new distance: " << dist[e.v] << endl;
            }
        }
    }
    return dist;
}
```

---

### **3. Floyd-Warshall Algorithm**

**Algorithm Explanation:**

This is an **all-pairs shortest path** algorithm using **dynamic programming**. It works on **both positive and negative weights** (but no negative cycles).

**Steps:**

1. Initialize `dist[i][j]` as edge weight or `∞`.
2. For each intermediate node `k`, update:

   * `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`

---

**MNC Question:**
**Problem:** Given a graph of airline routes with varying costs, find the cheapest cost between all city pairs.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void floydWarshall(vector<vector<int>>& dist) {
    int V = dist.size();
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    cout << "Updated dist[" << i << "][" << j << "] to " << dist[i][j] << endl;
                }
            }
        }
    }
}
```

---

### **4. Kruskal’s Minimum Spanning Tree Algorithm**

**Algorithm Explanation:**

Kruskal’s algorithm finds the **Minimum Spanning Tree (MST)** for a connected undirected graph.

**Steps:**

1. Sort all edges by weight.
2. Initialize disjoint sets for each vertex.
3. For each edge, if its endpoints belong to different sets, include the edge in MST.
4. Use Union-Find to avoid cycles.

---

**MNC Question:**
**Problem:** Design a network connecting all cities at the minimum cost. Edges represent cable costs.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& e) const { return w < e.w; }
};

int find(int u, vector<int>& parent) {
    if (parent[u] != u) parent[u] = find(parent[u], parent);
    return parent[u];
}

bool unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int pu = find(u, parent), pv = find(v, parent);
    if (pu == pv) return false;
    if (rank[pu] < rank[pv]) parent[pu] = pv;
    else if (rank[pu] > rank[pv]) parent[pv] = pu;
    else { parent[pv] = pu; rank[pu]++; }
    return true;
}

int kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; i++) parent[i] = i;

    int mst_weight = 0;
    for (auto& e : edges) {
        if (unionSets(e.u, e.v, parent, rank)) {
            mst_weight += e.w;
            cout << "Added edge " << e.u << " - " << e.v << ", weight = " << e.w << endl;
        }
    }
    return mst_weight;
}
```

---

